/*  restore.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <login.h>
#include <command.h>

inherit F_CLEAN_UP;

int
main(object me, string arg)
{
    string save_file;
    object ob;

    SECURED_ARCH_COMMAND;

    if( !arg ) return notify_fail("���O�榡�Grestore <���a>\n");
    seteuid(getuid());
    ob = new(USER_OB);
    seteuid(arg);
    export_uid(ob);
    seteuid(getuid());

#ifdef SAVE_USER
    save_file = ob->query_save_file();
    destruct(ob);
    if( cp(save_file+".backup", save_file) ) {
          write("�ƥ��^�s�����C\n");
          log_file("static/RESTORE",
              sprintf("%s restored by %s [%s]\n", arg, geteuid(this_player(1)), ctime(time())) );
    } else
        write("�ƥ��^�s���ѡI\n");
    return 1;
#else
    return notify_fail("�t�Υثe���x�s�ϥΪ̸�ơC\n");
#endif
}

int help(object me)
{
    write(@HELP
���O�榡�Grestore <���a>

���^�@�Ӫ��a���e�x�s���ƥ���ơC
HELP
    );
    return 1;
}
