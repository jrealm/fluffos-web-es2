/*  edit.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string file)
{
    SECURED_WIZARD_COMMAND;

    if( !file ) return notify_fail("���O�榡�Redit <�ɦW>\n");

    if( in_edit(me) ) return notify_fail("�A�w�g�b�ϥνs�边�F�C\n");

    seteuid(geteuid(this_player(1)));
    ed(resolve_path(me->query("cwd"), file));
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : edit <�ɦW>|edit here

�Q�Φ��@���O�i�����b�u�W�s���ɮסC
HELP
    );
    return 1;
}
