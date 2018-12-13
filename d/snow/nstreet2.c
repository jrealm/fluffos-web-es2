// Room: /d/snow/nstreet2.c

inherit ROOM;

void create()
{
	set("short", "��D");
	set("long", @LONG
�o�̬O���F��_�䪺�D�n��D�M���n�y���B�K�O�@�B�s���M���_�i
���@���d�骺�s����L�����~�󪺤s�Y�q�����Ϥs�W�M�F��O�@���p��
�q������M����h�O�@���毸�C
LONG
	);
	set("no_clean_up", 0);
	set("objects", ([ /* sizeof() == 1 */
		"/obj/area/man" : 1,
]));
	set("exits", ([ /* sizeof() == 4 */
		"west" : __DIR__"post_office",
		"east" : __DIR__"npath1",
		"south" : __DIR__"nstreet1",
		"north" : __DIR__"ngate",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
