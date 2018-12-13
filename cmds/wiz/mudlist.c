/*  mudlist.c - list muds that are in contact with us over intermud

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <intermud.h>

inherit F_CLEAN_UP;

#define SYNTAX	"���O�榡�Rmudlist [<Mud �W��>]\n"

private void create() { seteuid(getuid()); }

int
main(object me, string arg)
{
    mapping mudlist;
    mixed *muds;
    string output;
    string mud;
    int list_all = 0;

    if( !find_object(INTERMUD_D) )
        return notify_fail("�������F�èS���Q���J�A�Х��N�������F���J�C\n");

    mudlist = (mapping)INTERMUD_D->query_mudlist();

    if( !mapp(mudlist) )
        return notify_fail( MUD_NAME + "�ثe�|���M��L Mud ���o�pô�C\n");

    muds = sort_array( keys(mudlist), 1);

    if( arg ) {
	string* args, mud_name;

	args = explode(arg, " ") - ({ "" });

	foreach(string name in args)
	{
	    string prop, str, msg;
	    mapping mudinfo;

	    if( mud_name && mapp(mudinfo)
	    &&	sscanf(name, "%s=%s", prop, str)==2 ) {
		write("�]�w " + mud_name + " �����a�ݩʡG" + name + "\n");
		INTERMUD_D->set_mudinfo(mud_name, ([ prop : str ]) );
		continue;
	    }

	    if( sscanf(name, "%s->%s", prop, str)==2 ) {
		INTERMUD_D->set_mud_alias(prop, str);
		name = prop;
	    }

	    mud_name = name; // = htonn(name);
            if(!mapp( mudinfo = INTERMUD_D->query_mudinfo(name) )) {
                write(MUD_NAME + "�èS���M \"" + name + "\" ���o�pô�C\n");
		continue;
            }

	    msg = "";
	    foreach(prop, str in mudinfo)
		msg += sprintf("  %15s: %O\n", prop, str);
	    write("���� " + name + " ����T�R\n" + msg);
        }
	if( mud_name ) return 1;
    }

    output = "";

    // Loop through mud list and store one by one
    foreach(mud in muds)
    {
//	if( !list_all && mudlist[mud]["MUDLIB"] != "Eastern Stories" )
//	    continue;
	output += sprintf("%-20s %-10s %s (%s)\n",
		mud,
		mudlist[mud]["ALIAS"] ? mudlist[mud]["ALIAS"] : "",
		mudlist[mud]["NAME"],
		mudlist[mud]["MUDLIB"]);
    }

    //    Display dumped mudlist output through user's more pager
    this_player()->start_more( output );

    return 1;
}

int help()
{
    write( @HELP
���O�榡�Gmudlist [-a] [<MUD IP:PORT>|<�N��>] {�ݩ�=�r��}
	  mudlist <�N��>-><MUD IP:PORT>

�o�ӫ��O���A�C�X�ثe�z�L intermud ��w���o�pô����L Mud�C

�p�G�[�W -a �ﶵ�A�Ҧ��� Mud ���|�Q�C�X�F�_�h�u���ϥ� es2 mudlib �� Mud
�|�Q�C�X�C

�A�i�H���w��@�� MUD �W�١Amudlist �|�C�X�� MUD ��������T�C
mudlist �i�H�b���a�ݭק��L MUD ���ݩʡA�嫬���γ~�O�]�w�@�� MUD ������s
�X�p�G

> mudlist xajh ENCODING=GB

�|�N xajh(���Ʀ���) �o�Өϥ� GB ���X�� MUD �� ENCODING �]�w�� GB�A�]������
�֨ϥ��ª� ES2 mudlib ���j�� MUD �èS���]�w ENCODING ���ݩʡA�ҥH�p�G�A�ݨ�
���� MUD �e�L�Ӫ� es �W�D�T���O�ýX�A�i�H�յۥΤW�������O�]�w�C

�o�ǳ]�w�u���b���a�ݦ��ġA�èS����k���ܹ�誺�]�w�A�]���� intermud ��s��
MUD ���ݩʮɡA�A�i�ॲ�����s�]�w�C�y�����~����k�O�g�H����誺�޲z�̡A�ХL
�̥��T�]�w�e�X�Ӫ� ENCODING �ݩʡC
HELP
    );
    return 1;
}

