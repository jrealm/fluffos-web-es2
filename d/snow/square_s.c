// Room: /d/snow/square_s.c

inherit ROOM;

void create()
{
	set("short", "�s��");
	set("long", @LONG
�o�̬O���F��s�����n��M���_�i�H�樣�@�谪�j���_��M�s���H
�_�𬰤��ߧΦ��@�ӤQ�h�V���誺�j�Ŧa�M��D���n�q����~�M�F�䤣
���B�������K�Q�l�C
LONG
	);
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 4 */
		"west" : __DIR__"square_sw",
		"east" : __DIR__"smithy",
		"north" : __DIR__"square",
		"south" : __DIR__"sstreet1",
]));

	setup();
	replace_program(ROOM);
}
