// Room: /d/snow/tree.c

inherit ROOM;

void create()
{
	set("short", "�_��W");
	set("long", @LONG
�A�{�b���b�@�襨�j���_��W�M�Z�K���K���k�o�A���ǵo�o�M�e��
�@�ڲʤj����K�W���H��ۤ@���Ԥl�C
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"down" : __DIR__"square",
]));
	set("objects", ([
		__DIR__"npc/child": 1
	]) );
	setup();
	replace_program(ROOM);
}
