// Room: /d/snow/sstreet1.c

inherit ROOM;

void create()
{
	set("short", "��D");
	set("long", @LONG
�o�̬O���F��n��s����~����D�M���䦳�@���f�̡M�F��h�O�@
�a���f�Q�M��D���_�q���s���n��M���n��L�@�ӯ�ץX��~�C
LONG
	);
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 3 */
		"south" : __DIR__"sgate",
		"north" : __DIR__"square_s",
		"west" : __DIR__"store",
		"east" : __DIR__"bazar",
]));

	setup();
	replace_program(ROOM);
}
