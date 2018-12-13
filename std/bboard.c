/*  bboard.c - the buuletin board object

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

#define	BOARD_CAPACITY	query("capacity")
#define	NO_PLAYER_POST	query("NO_PLAYER_POST")

inherit ITEM;
inherit F_SAVE;

void setup()
{
    string loc;

    seteuid(getuid());
    ::setup();
    if( stringp(loc = query("location")) )
	move(loc);
    set("no_get", 1);
    restore();
}

void init()
{
    add_action("do_post", "post");
    add_action("do_read", "read");
    add_action("do_discard", "discard");
    add_action("do_save_article", "save");
    add_action("do_followup", "followup");
}

string query_save_file()
{
    string id;

    if( !stringp(id = query("board_id")) ) return 0;
    return DATA_DIR + "board/" + id + __SAVE_EXTENSION__;
}

string short()
{
    mapping *notes;
    int i, unread, last_read_time;

    notes = query("notes");
    if( !pointerp(notes) || !sizeof(notes) )
	return ::short() + " [ �S������d�� ]";

    if( this_player() && this_player()->link() ) {
	last_read_time = (int)this_player()->link()->query("board_last_read/" + (string)query("board_id"));
	for(unread = 0, i=sizeof(notes)-1; i>=0; i--, unread ++)
	    if( notes[i]["time"] <= last_read_time ) break;
    }
    if( unread )
	return sprintf("%s [ %d �i�d���M%d �i��Ū ]", ::short(), sizeof(notes), unread);
    else
	return sprintf("%s [ %d �i�d�� ]", ::short(), sizeof(notes));
}

string long()
{
    mapping *notes;
    int i, last_time_read;
    string msg;

    notes = query("notes");
    msg = query("long");
    if( !msg ) msg = "";
    if( !pointerp(notes) || !sizeof(notes) )
	return msg += query("name") + "�ϥΤ�k�Ш� help board�C\t�e�q�� (" +BOARD_CAPACITY+ ") �g\n";

    last_time_read = this_player()->link()->query("board_last_read/" + (string)query("board_id"));
    for(i=0; i<sizeof(notes); i++)
	msg += sprintf("%s[%2d]" NOR "  %-34s %+22s - %s\n",
	    ( notes[i]["time"] > last_time_read ? HIY: ""),
	    i+1,
	    notes[i]["title"],
	    notes[i]["author"],
	    ctime(notes[i]["time"])[0..9]
	);
    return msg += "\n=== " + query("name") + "�ϥΤ�k�Ш� help board�A�d�����e�q�G" +BOARD_CAPACITY+ " �g ===\n";
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void done_post(object me, mapping note, string text)
{
    mapping *notes;
    string sig;

    if( stringp(sig = me->link()->query("signature")) )
	text += "--\n" + sig;   // �[ -- �n�b followup �i�H���D
    note["msg"] = text;
    notes = query("notes");
    if( !pointerp(notes) || !sizeof(notes) )
	notes = ({ note });
    else
	notes += ({ note });

    // Truncate the notes if maximum capacity exceeded.
    if( sizeof(notes) > BOARD_CAPACITY )
	notes = notes[BOARD_CAPACITY / 4 .. BOARD_CAPACITY];

    set("notes", notes);
    tell_object(me, "�d�������C\n");

    save();
    return;
}

int do_post(string arg)
{
    mapping note;
    if(!arg) return notify_fail("�d���Ы��w�@�Ӽ��D�C\n");

    // add by ueiren ..
    if ( NO_PLAYER_POST && (!wizardp(this_player())))
    return notify_fail("���a���i�b�����G��d���C\n");

    if( strlen(arg) > 40 )
	return notify_fail("�z�����D�Ӫ��F�M���@�� 40 �Ӧr���H�����a�C\n");
        
    note = allocate_mapping(4);
    note["title"] = arg;
    note["author"] = this_player()->name() + "(" +this_player()->query("id") + ")";
    note["time"] = time();
    this_player()->edit( (: done_post, this_player(), note :) );
    return 1;
}

int do_read(string arg)
{
    int num,tmp;
    mapping *notes, last_read_time;
    string myid;

    last_read_time = this_player()->link()->query("board_last_read");
    myid = query("board_id");
    notes = query("notes");

    if( !pointerp(notes) || !sizeof(notes) )
	return notify_fail("�d���O�W�ثe�S������d���C\n");

    if( !arg ) return notify_fail("���O�榡�Rread <�d���s��>|new|next\n");
    if( arg=="new" || arg=="next" ) {
	if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
	    num = 1;
	else
	    for(num = 1; num<=sizeof(notes); num++)
		if( notes[num-1]["time"] > last_read_time[myid] ) break;
                        
    } else if( !sscanf(arg, "%d", num) )
	return notify_fail("�A�nŪ�ĴX�i�d���S\n");

    if( num < 1 || num > sizeof(notes) )
	return notify_fail("�S���o�i�d���C\n");
    num--;
    this_player()->start_more( sprintf("[%2d]  %-34s %+26s%s%s%s\n",
	num + 1,
	notes[num]["title"],
	notes[num]["author"],
	"(" + ctime(notes[num]["time"])[0..9] + ")",
	"\n---------------------------------------------------------------------------\n",
	notes[num]["msg"]));

    // Keep track which post we were reading last time.
    if( !mapp(last_read_time) ) {
	this_player()->link()->set("board_last_read", ([ myid: notes[num]["time"] ]) );
    }
    else 
	if( undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid] )
	    last_read_time[myid] = notes[num]["time"];

    return 1;
}


int do_discard(string arg)
{
    mapping *notes;
    int num;

    if( !arg || sscanf(arg, "%d", num)!=1 )
	return notify_fail("���O�榡�Rdiscard <�d���s��>\n");
    notes = query("notes");
    if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
	return notify_fail("�S���o�i�d���C\n");
    num--;
    if( notes[num]["author"] != (string) this_player(1)->query("name")+ "(" + this_player(1)->query("id") + ")"
    &&	wiz_level(this_player(1)) < 4 )
	return notify_fail("�o�ӯd�����O�A�g���C\n");

    notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
    set("notes", notes);
    save();
    write("�R���� " + (num+1) + " ���d��....Ok�C\n");
    return 1;
}

int do_save_article(string arg)
{
    int num;
    string file;
    mapping *notes;

    if( !wizardp(this_player()) ) return 0;
    if( !arg || sscanf(arg, "article %d to %s", num, file)!=2 ) return 0;
        
    if( !arrayp(notes = query("notes"))
    ||	num<1
    ||	num>sizeof(notes) )
	return notify_fail("�S���o�i�d���C\n");
    num--;
    file = resolve_path(this_player()->query("cwd"), file);
    if( write_file(file, notes[num]["msg"]) )
	write("Ok.\n");
    else
	return notify_fail("�x�s���ѡC\n");
    return 1;
}

int do_followup(string str)
{
    mapping *notes, note;
    string *text, title;
    int i, num;
        
    // add by dragoon
    if ( NO_PLAYER_POST && (!wizardp(this_player())))
	return notify_fail("���a���i�b�����G��d���C\n");

    if( !str )
	return notify_fail("���O�榡�Rfollowup <�d���s��> [�s�����D]\n");

    if( sscanf(str, "%d %s", num, title) != 2 )
	if( sscanf(str, "%d", num) != 1 )
	    return notify_fail("�A�n�^�ĴX�g���d���S\n");
        
    notes = query("notes");
        
    if( num < 1 || num > sizeof(notes) )
	return notify_fail("�S���o�g�d���C\n");

    num--;
    if( !title ) title = "Re�R" + notes[num]["title"];
    note = allocate_mapping(4);
    note["title"]  = title;
    note["author"] = this_player()->query("name") + "(" + this_player()->query("id") + ")";
    note["time"]   = time();

    text = explode( notes[num]["msg"], "\n" );
    // title, num �o����ܼƮ��ӦA�Q��
    title = sprintf(GRN"> %s �b %s �d�U�o�g�d���R\n"NOR,
	notes[num]["author"],
	"(" + ctime(notes[num]["time"])[0..9] + ")" );

    num = sizeof(text);
    for( i=0; i<num; i++ ) 
    {
	// �Ŧ���L, �W�W�@�g���L
	if( text[i] == "" || strsrch(text[i], "> ") != -1)
	    continue;
	// ñ�W��, ����
	if( text[i][0..1] == "--" )
	    i=num;
	else title = title + GRN + "> " + text[i] + NOR + "\n";
    }
    note["msg"] = title;
    this_player()->edit( (: done_post, this_player(), note :), title );
    return 1;
}
