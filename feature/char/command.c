/*  command.c

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
#include <dbase.h>
#include <origin.h>
#include <login.h>

/* ���O�j�M���|�C */
static string *path = ({});

string
find_command(string verb)
{
    return (string)COMMAND_D->find_command(verb, path);
}

static nomask int
command_hook(string arg)
{
    string verb, file;

#ifdef ENABLE_BENCHMARK
    int mem, utime, stime;
    mapping info;

    mem = memory_info();
    info = rusage();
    utime = info["utime"];
    stime = info["stime"];
#endif

    verb = query_verb();

    /* ���ի��O */
    if( stringp(file = find_command(verb)) 
    &&	call_other(file, "main", this_object(), arg));

    /* ���ձ������O */
    else if( EMOTE_D->do_emote( this_object(), verb, arg ) );

    /* �����W�D���O */
    else if( CHANNEL_D->do_channel( this_object(), verb, arg ) );

    /* ���� go */
    else if( (verb != "go") && environment()
    &&	stringp(environment()->query("exits/" + verb))
    &&	GO_CMD->main(this_object(), verb) );

    else return 0;

#ifdef ENABLE_BENCHMARK
    info = rusage();
    PROFILE_D->log_command(verb, memory_info() - mem, info["stime"] - stime,
	info["utime"] - utime);
#endif

    return 1;
}

static void
set_path(string *p)
{
    path = p;
}

/*  add_path()
 *
 *  �o�Ө�ƥΨӴ��Ѥ@�ӼW�[���O�j�M���|�������C
 */
nomask void
add_path(string p)
{
    if( previous_object() && (geteuid(previous_object())!=ROOT_UID) )
	error("Permission denied\n");

    if( arrayp(path) && (member_array(p, path) < 0) ) {
	path += ({ p });
	/* �O�@�S�v�ϥΪ̪��]�p�G���O�j�M���|���ܮɡA�L�X�T�����ϥΪ̪��D�C */
	if( wizardp(this_object()) )
	    receive(HIR "�s�W���O�j�M���|�G" NOR + p + "\n");
    }
}

mixed *
query_commands() { return commands(); }

int
force_me(string cmd)
{
    if( geteuid(previous_object()) != ROOT_UID )
	error("Permission denied\n");

    return command( userp(this_object()) ? this_object()->process_input(cmd) : cmd );
}

static void
enable_player()
{
    /* �]�w�ͪ��W�� */
    if( stringp(query("id")) ) set_living_name(query("id"));
    else if( stringp(query("name")) ) set_living_name(query("name"));
    else set_living_name(getuid());

    /* �s�����O�B�z��� */
    enable_commands();
    delete("disable_type");
}

void
init_command()
{
    if( !userp(this_object()) )
        set_path(NPC_PATH);
    else
	switch( wizhood(this_object()) )
	{
	case "(admin)":		set_path(ADM_PATH); enable_wizard(); break;
	case "(arch)":		set_path(ARC_PATH); enable_wizard(); break;
	case "(wizard)":	set_path(WIZ_PATH); enable_wizard(); break;
	case "(apprentice)":	set_path(APR_PATH); enable_wizard(); break;
	case "(immortal)":	set_path(IMM_PATH); break;
	default:		set_path(PLR_PATH); break;
	}

    add_action("command_hook", "", 1);
    add_action("cmd_quit", "quit");

    if( wizardp(this_object()) ) add_action("cmd_update", "update");
}

// cmd_quit()
//
// �o�ӬO�ΨӦb�U�@ quit ���O�a���ɡA�ƥΪ� quit�C
private int
cmd_quit(string arg)
{
    if( !catch(call_other(QUIT_CMD, "main", this_object(), arg)) ) {
	// �Y���\�Athis_object() �w�g�Q destruct �F�A�ߧY��^�C
	return 1;
    }

#ifdef SAVE_USER
    this_object()->save();
#endif
    destruct(this_object());
}

private int
cmd_update(string arg)
{
    if( !wizardp(this_object()) ) return 0;
    return call_other("/cmds/wiz/update", "main", this_object(), arg);
}

static void
disable_player(string type)
{
    if( origin()==ORIGIN_CALL_OTHER
    &&	geteuid(previous_object())!=ROOT_UID
    &&	previous_object()!=this_object())
	return;

    set("disable_type", type);
    disable_commands();
}

