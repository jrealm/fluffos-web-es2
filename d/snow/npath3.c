// Room: /d/snow/npath3.c

inherit ROOM;

void create()
{
	set("short", "����p��");
	set("long", @LONG
�A�{�b�Ө�@���ˬy��W���p���M�ˤ��y�L�G���۶����e�ɵo�X�F
�F���n���M�@�������L�ˬy���F�q����~���p���M�u�۷��䩹�n����
�B�h�i�H�樣�@���i�{�C�_��@���p���i�H�U��˨����C
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
		"north" : __DIR__"river1",
		"south" : __DIR__"lane2",
		"northwest" : __DIR__"npath2",
		"east" : __DIR__"ebridge",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
