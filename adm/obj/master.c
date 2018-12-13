/*  master.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

// Created by Annihilator (04/16/2000)

#include <http.h>

private void
create()
{
    write("master: loaded successfully.\n");
}

private object
connect(int port)
{
    object ob;
    mixed err;

    /* �t�m�@�ӷs���s�u����Ψӧ@���n�J�{�Ǫ��ϥΪ̪��� */
    switch(port)
    {
    case MUD_PORT:
    case 4001:
	err = catch(ob = new(LOGIN_OB));
	if( err ) {
	    write("�ϥΪ̵n�J�{�����b���פ��A�еy�ԦA�ӡC\n");
	    if( query_ip_number()=="127.0.0.1" ) write(err);
	    return 0;
	}
	return ob;
    case HTTP_PORT:
	err = catch(ob = new(HTTP_OB));
	if( err ) {
	    write(HTTP_VERSION + " 503 Service Unavailable" CRLF CRLF ":P");
	    return 0;
	}
	return ob;
    }
}

private mixed
compile_object(string file)
{
    object daemon;
    mixed err;

    /* �Φw�����覡�M��éI�s VIRTUAL_D */
    err = catch(daemon = load_object(VIRTUAL_D));

    if( err || !objectp(daemon) ) return 0;
    return daemon->compile_object(file);
}

private void
crash(string error, object command_giver, object current_object)
{
    efun::shout("�t�ή֤ߵo�X�@�n�G�s�G�z ....\n");
    efun::shout("�t�ή֤ߧi�D�A�R�n����F�M�ۤv�O���a�T\n");
    log_file("static/CRASHES", sprintf("[%s] %s\n", ctime(time()), error) );
    if (command_giver)
	log_file("static/CRASHES", sprintf("  this_player: %O\n", command_giver));
    if (current_object)
        log_file("static/CRASHES", sprintf("  this_object: %O\n", current_object));
}

static string *
read_config(string file)
{
    string str;

    str = read_file(file);
    if (!str) return ({});

    return filter( explode(str, "\n"), (: strlen($1) && ($1[0] != '#') :));
}

static string *
epilog(int load_empty)
{
    return read_config(CONFIG_DIR + "preload");
}

static void
preload(string file)
{
    string err;

    write("Preloading : " + file );
    err = catch(load_object(file));
    if( err ) log_file("preload.log",
        sprintf("[%s] %s: %s", ctime(time()), file, err) );
}

private int
save_ed_setup(object who, int code)
{
    return write_file(user_path(getuid(who)) + ".edrc",
	save_variable(code), 1);
}

private int
retrieve_ed_setup(object who)
{
    string val;
  
    val = read_file(user_path(getuid(who)) + ".edrc");
    return stringp(val) ? (int)restore_variable(val) : 0; 
}

private void
destruct_env_of(object ob)
{
    if (!interactive(ob)) return;
    tell_object(ob, "�A�Ҧs�b���Ŷ��Q�����F�C\n");
    ob->move(VOID_OB);
}

static string
make_path_absolute(string file)
{
    return resolve_path((string)this_player()->query("cwd"), file);
}

static string
get_save_file_name(string fname)
{
    return fname + "." + time();
}

static string
get_root_uid()
{
   return ROOT_UID;
}

static string
get_bb_uid()
{
   return BACKBONE_UID;
}

static string
creator_file(string str)
{
    object ob;

    catch(ob = load_object(SIMUL_EFUN_OB));
    return ob ? (string)ob->creator_file(str) : "NONAME";
}

string
object_name(object ob)
{
    if( !objectp(ob) ) return 0;
    return getuid(ob);
}

string
standard_trace(mapping error)
{
    int i, s;
    string res = "";

    /* keep track of number of errors per object...if you're into that */
    res += sprintf("����ɬq���~�G%s����G%O:%s\n�{���G%s:%i\n",
	error["error"],
	error["object"],
	error["program"],
	error["file"],
	error["line"]);

    res += "��ƩI�s�^��:\n";
    foreach(mapping trace in error["trace"]) {
	res += sprintf("%-25O %-20s %s:%i\n",
	    trace["object"],
	    trace["function"],
	    trace["program"]==trace["file"] ? trace["program"]
		: trace["file"] + "(" + trace["program"] + ")",
	    trace["line"] );
    }
    res += "\n";

    return res;
}

string
error_handler( mapping error, int caught )
{
    string report;
    object player;

    if( caught ) return 0;

    report = standard_trace(error);

    player = this_player();

    if( objectp(player) && interactive(player) ) efun::write(report);

    /* �Ǧ^���r��|�Q�����b debug.log */
    return report;
}

static void
log_error(string file, string message)
{
    string name, home;
   
    if( find_object(SIMUL_EFUN_OB) )
        name = file_owner(file);

    if (name) home = user_path(name);
    else home = LOG_DIR;

    if(this_player(1)) efun::write("�sĶ�ɬq���~�R" + message );
    
    efun::write_file(home + "log", sprintf("[%s]%s", ctime(time())[4..18], message));
}

static int
valid_override( string file, string name )
{
    if (file == SIMUL_EFUN_OB || file==MASTER_OB) return 1;

    if( file[0..15] == "/adm/simul_efun/" ) return 1;

    // Must use the move() defined in F_MOVE.
    if(((name == "move_object") || (name == "destruct")) && (file != F_MOVE)) {
        log_error("override", sprintf("%s attempts to override %s(), denied.\n", file, name));
        return 0;
    }

    //  may also wish to protect shutdown, snoop, and exec.
    return 1;
}

static int
valid_seteuid( object ob, string str )
{
    return (int)SECURITY_D->valid_seteuid( ob, str );
}

static int
valid_socket( object eff_user, string fun, mixed *info )
{
    return 1;
}

static int
valid_object( object ob )
{
    return (!clonep(ob)) || inherits(F_MOVE, ob);
}

// valid_save_binary: controls whether an object can save a binary
//   image of itself to the specified "save binaries directory"
//   (see config file)
static int
valid_save_binary( string filename ) { return 1; }

// valid_write: write privileges; called with the file name, the object
//   initiating the call, and the function by which they called it. 
static int
valid_write( string file, mixed user, string func )
{
    object ob;

    if( !catch(ob = load_object(SECURITY_D))
    &&    objectp(ob) )
        return (int)SECURITY_D->valid_write(file, user, func);

    return 0;
}

// valid_read: read privileges; called exactly the same as valid_write()
static int
valid_read( string file, mixed user, string func )
{
    object ob;

    if( !catch(ob = load_object(SECURITY_D))
    &&    objectp(ob) )
        return (int)SECURITY_D->valid_read(file, user, func);

    return 1;
}

static int
valid_bind(object binder, object old_owner, object new_owner)
{
    // Root can bind anything to anything
    if( geteuid(binder)==ROOT_UID ) return 1;

    // Root's function can be bind to anyone (down-grading)
    if( old_owner && geteuid(old_owner)==ROOT_UID ) return 1;

    // Any function can be bind to binder itself
    if( binder==new_owner ) return 1;

    if( !userp(new_owner) && clonep(new_owner) ) return 1;

    log_file("bind", sprintf("%O attempts to bind %O's function to %O\n",
        binder, old_owner, new_owner) );
    return 0;
}
