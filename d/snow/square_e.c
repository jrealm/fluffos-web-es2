// Room: /d/snow/square_e.c

inherit ROOM;

void create()
{
	set("short", "�s��");
	set("long", @LONG
�o�̬O���F��s���F��M���F�O�@�����R���Ѥl�M���䦳�@�谪�j
���_��M�n��O�@�a���K�Q�l�M���L�������b�o�@��C
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"east" : __DIR__"epath",
		"west" : __DIR__"square",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
