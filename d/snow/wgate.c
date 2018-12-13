// Room: /d/snow/wgate.c

inherit ROOM;

void create()
{
	set("short", "���F��");
	set("long", @LONG
�o�̬O���F����䪺�x�D�M���M���F��]�b��W���_��M���O�x�D
�o�O�q����J���F�M�]����ӭשx�D�ɧQ�ΤF�@�q�q�e�����J�����ڶ�
�x���̹D�M�]���W�o���x�D�K�q�����L�s�����j�����̹D�M�X���۹i
�M���F�q�����F����D�M����h�X��C
LONG
	);
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 1 */
		"east" : __DIR__"wstreet2",
		"northwest" : "/d/graveyard/grave1",
	]));

	setup();
	replace_program(ROOM);
}
