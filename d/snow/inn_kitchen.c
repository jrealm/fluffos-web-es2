// Room: /d/snow/inn_kitchen.c

inherit ROOM;

void create()
{
	set("short", "�p��");
	set("long", @LONG
�o�̬O�@���e�����p�СM�@�y�j�_���ڤF�F��b������M�n�䪺�d
�l�������a��۳\�h��J�]�֡M�o�̥��`�O�۷��L���M�p�G�A�n�b
�o�̪F�i��檺�ܡM�̦n�p�ߧO�Q���p�G�ݵ۪��������S��F�M���F�i
�H�^��ȴ̸̡C
LONG
	);
	set("detail", ([ /* sizeof() == 2 */
		"�d�l" : "�o���d�l�̩񪺬O���ȤH�Ϊ��J�L�и_�M�����O���˦b�X�Ӥj�d�l\n"
				 "�̡M�d�l��������F�M�Q�O��K���ΡC\n",
		"�j�_" : "�@�y�U�N�ۺ����������j�_�M�_�f�i�H�e�Ǥ@�Ӻ~�l���i�h�M���L\n"
				 "�դѬ����N�o�����M��M���|���H�F�o�ض̨ơC\n"
	]));
	set("exits", ([ /* sizeof() == 1 */
		"east" : __DIR__"inn_hall",
	]));

	setup();
	create_door("east", "��O��", "west", 0);
}

void init()
{
	add_action("do_enter", ({"enter", "climb"}));
}
	
int do_enter(string arg)
{
	if( arg != "�j�_" ) return 0;
	message_vision("$N�@�G��, �q�j�_���_�f�p�F�i�h.\n", this_player());
	if( this_player()->move(__DIR__"fireplace") )
		message("vision", this_player()->name() + "�q�~���p�F�i��, ��A�����@��.\n",
			environment(this_player()), this_player());
	return 1;
}	
	