/*  praise.c - praise command to give user reputation

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object ob;
    int level = me->query_level();
    string pro = me->query_class();

    seteuid(getuid());

    if( wizardp(me) ) return notify_fail("�Ův�����g���O�H�C\n");

    // This prevent abuse of praise from new characters.
    if( level < 2 ) return notify_fail("�A�����ɨ�ĤG�Ť���A�g���~���ĪG�C\n");

    if( me->query("praise_done") )
        return notify_fail("�A���[�e�~�g���L�O�H�A�����ɯŤ���~��A�g���L�H�C\n");

    if( !arg || arg=="" )
        return notify_fail("�A�n�g���֡H\n");

    ob = find_player(arg);
    if( !ob ) return notify_fail("�o�ӤH���b�u�W�C\n");
    if( wizardp(ob) )
        return notify_fail( ob->name() + "���§A���n�N�A���L�ЧA�g���A�Y�઺���a�C\n");
    if( ob==me )
        return notify_fail("�o�ӫ��O���O�ΨӦ۸ت��A�A�u�౵���O�H���g���C\n");

    log_file("praise", sprintf("[%s] %s praised %s at level %d.\n",
        ctime(time()), getuid(me), getuid(ob), level) );
    
    if( pro=="commoner")
        ob->gain_score("reputation", level-1);
    else
        ob->gain_score("reputation", (level-1) * (level-1) );

    me->gain_score("reputation", 1);
    if( pro!="commoner" && ob->query_class()==pro )
        CLASS_D(pro)->brother_praise(me, ob);
    me->set("praise_done", 1);

    shout( sprintf(YEL "%s��%s���g����o�F�\\�h�H���{�P�A�ô����F%s���n��I\n" NOR,
            me->name(), ob->name(), ob->name() ));
    write("Ok.\n");

    return 1;
}

int help()
{
    write(@TEXT
���O�榡�Gpraise <���a>

�o�ӫ��O���A�g���Y��A�Y�઺���a�A�ô�����誺�n��A��A�ɨ�ĤG�Ť���A�C
���ɯťi�H���X�A���g���@���A�ӱ����O�H���g���èS�����󭭨�A�p�G�g���A����
�a�M�A�㦳�ۦP¾�~�A�n�洣�ɪ��ĪG�i���n�A�Ϊ̤@�ּW�[�@�ǱM�~���n��C�Y
�O�������ݥ��������A�h�ѩ󥻨��b�Z�L�������������n��A�n�椧���ɮĪG���t�C
TEXT
    );
    return 1;
}
