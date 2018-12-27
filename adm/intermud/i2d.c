/*  i2d.c

    Intermud-2 service daemon.

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
#include <socket_err.h>
#include <origin.h>

#undef LOG_UDP
#undef LOG_TRAFFIC
#define SAVE_MUDLIST

inherit F_DBASE;
#ifdef	SAVE_MUDLIST
inherit F_SAVE;
#endif	/* SAVE_MUDLIST */

static int udp_port;
static int udp_socket;

static string my_address;

static mapping event_handler = ([
    "mudlist_q":	({ INTERMUD_SERVICE("mudlist"), "receive_request" }),
    "mudlist_a":	({ INTERMUD_SERVICE("mudlist"), "receive_answer" }),
    "ping_q":		({ INTERMUD_SERVICE("ping"), "receive_request" }),
    "ping_a":		({ INTERMUD_SERVICE("ping"), "receive_answer" }),
    "gchannel":		({ INTERMUD_SERVICE("gchannel"), "receive" }),
]);

mapping mudlist;
mapping mud_alias = ([]);

// --------------------------------------------------------------------------

void set_mud_alias(string alias, string name);
private void startup();

// --------------------------------------------------------------------------

private void
create()
{
    int err;

    seteuid(getuid());
    set("channel_id", "�������F");

#ifdef	SAVE_MUDLIST
    restore();
#endif	/* SAVE_MUDLIST */

    udp_port = INTERMUD_UDP_PORT;
    if( (udp_socket = socket_create(DATAGRAM, "read_callback")) < 0 )
	error("Unable to create UDP socket.\n");
    while( EEADDRINUSE==socket_bind(udp_socket, udp_port) )
	udp_port++;

    resolve( query_host_name(), "resolve_callback" );
    call_out((: startup :), 1);
}

#ifdef SAVE_MUDLIST
string
query_save_file()
{
    return DATA_DIR + "intermud-2";
}
#endif	/* SAVE_MUDLIST */

private void
update()
{
    string mud;
    mapping m;

    if( mapp(mudlist) )
	foreach(mud, m in mudlist)
	    INTERMUD_SERVICE("ping")->send_request(
		m["HOSTADDRESS"],
		m["PORTUDP"]
	    );

    call_out((: update :), MUDLIST_UPDATE_INTERVAL);
}

private void
startup()
{
    CHANNEL_D->do_channel(this_object(), "sys",
	"Intermud �����A�ȷǳƴN���A�ϥ� UDP �� " + udp_port );

    INTERMUD_SERVICE("ping")->send_request(MUDLIST_SERVER, MUDLIST_SERVER_PORT);
    INTERMUD_SERVICE("mudlist")->send_request(MUDLIST_SERVER, MUDLIST_SERVER_PORT);
    update();
}

void
remove()
{
    if( file_name(previous_object()) != SIMUL_EFUN_OB )
	error("Permission denied\n");
    socket_close(udp_socket);

#ifdef	SAVE_MUDLIST
    save();
#endif	/* SAVE_MUDLIST */

}

private void
read_callback(int socket, string msg, string addr)
{
    string *info, p, v;
    mixed* handler;
    mapping args;

#ifdef LOG_UDP
    log_file("intermud/udp.log", sprintf("[%s] from %s (size=%d): %s\n",
	ctime(time()), addr, strlen(msg), msg) );
#endif

    if( !sscanf(msg, "@@@%s@@@%*s", msg) ) return;

    info = explode(msg, "||");
    if( sizeof(info)==0
    ||	undefinedp(handler = event_handler[info[0]]) ) return;

    args = ([]);
    foreach(string pair in info)
	if( sscanf(pair, "%s:%s", p, v)==2 ) args[p] = v;

    sscanf(addr, "%s %*d", addr);
    args["HOSTADDRESS"] = addr;

#ifdef LOG_TRAFFIC
    log_file("intermud/traffic.log", sprintf("[%s] '%s' from %s (size=%d)\n",
	ctime(time()), info[0], addr, strlen(msg)) );
#endif

    call_other(handler[0], handler[1], args);
}

private void
resolve_callback(string addr, string resolved, int key)
{
    my_address = resolved;
}

// --------------------------------------------------------------------------

int query_udp_port() { return udp_port; }
string query_address() { return my_address; }

mapping
query_mudlist()
{
    SECURED_INTERMUD_API;

    // �Ǧ^�ثe���o�pô���� MUD �C��C
    return mudlist;
}

void
set_mudinfo(string name, mapping mudinfo)
{
    mapping m;
    string p, v;

    SECURED_INTERMUD_API;

    if( ! mapp(mudlist) ) mudlist = ([]);

    if( sscanf(name, "%*d.%*d.%*d.%*d:%*d") != 5 ) return;

    // �s��o��Ĳ�� MUD ?
    if( undefinedp(m = mudlist[name]) ) {
	mudlist[name] = mudinfo;
	return;
    }

    // ��s��T ...
    foreach(p, v in mudinfo) m[p]=v;

    if( mudinfo["ALIAS"] ) set_mud_alias(mudinfo["ALIAS"], name);
}

mapping
query_mudinfo(string name)
{
    SECURED_INTERMUD_API;

    if( !mapp(mudlist) ) return 0;
    if( mapp(mudlist[name]) ) return mudlist[name];
    if( mud_alias[name] && mudlist[mud_alias[name]] )
	return mudlist[mud_alias[name]];

    return 0;
}

void
set_mud_alias(string alias, string name)
{
    SECURED_INTERMUD_API;

    if( !mapp(mudlist) || undefinedp(mudlist[name]) ) return;
    mud_alias[alias] = name;
    mudlist[name]["ALIAS"] = alias;
}

void
send_event(string dest, int port, string event, mapping args)
{
    int sock;
    string msg, p, v;

    SECURED_INTERMUD_API;

    // ���n�ǰe�s�ڭ̦ۤv�����F�Ѫ��ƥ�C
    if( undefinedp(event_handler[event]) )
	error("Invalid intermud event.\n");

    // ���n�ǰe��Ƶ��ۤv�A���o�ä��O���~�C
    if( dest==my_address ) return;

    sock = socket_create(DATAGRAM, "read_callback");
    if( !sock ) return;

    // �N�T���]�˦� Intermud-2 ���T����C
    msg = event;
    if( mapp(args) ) {
	foreach(p, v in args) {
	    if( !stringp(p) || !stringp(v) ) continue;
	    msg += sprintf("||%s:%s", p, v);
	}
    }

    // �e�X�T���C
#ifdef LOG_TRAFFIC
    log_file("intermud/traffic.log", sprintf("[%s] '%s' sent to %s (size=%d)\n",
	ctime(time()), event, dest + " " + port, strlen(msg)+6) );
#endif

    socket_write(sock, "@@@" + msg + "@@@", dest + " " + port);
    socket_close(sock);
}
