//block_robot.c	the npc in this room will ask player some question
//and log some data to file: robot_check

inherit ROOM;

void create()
{
	set("short","�����H�q");
	set("long","\n
\t�o�̬O ES2 �������H�q, �p�G�A�Q�e��o��, 
\t����ܧA���欰�����������H (help robot).
\t�Y�A�w���F, �Ц^�������H�p���F���ݸ�, �Χ�Ův����.\n\n\n");
	set("no_fight", 1);
	set("objects", ([
		__DIR__"spirit": 1,
	]));
	setup();
}

void init()
{
	if(!wizardp(this_player()))
		add_action("do_quit", "quit");
}

int do_quit()
{
	write("��p, �A�{�b���� quit , �Ц^�������H�p���F���ݸܩΧ�Ův����.\n");
	return 1;
}
