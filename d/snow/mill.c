// Room: /d/snow/mill.c

inherit ROOM;

void create()
{
	set("short", "�i�{");
	set("long", @LONG
�o�̬O�@���H�i�ѯ����~���i�{�M�Τl�̤@�j�b���Ŷ��Q�@�[����
���ڡM������ʾ�L�μ٤W����b�M��b���ʴX�ӵ��L��ʫΤl������
�ۿi�M�Фl���t�@�����ۤ@�ǪŪ��³U�C
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"out" : __DIR__"lane2",
	]));
	set("objects", ([
		__DIR__"npc/miller": 1
	]));

	setup();
	replace_program(ROOM);
}
