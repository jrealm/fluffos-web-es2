// Room: /d/snow/store.c

inherit ROOM;

void create()
{
	set("short", "�f��");
	set("long", @LONG
�o�̬O�@���f�̡M�]�O�Ȧ�Ȱӭ��x��f���M�B�e�B��檺�a��M
���F��]�����q���Ѩ��ꪺ���n�D���M�ҥH�f�̩��Ӫ��f���۷��h
�M�]�������ּƴX�ӳ]���f�̪�����M�Ѵ¦U�a���f�̤j�h�Ƴ����۳s
ô�M�]���ӷ~�Q���o�F�M���L���f�̤]�`�`�O�ʿ����H���s�u���a��M
�]���f�̪��u�@�q���T�w�M���j��f���i�Ӫ��ɭԩ����ݭn���`�Q�X��
���H��M���O�f�̪��Q��S�����_�������u�H�C
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"east" : __DIR__"sstreet1",
]));
	set("objects", ([
		__DIR__"npc/foreman": 1,
		__DIR__"npc/obj/wagon": 1,
		__DIR__"npc/obj/crate": 3,
	]));
set("no_fight", 1);



	setup();
	replace_program(ROOM);
}
