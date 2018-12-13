// Room: /d/snow/ruin1.c

#include <localtime.h>

inherit ROOM;

int flag = 0;

void create()
{
	set("short", "�}�¤j�v");
	set("long", @LONG
�o�̬O�@���}�¤j�v���e�|�M�j�U�w�g�Y��F�@�b�M�J�ª��٬W��
��F�A���h���M�x�|�������O�͡M�ݨӤw�g�ܤ[�S���H��F�M�ڻ��o��
�ߤW������X�{�M���O�ˤ]�q�Sť���L���H�Q�`�M�]�����񪺩~�����M
�ӱ`�ͬ��M����i�H�g�Ѥj�v�������^���W�C
LONG
	);
	set("detail", ([ /* sizeof() == 2 */
		"����" : "�o�̪�����w�g�������θy�����פF�M�A���M�o�{�n�䪺���O����
��F��o�X���ݪ��{���M���L�]���i��O�A����ı�C
",
		"�٬W" : "�q�٬W�J�ª�����ӬݡM�o�y�j�v���D�H�j���O�]�����a�����Y�~
���}���a�C
",
]));
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 2 */
		"west" : __DIR__"lane1",
		"east" : __DIR__"egate",
]));

	setup();
}

void init()
{
	add_action("do_climb", "climb");
	add_action("do_search", "search");
}

int do_climb(string arg)
{
	if( arg != "�٬W" ) return 0;

	message_vision("$N�p���l�l�a���L�~�򪺼٬W�i�J�j�U�C\n", this_player());
	this_player()->move(__DIR__"ruin2");
	message("vision", this_player()->name() + "�q�~��٬W���t�@�Y���F�L�ӡC\n",
		environment(this_player()), this_player());
	return 1;
}

int do_search(string arg)
{
	mixed t;
	object ob;

	if( arg != "����" ) return 0;

	t = NATURE_D->game_time(1);
	// Can only be found during 11:00 to 14:00
	if( flag || (t[LT_HOUR] < 10) || (t[LT_HOUR] > 13) ) {
		message_vision("$N�b�����O�̧�ӧ�h�M���O����]�S�����C\n", this_player());
		return 1;
	}
	flag = 1;
	ob = new(__DIR__"npc/obj/hairpin");
	ob->move(this_player());
	message_vision("$N�b���O�̧�ӧ�h�M���G�o�{�F�@��v¯�T\n", this_player());
	return 1;
}

void reset()
{
	flag = 0;
	::reset();
}
