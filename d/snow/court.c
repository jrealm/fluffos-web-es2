// Room: /d/snow/court.c

inherit ROOM;

void create()
{
	set("short", "�m��");
	set("long", @LONG
�o�̬O���F���m�աM���`�����x�����I�F�����򤣺����i�H��
�o�̨ӦV�զѥӶD�M�ҿת��զѴN�O�a��W���w��P�n�檺�ѤH�M���~
����զѪ��O�}�i�{�����ѯR�M���O�L�̪��餣�O�ܦn�M�ä��`��m
�ո̨ӡM���n�O��D�M�_��O�@���Ű�M���̬��v�ݨӳo���_�ƴN�|
�b���̶}��C
LONG
	);
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"wstreet2",
	]));
	set("objects", ([
		__DIR__"npc/oldman": 1
	]));

	setup();
	replace_program(ROOM);
}
