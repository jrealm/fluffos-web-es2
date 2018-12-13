/*  _gchannel.c

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

static string id;
static mapping spam_check = ([]);

private void create() { seteuid(getuid()); }

string query(string prop) { return prop=="channel_id" ? id : 0; }

void
receive(mapping info)
{
    mapping m;
    int port;
    string mid, encoding, msg;

    SECURED_INTERMUD_EVENT;

    // �ˬd���������O�_���� ...
    if( undefinedp(info["NAME"])
    ||	undefinedp(info["PORTUDP"])
    ||	undefinedp(info["USRNAME"])
    ||	undefinedp(info["CHANNEL"])
    ||	undefinedp(msg = info["MSG"])
    )	return;

    // �p�G�ڭ̨S�����o�M�o�� MUD ���pô�A�e�X�@�� PING �n�D�C
    mid = info["HOSTADDRESS"] + ":" + info["PORTUDP"];
    if( !mapp(m = INTERMUD_D->query_mudinfo(mid)) )
	INTERMUD_SERVICE("ping")->send_request(info["HOSTADDRESS"],
		info["PORTUDP"]);

#ifdef	ENABLE_ANTISPAM
    if( spam_check[mid]==msg ) return;
	spam_check[mid] = msg;
#endif
    
    id = info["USRNAME"] + "@" + info["NAME"];

    // �Y�� CNAME�A�ϥ��X�R�榡�C
    if( info["CNAME"] ) id = info["CNAME"] + "(" + id + ")";

    // �ˬd�O�_���w�ϥλy�����s�X�覡�C
    encoding = info["ENCODING"];
    if( !encoding && mapp(m) ) encoding = m["ENCODING"];

    // �ݭn���ܶi����X�C
    if( encoding && encoding != MUDLIB_LOCALE ) {
	if( encoding=="GB" && MUDLIB_LOCALE=="BIG5" ) {
	    id = LANGUAGE_D->GB2Big5(id);
	    msg = LANGUAGE_D->GB2Big5(id);
	}
	else if( encoding=="BIG5" && MUDLIB_LOCALE=="GB" ) {
	    id = LANGUAGE_D->Big52GB(id);
	    msg = LANGUAGE_D->Big52GB(id);
	}
    }

    // �����W�D�T���C
    CHANNEL_D->do_channel(this_object(), info["CHANNEL"], msg, info["EMOTE"] );
}

void
send(string ch, string id, string name, string msg, int emote, function flt)
{
    string mid;
    mapping info, mud;

    SECURED_INTERMUD_API;

    info = ([
	"NAME":		MUD_NAME_INTERMUD,
	"PORTUDP":	"" + INTERMUD_D->query_udp_port(),
	"USRNAME":	id,
	"CNAME":	name,
	"CHANNEL":	ch,
	"ENCODING":	MUDLIB_LOCALE,
	"MSG":		msg,
    ]);

    if( emote ) info["EMOTE"] = "YES";

    foreach(mid, mud in INTERMUD_D->query_mudlist())
    {
	if( ! evaluate( flt, mud ) ) continue;
	INTERMUD_D->send_event(mud["HOSTADDRESS"], mud["PORTUDP"],
		"gchannel", info);
    }
}
