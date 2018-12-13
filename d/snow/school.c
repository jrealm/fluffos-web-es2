// Room: /d/snow/school.c

inherit ROOM;

void create()
{
	set("short", "�p��");
	set("long", @LONG
�o�̬O�@���p�ѡM²�檺���]�P�X�i�Ʊo����������ȡM�N�O�o
���Τl���Ҧ��è�M�Ψ��@�Ӥj���d�M�̭���۳\�h��ۥ����j�ѡM��
�L���d�����O��۪��M�̫e������W��ۤ�Х|�_�M�P�@�֤p�����֮�
�f��M�p�Ѫ��X�f�b�_��C
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"north" : __DIR__"wstreet1",
	]));
	set("objects", ([
		__DIR__"npc/teacher": 1,
		__DIR__"npc/alchemist": 1,
		__DIR__"npc/child3.c": 2,
	]));
	set("no_fight", 1);

	setup();
	replace_program(ROOM);
}
