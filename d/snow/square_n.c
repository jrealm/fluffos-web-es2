// Room: /d/snow/square_n.c

inherit ROOM;

void create()
{
	set("short", "�s��");
	set("long", @LONG
�o�̬O���F��s���_��M���`�O����ĵ��^���C�����a��M��@�Q
���h�O�������Ҧb�M���n�i�H�ݨ��@��j�_��M���_�h�O�@����������
�D�C
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"north" : __DIR__"nstreet1",
		"south" : __DIR__"square",
	]));
	set("objects", ([
		__DIR__"npc/child1" : 1,
		__DIR__"npc/child2" : 1
	]) );
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
