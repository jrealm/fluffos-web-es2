/*  rmdir.c

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

int help(object me);

int main(object me, string arg)
{
    string dir;

    SECURED_WIZARD_COMMAND;

    if(!arg) return help(me);

    dir = resolve_path(me->query("cwd"), arg);

    seteuid(geteuid(this_player(1)));
    if( rmdir(dir) )
        write("Ok.\n");
    else
        write("�R�����ѡC\n");
    return 1;    
}

int help(object me)
{
    write(@HELP
���O�榡 : rmdir <�l�ؿ��W>

�R���@�Ӥl�ؿ��C
HELP
    );
    return 1;
}
