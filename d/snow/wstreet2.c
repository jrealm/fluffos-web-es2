// Room: /d/snow/wstreet2.c

inherit ROOM;

void create()
{
	set("short", "��D");
	set("long", @LONG
�o�̬O���F����䪺��D�M�_��O���F���m�աM���`�|���@����
�W�����̦b�o�̽ͽ���W�����ơM���̭Y�����ݨӳo���_�ơM�]�O�b�o
�̳]������M���褣���B�N�O�X���x�D�M��D�n��O�@�a�|��Q�C
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
		"north" : __DIR__"court",
		"east" : __DIR__"wstreet1",
		"west" : __DIR__"wgate",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
