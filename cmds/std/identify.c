/*  identify.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <combat.h>

inherit F_CLEAN_UP;

mapping named_apply = ([
    "attack" : "������O��",
    "defense" : "���m��O��",
    "str" : "�M�O",
    "cor" : "�x��",
    "cps" : "�w�O",
    "int" : "����",
    "wis" : "�z��",
    "spi" : "�F��",
    "con" : "�ڰ�",
    "dex" : "����",
    "damage" : "�ˮ`�O",
    "armor" : "���m�O",
]);

int main(object me, string arg)
{
    object ob;
    string type, sub_type;
    class damage_parameter dp;
    mapping apply;

    if( me->is_busy() ) return 0;

    if( !arg ) return notify_fail("�A�nŲ�w����F��?\n");
    ob = present(arg, me);
    if( !ob ) return notify_fail("�A�nŲ�w����F��?\n");
    if( !(type = ob->query("equipped")) )
        return notify_fail("�A�������˳�" + ob->name() + "�~��Ų�w.\n");
    if( sscanf(type, "%s/%s", type, sub_type) != 2 )
        return notify_fail("�o�����~�L�kŲ�w.\n");

    if( !wizardp(me) ) {
        if( me->query_stat("sen") < 10 )
            return notify_fail("�A�Ӳ֤F.\n");
        me->consume_stat("sen", 10);
    }

    write(ob->long() + "\n");
    if( type=="weapon" ) {
        string s;
        mixed sk = ob->query("wield_as");
        
        write("�i�Χޯ�G\n");
        if( stringp(sk) ) sk = ({ sk });
        foreach(s in sk)
            printf("  %s (%s)\n", to_chinese(s), s);
        dp = ob->query("damage/" + sub_type);
        printf("\n�ˮ`�O�G %d - %d (�O�q�ץ� %d%%�A���Ƶ��� %d)\n", 
            dp->roll + dp->multipler,
            dp->roll + dp->multipler * dp->range,
            dp->bonus, dp->multipler );
        apply = ob->query("apply_" + type + "/" + sub_type);
        if( mapp(apply) ) {
            string prop;
            mixed value;
            
            write("\n�Z���S�ʡR\n");
            foreach(prop, value in apply) {
                if( !undefinedp(named_apply[prop]) )
                    prop = named_apply[prop];
                else
                    prop = to_chinese(prop);
                printf("  %-30s %O\n", prop, value);
            }
        }
    }
    if( type=="armor" ) {
        apply = ob->query("apply_" + type + "/" + sub_type);
        if( mapp(apply) ) {
            string prop;
            mixed value;
            
            write("�@��S�ʡR\n");
            foreach(prop, value in apply) {
                if( !undefinedp(named_apply[prop]) )
                    prop = named_apply[prop];
                printf("  %-30s %O\n", to_chinese(prop), value);
            }
        }
    }

    return 1;        
}

int help(object ob)
{
    write(@TEXT
���O�榡: identify <����>

�o�ӫ��O�i�H���AŲ�w�@�ǪZ���˳Ƶ����~, �ݭn��O�@�Ǻ믫.
TEXT
    );
    return 1;
}
