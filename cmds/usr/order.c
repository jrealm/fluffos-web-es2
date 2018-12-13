/*  order.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int res;
    object ob;
    string who, cmd, verb, path;

    // No indirect mode for this command.
    if( me != this_player(1) ) return 0;

//    if( !wizardp(me) ) return 0;

    if( !arg || arg=="" || sscanf(arg, "%s to %s", who, cmd)!=2 )
        return notify_fail("�A�n�R�O�ְ�����ơS\n");

    ob = present(who, environment(me));
    if( !ob || !ob->is_character())
        return notify_fail("�o�̨S���o�ӤH�C\n");

    if( sscanf(cmd, "%s %*s", verb) != 2 ) verb = cmd;

    if( stringp(path = ob->find_command(verb))
    &&    path != "/cmds/std/" + verb )
        return notify_fail("�A����R�O�O�H���o�بơC\n");

    if( wizardp(ob) && wiz_level(me) <= wiz_level(ob) )
        return notify_fail("�A��������o�ӤH�C\n");

    write("�A�R�O" + ob->name() + ": " + cmd + "\n");
    if( (object)ob->query_temp("possessed") != me
    &&    !ob->accept_order(me, verb) )
        return notify_fail( "�ݰ_��" + ob->name() + "�ä��Qť�A�����C\n");

    notify_fail( ob->name() + "�L�k�����o�өR�O�C\n");
    seteuid(getuid());
//    snoop(me, ob);
    res = ob->force_me(cmd);
//    snoop(me);
    return res;
}

int help(object me)
{
    write(@TEXT
���O�榡�Rorder <�Y�H> to <���O>

�R�O�L�H����Y�ӫ��O�R�ܩ�p��ϥL�Hť�A���R�O ... �ۤv�� :P
TEXT
    );
    return 1;
}
