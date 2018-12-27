/*  cestablish.c - to establish a clan

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
#include <ansi.h>
inherit F_CLEAN_UP;

private void get_clan_name(string arg, object me);
private void confirm_name(string yn, object me);
private void get_clan_rank(string arg, object me);
private void confirm_rank(string yn, object me);

int main(object me, string arg)
{
	object who;

	if( !arg ) {
		if( me->query("level") < 50 
		|| me->query_score("reputation") < 60000 ) return 
			notify_fail("�u���n����������Ū��a�~�����������C\n");

		if( me->query("clan/create") ) return 
			notify_fail("�C�ӤH�@�ͥu���\\�гy�@���s�����C\n");

		if( me->query("clan/clan_level") ) return 
			notify_fail("�A�w�g�O���������F, �Х�������������C\n");

		if( me->query_temp("clan/sign_number") < 2 ) return
			notify_fail("�A�ܤֱo���ӰƤ�������~������C\n");
		write("�ثe�w���������p�U: \n\n");
		seteuid(ROOT_UID);
		write( read_file("/obj/CLAN") );
		write("\n�b���W�M�w���e, �i�H�ɥH���O:q������������C��\n");
		write("�Ф@�㭷�檺���s�����C�п�J�����W: ");
		input_to((: get_clan_name :), me);
		return 1;
	}

	if( sscanf(arg, "with %s", arg) ) {
		if( me->query("level") < 44 ) return 
			notify_fail("�A�����Ť����H�ѻP�����C\n");

		if( me->query("clan/clan_level") ) return 
			notify_fail("�A�w�g�O���������F, �L�k���U�~�H�����C\n");

		if( me->query("clan/signed") ) return 
			notify_fail("�A�w�g�������߹L���|�F�C\n");

		who = present(arg, environment(me));

		if( who == me ) return notify_fail("�Ч�ۤv�H�~���H�����C\n");

		if( !objectp(who) || !living(who) ) 
			return notify_fail("�o�̨S���o�ӤH�C\n");

		message_vision(HIW"$N�M�w��U$n�Хߤ@�ӷs�����C\n"NOR
		, me, who);

		who->add_temp("clan/sign_number", 1);
		me->set("clan/signed", 1);
#ifdef SAVE_USER
        me->save();
#endif
		return 1; }
	else {
		tell_object(me, 
		"���O�榡: cestablish �άO cestablish with <�Y�H>\n");
		return 1;
	}
}

private void get_clan_name(string arg, object me)
{
        seteuid(getuid(me));
	me->set("clan/clan_name", arg);
	write("�z�T�w�n�γo��z�������W��(y/n/q)�S");
	input_to((: confirm_name :), me);
}

private void confirm_name(string yn, object me)
{        
	if( yn=="" ) {
		write("�z�T�w�n�γo��z�������W��(y/n)�S");
                input_to((: confirm_name :), me);
                return;
	}
	if( yn == "q" ) {
		write("����....�U���a�C\n");
		return;
	}

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("����Э��s��J�z�Q�n�������W�r: ");
                input_to((: get_clan_name :), me);
                return;
        }
	seteuid(ROOT_UID);
	// keep in /log/CLAN
	log_file("CLAN", sprintf("[%s] %s �� %s(%s) �Х�\n",
        ctime(time()), me->query("clan/clan_name"), me->name(),
        me->query("id")) );
	// write in /obj/CLAN for player to query clan data
	write_file("/obj/CLAN", sprintf("[%s] %s �� %s(%s) �Х�\n",
	ctime(time()), me->query("clan/clan_name"), me->name(),
	me->query("id")) );
	write("�п�J�o��������ɤH���ٸ�(�p: ���D, ���D, �x��): ");
	input_to((: get_clan_rank :), me);
}

private void get_clan_rank(string arg, object me)
{
	if( strlen(arg) > 4 ) {
		write("�ٸ��L��, �Э��s��J: ");
		input_to((: get_clan_rank :), me);
	}
	seteuid(getuid(me));
	me->set("clan/rank", arg);
	me->set("clan/nick", "�Ĥ@�N�j�Y��");
	me->set("clan/clan_level", 3);
	me->set("clan/elder", 0);
	write("�z�T�w�n�γo��z�������ٸ���(y/n)�S");
	input_to((: confirm_rank :), me);
}

private void confirm_rank(string yn, object me)
{
	object mark;

	if( yn=="" ) {
		write("�z�T�w�n�γo��z�������ٸ���(y/n)�S");
                input_to((: confirm_rank :), me);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("����Э��s��J�z�Q�n�������ٸ�: ");
                input_to((: get_clan_rank :), me);
                return;
        }
#ifdef SAVE_USER
        me->save();
#endif
	message("system", HIW"�Ѵ¤��i: "+me->query("clan/clan_name")
	+"�w��"+me->name()+"�Хߧ���, �}�l�ۦ�����!!\n"NOR, users());
	mark = new("/obj/clan_symbol");
	mark->move(me);
	return;		
}


int help(object me)
{
write(@HELP
�����O�γ~����������, �Q�����������H(�H�U�H���D�٤�)������
��H(�H�U�H�����٤�)��U�@�_�i��, ��ন�߷s�����C�b������
������, �����H�ƥ��ݦb��H�H�W, �ӦU����������������аѾ\
: help clan, ���O�榡�p�U:
1. �����
   cestablish with <�Y�H>
2. ���D
   cestablish
   ���H���ܶ�J�����U���򥻸�ơC�>
HELP
    );
    return 1;
}
