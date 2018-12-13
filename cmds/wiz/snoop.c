/*  snoop.c

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

int main(object me, string arg)
{
    object ob;

    SECURED_WIZARD_COMMAND;

    if( !arg ) {
        if( objectp(ob = query_snooping(me)) )
            write("�A�{�b���b��ť" + ob->query("name") + "�Ҧ��쪺�T���C\n");
        return 1;
    } else if( arg=="none" ) {
        if( objectp(ob = query_snooping(me))
        &&    wiz_level(ob) >= wiz_level(me) )
            tell_object(ob, HIW + me->name(1) + "�����ť�A�Ҧ��쪺�T���C\n" NOR);
        snoop(me);
        write("Ok.\n");
        return 1;
    }

    ob = find_player(arg);
    if(!ob) ob = find_living(arg);
    if(!ob || !ob->visible(me)) return notify_fail("�S���o�ӤH�C\n");

    if( wizhood(me) != "(admin)"
    &&    wiz_level(me) <= wiz_level(ob) || wiz_level(me) < 3)
        return notify_fail("�A�S����ť" + ob->name() + "�Ҧ�ť�T�����v�Q�C\n");

    if( me==ob ) return notify_fail("�Х� snoop none �Ѱ���ť�C\n");
        
    snoop(me, ob);
    write("�A�{�b�}�l��ť" + ob->name(1) + "�Ҧ��쪺�T���C\n");
    if( userp(ob) ) {
	log_file("SNOOP_PLAYER",
	    sprintf("[%s] %s snoops %O\n", ctime(time()), geteuid(me), ob));
	if( wizardp(ob) && wiz_level(me) < wiz_level("(arch)") )
	    tell_object(ob, HIW + me->name(1) + "�}�l��ť�A�Ҧ��쪺�T���C\n" NOR);
    }

    return 1;
}

int help()
{
    write(@TEXT
���O�榡�Rsnoop <�Y�H>|none

��ť��L�ϥΪ̩Ҧ�ť���T���Msnoop none �h������ť�C
TEXT
    );
    return 1;
}
