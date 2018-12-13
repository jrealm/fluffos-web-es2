// Room: /d/snow/square.c

inherit ROOM;

void create()
{
	set("short", "�s������");
	set("long", @LONG
�o�̬O���F��s���������M�@�襨�j���Ѻ_��L�ڿ����a���b����
�M�@�ǫĵ��`�`���W�o��Ѻ_�^���M�_��U�C��K�ݦa��۴X�i������
�H������ѡM����٦��@�Ӥ����Ѹ��H�����Ѵ��C
LONG
	);
	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/obj/pot" : 1,
		__DIR__"npc/gammer" : 1,
		__DIR__"npc/junkman": 1,
	]));
	set("detail", ([ /* sizeof() == 2 */
		"�_��" : "�o��_��ֻ��]����T�ʷ��F�M�@����������Ž�ڴX�G����a���M
��F�]���g�`�Q�H���N����o���ơC
",
		"����" : "�Q�����q�`���������M�p�G�A�֤F�M�����Ȯ�M�ɺް��U�ӥ𮧡C
",
]));
	set("exits", ([ /* sizeof() == 4 */
		"east" : __DIR__"square_e",
		"north" : __DIR__"square_n",
		"west" : __DIR__"square_w",
		"south" : __DIR__"square_s",
	]));

	setup();
}

void init()
{
	add_action("do_climb", "climb");
}

int do_climb(string arg)
{
	if( arg != "�_��" ) return 0;

	message_vision("$N�k�ۺ_�𪺾�F���F�W�h�C\n", this_player());
	if( this_player()->move(__DIR__"tree") )
		message("vision", this_player()->name() + "�q��U���F�W�ӡC\n",
		environment(this_player()), this_player());
	return 1;
}

