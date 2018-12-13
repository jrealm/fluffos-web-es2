// Room: /d/snow/npath1.c

inherit ROOM;

void create()
{
	set("short", "�p��");
	set("long", @LONG
�o�̬O�@�����g�p���M����i�H�^�쳷�F���D�n��D�M�_��O�@
����a�M��a���Y�h�O�@����L�M���F�A�i�Hť��F�F�����n�M�����B
�i�H�樣�@���s�ˡC
LONG
	);
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 2 */
		"east" : __DIR__"npath2",
		"west" : __DIR__"nstreet2",
]));

	setup();
	replace_program(ROOM);
}
