// Room: /d/snow/epath.c

inherit ROOM;

void create()
{
	set("short", "���R�p��");
	set("long", @LONG
�o�̬O�����R���p�Ѥl�M���褣���B�q�����F���s���M�p�Ѫ��_
���O�@�ǥ˫ΡM��¶�۰���������M�ݨӬO�����H���Τl�M�n�䦳�a�p
�ľQ�M���f���F�n���ΰ����į�M�p�ѩ��F�O���ਤ�C
LONG
	);
	set("detail/����",
		"�o���Τl������ݰ_�Ӭ۷��M���L�p�G�A���_�Ӫ��ܫj�j�i�H�p�o�ۡC\n");
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 2 */
		"east" : __DIR__"lane1",
		"west" : __DIR__"square_e",
		"south" : __DIR__"herb_shop",
	]));

	setup();
}

void init()
{
	add_action("do_climb", "climb");
}

int do_climb(string arg)
{
	if( arg!="����" ) return 0;

	message_vision("$N�Τ��k�W����M�ޤF�X�U½�F�L�h�C\n", this_player());
	this_player()->move(__DIR__"kitchen");
	message("vision", this_player()->name() + "�q���𪺥t�@�Y���F�L�ӡC\n",
		environment(this_player()), this_player());
	return 1;
}
