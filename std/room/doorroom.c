// room.c

#pragma save_binary

#include <ansi.h>
#include <dbase.h>
#include <room.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

static mapping doors;
static mapping guards;

int receive_object(object ob, int from_inventory) { return 1; }

// clean_up()
//
// We override the clean_up() here to provide that the room won't got
// destructed when there is NPC(s) created in this room was wandering
// outside, and create another copy of the same NPC when next time
// the room is loaded.

int clean_up(int inherit_flag)
{
	mapping items;
	string file;
	object ob;

	// Don't clean up if any NPCs we created were wandering somewhere.
	// This may introduce a potential deadlock that when room-A holds
	// an NPC from room-B while room-B holds another NPC from room-A.
	// Anyway, such condition is really rare and its only fault is leaving
	// the room not cleaned up when deadlock exists. So, we just merely
	// ignore it :P                                 - Annihilator

	if( mapp(items = query_temp("objects")) )
		foreach(file, ob in items) {
			if( objectp(ob)
			&&	ob->is_character()
			&&	environment(ob)!=this_object() )
				return 1;
		}

	return ::clean_up(inherit_flag);
}

void remove()
{
	mapping items;
	string file;
	object ob;
	int cnt = 0;

	if( !mapp(items = query_temp("objects")) ) return;

	// Destroy wandering NPC created by this room as well.
	foreach(file, ob in items) {
		if( objectp(ob)
		&&	ob->is_character()
		&&	environment(ob)!=this_object() ) {
			message("vision", "�@�}�j�P���{�����M�X�{�M�]�S�F" + ob->name() + "�C\n",
				environment(ob));
			destruct(ob);
			cnt++;
		}
	}
	if( cnt && this_player() )
		write("WARNNING: " + cnt + " wandering NPC(s) created by this room are forced destructed.\n");
}

object make_inventory(string file)
{
	object ob;

	ob = new(file);

	// Support for uniqueness
	if( ob->violate_unique() ) ob = ob->create_replica();
	if( !ob ) return 0;

	ob->move(this_object());

	return ob;
}

void reset()
{
	mapping ob_list, ob;
	string ob_kind;
	int amount;
	object obj, *inv;

	inv = all_inventory(this_object());

	ob_list = query("objects");
	if( mapp(ob_list) ) {
	
		if( !mapp(ob = query_temp("objects")) )
			ob = allocate_mapping(sizeof(ob_list));
		inv -= values(ob);

		foreach(ob_kind, amount in ob_list) {
			if( amount==1 ) {
				if( !objectp(ob[ob_kind]) ) ob[ob_kind] = make_inventory(ob_kind);
			} else {
				for(int i=0; i<amount; i++)
					if( !objectp(ob[ob_kind + " " + i ]) )
						ob[ob_kind + " " + i] = make_inventory(ob_kind);
			}
		}
		set_temp("objects", ob);
	}
	foreach(obj in inv) if( interactive(obj) ) return;
	foreach(obj in inv) if(!clonep(obj)) return;
	foreach(obj in inv) destruct(obj);

	// Reset resource value
	if( mapp(query("resource")) )
		set_temp("resource", copy(query("resource")) );
}

// Redirect item_desc of the door to this function in default.
string look_door(string dir)
{
	if( !mapp(doors) || undefinedp(doors[dir]) || doors[dir]["status"]&DOOR_HIDDEN)
		return "�A�n�ݤ���S\n";
	if( doors[dir]["status"] & DOOR_CLOSED )
		return "�o��" + doors[dir]["name"] + "�O���۪��C\n";
	else
		return 0;
//		return "�o��" + doors[dir]["name"] + "�O�}�۪��C\n";
}

varargs int open_door(string dir, int from_other_side)
{
	mapping exits;
	object ob;

	if( !mapp(doors) || undefinedp(doors[dir])
	|| (!from_other_side && doors[dir]["status"]&DOOR_HIDDEN))
		return notify_fail("�o�Ӥ�V�S�����C\n");

	if( !from_other_side && !(doors[dir]["status"] & DOOR_CLOSED) )
		return notify_fail( doors[dir]["name"] + "�w�g�O�}�۪��F�C\n");

	if( !from_other_side && doors[dir]["status"] & DOOR_LOCKED )
		return notify_fail( doors[dir]["name"] + "�O��۪��C\n");

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: open_door: attempt to open a door with out an exit.\n");

	if( from_other_side ) {
		message("vision", "���H�q�t�@��N" + doors[dir]["name"] + "���}�F�C\n", this_object());
	} else if( objectp(ob = find_object(exits[dir])) ) {
		if( !ob->open_door(doors[dir]["other_side_dir"], 1) )
			return notify_fail("�����t�@��n���d��F�C\n");
	}

	doors[dir]["status"] &= (~DOOR_CLOSED);
	return 1;
}

varargs int close_door(string dir, int from_other_side)
{
	mapping exits;
	object ob;

	if( !mapp(doors) || undefinedp(doors[dir]
	||	(!from_other_side && doors[dir]["status"]&DOOR_HIDDEN)) )
		return notify_fail("�o�Ӥ�V�S�����C\n");

	if( (doors[dir]["status"] & DOOR_CLOSED) )
		return notify_fail( doors[dir]["name"] + "�w�g�O���۪��F�C\n");

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: close_door: attempt to open a door with out an exit.\n");

	if( from_other_side )
		message("vision", "���H�q�t�@��N" + doors[dir]["name"] + "���W�F�C\n", this_object());
	else if( objectp(ob = find_object(exits[dir])) ) {
		if( !ob->close_door(doors[dir]["other_side_dir"], 1) ) return 0;
	}

	doors[dir]["status"] |= DOOR_CLOSED;
	return 1;
}


varargs int lock_door(string dir, string key, int from_other_side)
{
	object ob;
	mapping exits;

	if( !mapp(doors) || undefinedp(doors[dir]) )
		return notify_fail("�o�Ӥ�V�S�����C\n");
	if( !doors[dir]["lock"] ) return notify_fail("�o��"+ doors[dir]["name"] 
		+ "�W���S����C\n");
	if( doors[dir]["lock"] != key )
		return notify_fail("�A���_�ͤ���C\n");

	if( doors[dir]["status"] & DOOR_LOCKED ) 
		return notify_fail(doors[dir]["name"] + "�w�g��W�F�C\n");

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: lock_door: attempt to lock a door with out an exit.\n");

	if( from_other_side )
		message("vision", "�Ať��" + doors[dir]["name"] + "�o�X�u�ءv�a�@�n�C\n",
		this_object());
	else if( objectp(ob = find_object(exits[dir])) )
		if( !ob->lock_door(doors[dir]["other_side_dir"], key, 1) ) return 0;

	doors[dir]["status"] |= DOOR_LOCKED;
	return 1;
}

varargs int unlock_door(string dir, string key, int from_other_side)
{
	object ob;
	mapping exits;

	if( !mapp(doors) || undefinedp(doors[dir]) )
		return notify_fail("�o�Ӥ�V�S�����C\n");
	if( !doors[dir]["lock"] ) return notify_fail("�o��"+ doors[dir]["name"] 
		+ "�W���S����C\n");
	if( doors[dir]["lock"] != key )
		return notify_fail("�A���_�ͤ���C\n");

	if( !(doors[dir]["status"] & DOOR_LOCKED) ) 
		return notify_fail(doors[dir]["name"] + "�èS���W��C\n");

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: unlock_door: attempt to unlock a door with out an exit.\n");

	if( from_other_side )
		message("vision", "�Ať��" + doors[dir]["name"] + "�o�X�u�ءv�a�@�n�C\n",
		this_object());
	else if( objectp(ob = find_object(exits[dir])) )
		if( !ob->unlock_door(doors[dir]["other_side_dir"], key, 1) ) return 0;

	doors[dir]["status"] &= ~DOOR_LOCKED;
	return 1;
}

#define CONSIST_DOOR_STATUS (DOOR_CLOSED|DOOR_LOCKED)
int check_door(string dir, mapping door)
{
	// If we have no responding door, assume it is correct.
	if( !mapp(doors) || undefinedp(doors[dir]) ) return 1;

	door["status"] &= (~CONSIST_DOOR_STATUS);
	door["status"] |= (doors[dir]["status"] & CONSIST_DOOR_STATUS);
	return 1;
}

varargs void create_door(string dir, mixed data, string other_side_dir, int status)
{
	mapping d, item_desc;
	object ob;
	string exit;

	if( !stringp(exit = query("exits/" + dir)) )
		error("Room: create_door: attempt to create a door without exit.\n");

	// String mode.
	if( stringp(data) ) {
		d = allocate_mapping(4);
		d["name"] = data;
		d["id"] = ({ dir, data, "door" });
		d["other_side_dir"] = other_side_dir;
		d["status"] = status;
	// Compelete specification mode.
	} else if( mapp(data) )
		d = data;
	else
		error("Create_door: Invalid door data, string or mapping expected.\n");

	set("detail/" + dir, (: look_door, dir :) );

	if( objectp(ob = find_object(exit)) ) {
		if( !ob->check_door(other_side_dir, d) )
			return;
	}

	// Add the door.
	if( !mapp(doors) ) doors = ([ dir: d ]);
	else doors[dir] = d;
}

mapping query_doors() { return doors; }

mixed query_door(string dir, string prop)
{
	if( !mapp(doors) || undefinedp(doors[dir]) ) return 0;
	else return doors[dir][prop];
}

mixed set_door(string dir, string prop, mixed data)
{
	if( !mapp(doors) || undefinedp(doors[dir]) ) return 0;
	else return doors[dir][prop] = data;
}

int valid_leave(object me, string dir)
{
	int i, move_skill;
	string my_name;
	object guard, *ob;

	if( mapp(doors) && !undefinedp(doors[dir]) ) {
		if( doors[dir]["status"] & DOOR_CLOSED ) {
			if( doors[dir]["status"]& DOOR_HIDDEN ) return notify_fail("�o�Ӥ�V�S���X���C\n");
			return notify_fail("�A��������" + doors[dir]["name"] + "���}�T\n");
		}
		// if ( door[dir]["status"] & DOOR_HAS_TRAP ) ....
	}
	return 1;
}

varargs int do_look(object me, string arg)
{
	int i;
	object *inv, ob;
	mapping exits;
	string str, *dirs;

	// Look specific object in the room.
	if( arg ) {
		if( str = query("detail/" + arg) ) {
			write(str);
			return 1;
		}
		if( strsrch(query("long"), arg) >= 0 )
			return notify_fail("�A�ݤ��X�o�̪�" + arg + "������S�O���C\n");
		return notify_fail("�A�n�ݤ���S\n");
	}

	if( previous_object() && previous_object()->query("option/BRIEF_ROOM") )
		str = query("short") + "�A";
	else
		str = sprintf( "%s - %s\n    %s%s    ",
			query("short"),
			wizardp(me)? file_name(this_object()) : "",
			query("long"),
			query("outdoors") ? NATURE_D->outdoor_room_description() : "" );

	if( mapp(exits = query("exits")) )
		dirs = keys(exits);
	
	// Check for exits with door.
	if( mapp(doors) )
		dirs = filter(dirs, (: undefinedp(doors[$1]) || (doors[$1]["status"] & DOOR_CLOSED)==0 :));

	if( sizeof(dirs)==0 )
		str += "�o�̨S��������㪺�X���C\n";
	else if( sizeof(dirs)==1 )
		str += "�o�̰ߤ@���X�f�O " BOLD + dirs[0] + NOR "�C\n";
	else
		str += sprintf("�o�̩��㪺�X�f�O " BOLD "%s" NOR " �M " BOLD "%s" NOR "�C\n",
			implode(dirs[0..<2], "�B"), dirs[<1]);

	inv = all_inventory(this_object()) - ({ me });
	for(i=0; i<sizeof(inv); i++) {
		if( !inv[i]->visible(me) ) continue;
		str = sprintf("%s  %s\n", str, inv[i]->short() );
	}

	write(str);
	return 1;
}

void init()
{
	int explore_id;
	if( !undefinedp(explore_id = query("site_explore")) ) {
		if( !this_player()->recognize(explore_id, 1) ) {
			this_player()->gain_score("survive", 100);
			this_player()->gain_score("explorer fame", 1);
		}
	}
}

void setup()
{
	seteuid(getuid());
	this_object()->reset();
}
