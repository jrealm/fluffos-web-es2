/*  enable.c - enable a special skill with another skill

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
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    mapping map;
    string *types, *skill, ski, map_to;
    int i, modify;

    SECURED_COMMAND;

    if( !arg ) {
        map = me->query_skill_map();
        if( !mapp(map) ) map = ([]);

        write("�H�U�O�A�ثe�ϥΤ����S��ޯ�C\n");
        foreach( skill, map_to in map ) {
            printf("%-20s�G%s\n", to_chinese(skill),
                map_to ? to_chinese(map_to) : "���ϥ�");
        }
        return 1;
    }

    if( sscanf(arg, "%s with %s", ski, map_to)==2 ) {

        if( !me->query_skill(map_to, 1) && !me->query_learn(map_to) )
            return notify_fail("�A���|�o�اޯ�C\n");

        if( !function_exists("valid_enable", SKILL_D(map_to)) )
            return notify_fail( "�u" + to_chinese(map_to) + "�v����M��L�ޯ�X�ΡC\n");

        notify_fail("�o�ӧޯण����o�إγ~�C\n");
        if( !SKILL_D(map_to)->valid_enable(ski) )
            return 0;

        me->map_skill(map_to, map_to);
        me->map_skill(ski, map_to);

        write("�A�M�w�ϥΡu" + to_chinese(map_to) + "�v��@" + to_chinese(ski) + "�C\n");
        return 1;
    }

    if( !me->query_learn(arg) )
        return notify_fail("�A�S���ǹL�o�اޯ�C\n");

    if( me->skill_mapped(arg)==arg ) {
        write("�A�b�A�����X�|�۰ʨϥγo�ӧޯ�C\n");
        return 1;
    }

    me->map_skill(arg);
    write("�A�M�w��_�ϥΩҾǦ����u" + to_chinese(arg) + "�v���ޥ��C\n");

    return 1;
}
int help(object me)
{
    write(@HELP
���O�榡 : enable <�ޯ����> with <�ޯ�W��>   <- �ϥίS��ޯ�B�Z�N
           enable <�ޯ����>                   <- �u�ΰ򥻧ޯ�

�o�ӫ��O���A���w�ҭn�Ϊ��ޯ�M�ݫ����ޯ�����M�ޯ�W�١C�p�G���[�Ѽƫh�|
��ܥX�ޯ�����ΧA�ثe�ҨϥΪ��ޯ�W�� �M�p�G�[�@�� ? �|�C�X�Ҧ���ϥίS
��ޯ઺�ޯ�����C

SEE ALSO:
    disable 
HELP
    );
    return 1;
}
