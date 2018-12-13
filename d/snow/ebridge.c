// Room: /d/snow/ebridge.c

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�A�{�b�Ө�@����L�s�˪����W�M�s�������Ƽe�M���O�`�׫o���T
�B�|�V�M�]���o�����ﳷ�F���~����q��~���n�M���U���ˤ����o�X
�F���F�������T�y�L�˨��M����O���F��M���F�h�q���ۦW�����u�s��
�M����Z�L���Z�L���D�����ݼݲ{�U���n�ަb���W�C
LONG
	);
	set("no_clean_up", 0);
	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/guard" : 2,
]));
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 2 */
		"west" : __DIR__"npath3",
		"east" : "/d/snowkeep/entrance",
]));

	setup();
	replace_program(ROOM);
}
