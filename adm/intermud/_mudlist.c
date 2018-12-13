/*  _mudlist.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <mudlib.h>
#include <intermud.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

void
receive_answer(mapping info)
{
    string name, chunk;

    SECURED_INTERMUD_EVENT;

    foreach(name, chunk in info)
    {
	string *prop_list;
	mapping mudinfo;

	if( strsrch(chunk, "NAME")==-1 ) continue;

	mudinfo = ([ ]);
	prop_list = explode(chunk, "|") - ({ "" });

	foreach(string prop in prop_list) {
	    string p, v;
	    if( sscanf(prop, "%s:%s", p, v)==2 ) mudinfo[p] = v;
	}

	// �ˬd�Ҧ����������O�_�����w�q ...
	if( undefinedp(mudinfo["NAME"])		// MUD ���W��
	||  undefinedp(mudinfo["PORT"])		// MUD ���s����
	||  undefinedp(mudinfo["PORTUDP"])	// MUD �� intermud �s����
	)   continue;

	// HOSTADDRESS �o�����@�w�|�s�b( �� INTERMUD_D �]�w )
	INTERMUD_D->set_mudinfo(
	    mudinfo["HOSTADDRESS"] + ":" + mudinfo["PORTUDP"], mudinfo);
    }
}

void
receive_request(mapping info)
{
    SECURED_INTERMUD_EVENT;
}

void
send_request(string dest, int port)
{
    SECURED_INTERMUD_API;
    INTERMUD_D->send_event(dest, port, "mudlist_q", ([
	"HOSTADDRESS":	INTERMUD_D->query_address(),
	"PORTUDP":	"" + INTERMUD_D->query_udp_port(),
    ]));
}
