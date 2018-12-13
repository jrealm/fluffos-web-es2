/*  promote.c

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

static void create() { seteuid(getuid()); }

int
main(object me, string arg)
{
    object ob;
    string old_status, new_status;

    SECURED_ARCH_COMMAND;

    if( !arg || sscanf(arg, "%s %s", arg, new_status)!=2 )
        return notify_fail("���O�榡�Rpromote <�ϥΪ�> <����>\n");

    if( wiz_level(new_status) < 0 ) return notify_fail("�S���o�ص��šC\n");
    if( wiz_level(me) < wiz_level(new_status) )
        return notify_fail("�A�S���o���v�O�C\n");

    if( !objectp(ob = find_player(arg))) {
        if( !(SECURITY_D->set_status(arg, new_status)) )
            return notify_fail("�ק異�ѡC\n");
        write("Ok.\n");
        return 1;
    }

    old_status = wizhood(ob);

    if( !(SECURITY_D->set_status(ob, new_status)) )
        return notify_fail("�ק異�ѡC\n");

    message_vision("$N�N$n���v���q " + old_status + " �אּ " + new_status + " �C\n", me, ob);
    seteuid(getuid());
    ob->setup();

    return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : promote <�Y�H> (�v������)

�ΨӴ����v������, (player) (immortal) (apprentice) (wizard) (arch) (admin)
�@�� admin �ണ���v���ܥ��󵥯�, �� arch �u�ണ�ɦ� arch�C
HELP
    );
    return 1;
}
