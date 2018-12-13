// Room: /d/snow/ruin2.c

inherit ROOM;

void create()
{
	set("short", "�}�¤j�v���U");
	set("long", @LONG
�o�̬O�@�ɯ}�¤j�v�����U�M�_���������γ��w�g��ӧ~��F�M
�D�B�B���N���q�_�䪺�ʤf����i�ӡM�t�Aı�o�N�~���O�M�o�̲M���o
�۷���M�a�W�ΰ���������a�Q�ۤ@�ӧ��E�M���O�y���~�b�o�̴�
�J�o�]�����M���̷|���o��R��䪺�y���~�S�j�U�˶򪺼٬W�צ�F��
�誺�X�f�C
LONG
	);
	set("detail", ([ /* sizeof() == 3 */
		"�٬W" : "�@��ʤj���٬W�ˤF�U�ӡM���n�צ�F���U���X�f�C
",
		"���E" : "�@�ӥΰ���Q�������E�M���M²���M���O�o�����b�b�M��A�a��
�ɭԳ��ٻD��@�ѲH�H���ׯ�����C
",
		"�ʤf" : "�q�ʤf���~��h�M�u���j�v����L�������w�g�������t��F�M�p�G
�A�Q�L�h�M�j�j�i�H�q�ʤf���X�h�C
",
]));

	set("exits", ([
		"north": __DIR__"riverbank"
	]));
	set("objects", ([
		__DIR__"npc/girl" : 1
	]) );
	setup();
}

void init()
{
	add_action("do_climb", "climb");
}

int do_climb(string arg)
{
	if( arg != "�٬W" ) return 0;

	message_vision("$N���L�˶򪺼٬W�M���j�v���e�|���h�C\n", this_player());
	this_player()->move(__DIR__"ruin1");
	message("vision", this_player()->name() + "�q�˶�٬W���t�@�Y���F�X�ӡC\n",
		environment(this_player()), this_player());
	return 1;
}

