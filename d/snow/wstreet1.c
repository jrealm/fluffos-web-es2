// Room: /d/snow/wstreet1.c

inherit ROOM;

void create()
{
	set("short", "��D");
	set("long", @LONG
�o�̬O���F��s�����䪺��D�M���_�O�@���ȴ̡M���L�o�Ӥ�V�S
���J�f�M�n��@���C�˫ΡM���f�x���o�����b�b�M���O�a�p�ѼҼˡM��
�誺��D�Q���e���M���W�٦������g�L���X�Ӫ������C
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
		"south" : __DIR__"school",
		"east" : __DIR__"square_sw",
		"west" : __DIR__"wstreet2",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
