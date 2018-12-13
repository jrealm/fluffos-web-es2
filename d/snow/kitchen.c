// Room: /d/snow/kitchen.c

inherit ROOM;

void create()
{
	set("short", "�p��");
	set("long", @LONG
�A�{�b���b�@�ᦳ���H�a���p�и̡M���L�M�A�Q�����������H�a�p
�Цn�����Ӥ@�ˡM�èS���ﺡ�F���n���׸�s�î����M�Q�Ӧ����H�]�O
�٦Y���Τ~�঳�����M�p�Ъ����b�A���n��M���L���F�M�F��h�O�A
�i�Ӫ�����C
LONG
	);

	set("objects", ([
		"/obj/food/dumpling" : 2
	]) );
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
	this_player()->move(__DIR__"epath");
	message("vision", this_player()->name() + "�q���𪺥t�@�Y���F�X�ӡC\n",
		environment(this_player()), this_player());
	return 1;
}
