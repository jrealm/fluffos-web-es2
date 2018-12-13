// Room: /d/snow/ngate.c

inherit ROOM;

void create()
{
	set("short", "�s��");
	set("long", @LONG
�A�{�b�����b�@���d�骺�s���W�M���n�����B�i�H�ݨ��\�h�H�a�M
�Ъ١M���_�h�q���s�W�M�s����Ǫ�������M�a�誺�@���O�s���M�F��
�O���w���s�Y�M�s�Y���Y�O�@����a�C
LONG
	);
	set("outdoors", "snow");
	set("connect-p", 1);
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"nstreet2",
		"north" : "/d/goat/sroad1",
	]));
	set("objects", ([
		__DIR__"npc/garrison": 4,
		__DIR__"npc/lieutenant": 1,
	]) );

	setup();
	replace_program(ROOM);
}
