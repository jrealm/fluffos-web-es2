// Room: /d/snow/square_sw.c

inherit ROOM;

void create()
{
	set("short", "�s��");
	set("long", @LONG
�o�̬O���F��s������n��M�s���������j�_��N�b�A���F�_�褣
���B�M�o�̪��_��i�H�ݨ��@�a�ȴ̡M����O�@����D�M�F���L�@��
���f�i�ݨ��@�a���K�Q�l�C
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
		"west" : __DIR__"wstreet1",
		"east" : __DIR__"square_s",
		"north" : __DIR__"square_w",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
