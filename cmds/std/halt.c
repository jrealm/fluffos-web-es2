/*  halt.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include "/doc/help.h"
#include <action.h>
#include <command.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    SECURED_COMMAND;

    if( me->is_busy() ) {
        me->interrupt(me, INTR_HALT);
        if( ! me->is_busy() ) {
            write("Ok�C\n");
            return 1;
        }
        return 0;
    }

    if( !me->is_fighting() )
        return notify_fail("�A�{�b�èS���b�԰��C\n");

    if( wizardp(me) ) {
        me->remove_all_killer();
        message_vision("$N�ΧŮv�����O����F�o�������C\n", me);
    } else {
        me->remove_all_enemy();
        message_vision("$N�V��@�D�A���}�԰�}�⤣���F�C\n", me);
    }

    write("Ok.\n");
    return 1;
}

int help(object me)
{
   write(@HELP
���O�榡�Ghalt

�i�H����Ҧ��P�A(�p)���b�i�檺��աM���O���b��A�ʩR�۷i���ĤH�q�`
���|�������M�C

�o�ӫ��O���ɭԤ]�i�H�ΨӰ���@�ǻݭn�����ɶ����ʧ@�A�p�׽m���\�B��
�����A���L�ण�ఱ��n�����Ӱʧ@�өw�C
HELP
   );
   return 1;
}
