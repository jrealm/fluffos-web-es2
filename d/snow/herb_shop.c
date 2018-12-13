// Room: /d/snow/herb_shop.c

inherit ROOM;

void create()
{
	set("short", "�p�ľQ");
	set("long", @LONG
�o�̬O�@���p�ľQ�M�s���ˤ@�I���۵P���S���M�u�b���䱾�ۤ@��
���ư_������P�M�W���g�ۡu���Ͱ�v�T�Ӧr�M���ª��d�O�᭱���C��
�@�C���d�M���d���C�ө�P���ľQ���W�x���S��������ҡM�譱����W
�Q�۴X���ΰ����̯�M���o�ؤp�ľQ�S�����N�ȭ��簣�Ĩ��M�u�n�Υ�
����N�C
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"north" : __DIR__"epath",
	]));
	set("objects", ([
		__DIR__"npc/herbalist": 1,
	]));

	setup();
	replace_program(ROOM);
}
