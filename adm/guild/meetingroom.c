#include <ansi.h>
#include <command.h>

inherit ROOM;

string filename;

void create()
{
        set("short", "�|ĳ�U");
        set("long", @LONG
�o�̬O�F�诫�Ъ��|ĳ�U, �����򭫤j�Ʊ��n�Q�׳��|�b�o�i��
�C��Ϊ��ж�, �զ⪺��, �Q�۬��⪺�a��, �ж��������^�r�ۤ@��
����������, ���u�N�q���۴��o�X��, �ӫG�F��өж�, ���G�o����
���C�a��������B�ۤ@�����⪺�ɪO, �O�l�W��F�Ǧr�C�n��i�H�^
��Ův���|�C
LONG
        );

        set("exits", ([ /* sizeof() == 1 */
                "south" : "/adm/guild/guildhall"
        ]));

	set("detail", ([ /* sizeof() == 1 */
		"�ɪO" : "�@���ƯB�b�b�Ť������A�ɪO, �W����F�Ǧr:

�|ĳ�O������k:
start <filename> :	�}�l�O���|ĳ�L�{, filename �O�|ĳ�O�����ɦW�C
over :			����O���|ĳ�L�{�C

",
	]));
	setup();
	load_object("/daemon/board/wizard_talk");
}

void init()
{
	add_action("say", ({"say", "'"}) );
	add_action("start", "start");
	add_action("over", "over");
}

int start(string str)
{
	if( !wizardp(this_player()) )
	return notify_fail("�A�S���v�O�}�|ĳ�C\n");

	if( !str )
	return notify_fail("�A�n�N�|ĳ�O���g�b������??\n");

	if ( (int)query("meeting_trigger") != 0 )
	return notify_fail("�ثe���b�}�|���C\n");

	set("meeting_trigger", 1);
	message_vision(HIW"\n$N�ť��{�b�|ĳ�����}�l�C\n\n"NOR, this_player());
	filename = str;
	log_file(filename, sprintf("[%s] %s (%s) �}�ҷ|ĳ�C\n",
		ctime(time()), this_player()->name(1), geteuid(this_player())));
	return 1;
}

int say(string msg)
{
	if( !msg ) return 0;
	else
	SAY_CMD->main(this_player(), msg);
	if ((int)query("meeting_trigger") == 1)
	log_file(filename,
	sprintf("%s���D�R" + msg + "\n",this_player()->name(1)) );
	return 1;
}

int over()
{
	if( !wizardp(this_player()) )
        return notify_fail("�A�S���v�O�����|ĳ�C\n");

	delete("meeting_trigger");
	log_file(filename, sprintf("[%s] %s (%s) �����|ĳ�C\n",
		ctime(time()), this_player()->name(1), geteuid(this_player())));
	message_vision(HIW"\n$N�ť��|ĳ�����C\n\n"NOR, this_player());
	return 1;
}
