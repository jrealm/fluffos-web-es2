// Room: /d/snow/npath2.c

inherit ROOM;

void create()
{
	set("short", "����p��");
	set("long", @LONG
�o�̬O�@�����䪺�p���M�q�o�̥i�H�樣�_�䪺�s���@�D�r���q�V
�W���U�M��L�s�Y�W���@����L�M�H�Τ����B����a�M���A���F�n��y
�L�M�ˤ��ĿE�۷˧ɪ����ۡM�o�X�F�F���T�n�M����u�ۤp���i�H�^��
���F���j��M�p���V�F�n�i�H�q������C
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"southeast" : __DIR__"npath3",
		"west" : __DIR__"npath1",
		"north" : "/d/month/a1",
	]));
	set("objects", ([
		__DIR__"npc/woman": 1
	]) );
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
