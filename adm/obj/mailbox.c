/*  mailbox.c

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

inherit ITEM;
inherit F_SAVE;

/* �o�� mapping �x�s���J���l�󤺮e�A�ŧi�� private �H����Q��L����H
 * �~�Ӥ覡�s���C
 */
private mapping *mails;

void get_mail_text(mapping mail, string str);

private void
create()
{
    set_name("�H��", "mail folder", "mail", "folder" );
    set("long", @LONG
�o�O�@�ӥΨӾ�z�A�H�󪺫H���M�A�i�H�ΥH�U���O�ӳB�z�A���H��G

mail <�Y�H>		�H�H���O�H�M���D�A�O�Ův�M�_�h�A�����b�毸�~��H�H�C
forward <�s��> <�Y�H>	�N�Y�ʫH��H���O�H�M�P�˥����b�毸�~���ΡC
from [-a]		�d�ݫH�������H��A�w�]�u��ܩ|��Ū�����H��A�[�W -a
			�|��ܥ������H��C
read <�s��>		�\Ū�@�ʫH��C
discard <�s��>		���@�ʫH��C
LONG
    );
    set("unit", "��");
    set("no_drop", "�p�H���H���Ф��n�H�K���C\n");
    set("no_insert", 1);
    setup();

    seteuid(0);	/* �M�� euid�A�� SMTP daemon ���w uid ���o�Ӫ��� */
}

varargs string
short(int raw)
{
    if( arrayp(mails) && sizeof(mails) )
	return ::short(raw) + "[ " + sizeof(mails) + " �ʫH ]";
    return ::short(raw) + "[ �ŵL�@�� ]";
}

nomask void
retire()
{
    destruct(this_object());
}

nomask private void
init()
{
    object ob;

    if( environment()!=this_player() ) {
	/* �w�����I�G�Y mailbox �Q���ʨ� this_player() �H�~���a��A�ߨ�
	 * �P�����󤤸��J���l�󤺮e�A�þ��־P���o�Ӫ���C
	 */
	mails = 0;
	call_out("retire", 0);
	return;
    }

    seteuid(getuid());		/* �]�w euid�A�ΨӸ��J SMTP daemon */
    ob = load_object(SMTP_D);
    seteuid(0);			/* �M�� euid�A�� SMTP ���w uid ���o�Ӫ��� */
    ob->restore_mailbox(this_object());

    if( objectp(ob = this_player()->query_temp("mbox_ob")) )
	ob->retire();

    this_player()->set_temp("mbox_ob", this_object());

    set("owner_ob", this_player());
    add_action("do_mail", "mail");
    add_action("do_forward", "forward");
    add_action("do_from", "from");
    add_action("do_read", "read");
    add_action("do_discard", "discard");
}

nomask string
query_save_file()
{
    return mail_data(getuid());
}

void receive_mail(mapping mail)
{
    /* �u�����Ӧۨ㦳 ROOT �v��������Ұe���H */
if (!previous_object()) error("no previous object\n");
    if( geteuid(previous_object()) != ROOT_UID )
	error("Permission denied.\n");

    if( !pointerp(mails) ) mails = ({ mail });
    else mails += ({ mail });
}

private int
do_mail(string arg)
{
    mapping mail;

    if( this_player()!=environment() ) return 0;
    if( !wizardp(this_player())
    &&  !environment(this_player())->query("post_office") )
	return notify_fail("�A������@���毸�~��H�H�C\n");

    if( !arg || arg=="" )
	return notify_fail("�A�n�H�H���֡S\n");

    mail = ([
	"from": this_player()->name(1) + "(" + this_player()->query("id") + ")",
	"unread": 1 ,
	"title": "�L�D",
	"to": arg,
	"time": time(),
	"text": ""
    ]);
    write("�H����D�R");
    input_to("get_mail_title", mail);
    return 1;
}

private void
get_mail_title(string str, mapping mail)
{
    if( str!="" ) mail["title"] = str;
    write("�H�󤺮e�R\n");
    this_player()->edit( (: get_mail_text, mail :) );
}

void get_mail_text(mapping mail, string str)
{
    mail["text"] = str;
    write("�z�ۤv�n�d�@���ƥ���(y/n)�S[n]");
    input_to("confirm_copy", mail);
}

private void
confirm_copy(string yn, mapping mail)
{
    if( yn[0]=='y' || yn[0]=='Y' ) receive_mail(mail);
    if( SMTP_D->send_mail(getuid(), mail["to"], mail) )
	write("Ok.\n");
    else
	write("�H�H���ѡI\n");
}

private int
do_from(string arg)
{
    int i, n_listed = 0, all = 0;
    string txt = "--------------------------------------------------\n";

    if( !arrayp(mails) || !sizeof(mails) ) {
	write("�A���H�����ثe�S������H��C\n");
	return 1;
    }

    if( arg=="-a" ) all = 1;
    for(i=sizeof(mails)-1; i>=0; i--)
    {
	mapping msg = mails[i];

	if( !all && !msg["unread"] ) continue;
	n_listed++;
	if( msg["unread"] == 1 )
	    txt += sprintf("%2d " HIC "%-46s �Ӧ�: %-20s\n" NOR,
		i+1, msg["title"], msg["from"]);
	else
	    txt += sprintf("%2d %-46s �Ӧ�: %-20s\n",
		i+1, msg["title"], msg["from"]);
    }
    if( all ) txt = "�A�{�b�@�� " + sizeof(mails) + " �ʫH��R\n" + txt;
    else txt = sprintf("�A�@�� %d/%d �ʥ�Ū���H�G\n%s", n_listed,
	sizeof(mails), txt);
    this_player()->start_more(txt);

    return 1;
}

private int
do_read(string arg)
{
    int num;

    if( !arg || !sscanf(arg, "%d", num) )
	return notify_fail("�A�nŪ���@�ʫH�S\n");

    if( !pointerp(mails) || num < 1 || num > sizeof(mails) )
	return notify_fail("�S���o�ӽs�����H��C\n");

    num--;

    printf(HIC "�H����D�R%s\n�H�H�H�R%s" NOR "\n\n%s\n",
	mails[num]["title"], mails[num]["from"], mails[num]["text"] );

	mails[num]["unread"] = 0;
	save();
    return 1;
}

private int
do_discard(string arg)
{
    int num;

    if( !arg || !sscanf(arg, "%d", num) )
	return notify_fail("�A�n�����@�ʫH�S\n");

    if( !pointerp(mails) || num > sizeof(mails) )
	return notify_fail("�S���o�ӽs�����H��C\n");

    num --;

    mails = mails[0..num-1] + mails[num+1..sizeof(mails)-1];
    save();
    write("Ok.\n");

    return 1;
}

private int
do_forward(string arg)
{
    string dest;
    int num;
    mapping m;

    if( !wizardp(this_player())
    &&  !environment(this_player())->query("post_office") )
	return notify_fail("�A������@���毸�~��H�H�C\n");

    if( !arg || sscanf(arg, "%d %s", num, dest)!=2 )
	return notify_fail("�A�n�N���@�ʫH��H���O�H�S\n");

    if( !pointerp(mails) || num > sizeof(mails) )
	return notify_fail("�S���o�ӽs�����H��C\n");

    num --;

    m = ([]);
    m["title"] = mails[num]["title"];
    m["text"] = mails[num]["text"];
    m["unread"] = 1;
    m["time"] = mails[num]["time"];
    m["from"] = mails[num]["from"] + "/��H��" + this_player()->query("name");
    m["to"] = dest;
    SMTP_D->send_mail( getuid(), dest, m );
    write("Ok.\n");

    return 1;
}

nomask void
owner_is_killed()
{
    retire();
}

