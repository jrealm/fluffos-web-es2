// Room: /d/snow/lane2.c

inherit ROOM;

void create()
{
	set("short", "����p��");
	set("long", @LONG
�A�{�b�Ө�@�B�Ѥl���J�f�M���_�q���@�����䪺�p���M����O�@
�ɤj�˫ΡM�j���`��ۡM�F�䦳�@�a�i�{�M�i�{�ήǤ@�Ӥ������F�F�a
��ۡM���n�q���Ѥl�̪��@���ਤ�C
LONG
	);
	set("detail", ([ /* sizeof() == 3 */
		"�j�˫�" : "�@�����j���˫ΡM�b���F��o�˪��s���p��Ө��M�o�˪��Τl�ä�
�h���M�i��o�W�O�����H�a�C
",
		"����" : "�o�[�����O�i�{�ʤO���ӷ��M���`�ˤ��רK���u�`�N�����Τ��O�M
�@���V�\\���u�`�M�N�o���u�H�θ}��C
",
		"�i�{" : "�@�a�Τ������ѯ����i�{�M�i�{�����O���۪��M���L�q�̭��ǨӪ�
�n���P�_�M���Ӧ��u�H���b�̭��u�@�C
",
]));
	set("exits", ([ /* sizeof() == 2 */
		"south" : __DIR__"lane1",
		"north" : __DIR__"npath3",
]));
	set("outdoors", "snow");

	setup();
}

void init()
{
	add_action("do_enter", "enter");
}

int do_enter(string arg)
{
	if( !arg || arg!="�i�{") return 0;

	message_vision("$N���}�i�{�����M���F�i�h�C\n", this_player());
	if( this_player()->move(__DIR__"mill") )
		message("vision", this_player()->name() + "���}���q�~�����F�i�ӡC\n",
			environment(this_player()), this_player());
	return 1;
}


