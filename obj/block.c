inherit ROOM;

void create()
{
	set("short","��q");
	set("long",@LONG
�o�̬O ES2 ���u���q�v�ްV��, �p�G�A�Q�e��o��, ���:
�A�H�ϤF�C���W�h, �Цn�n���Ϭ٤@�U�A���ҧ@�Ҭ�, �Q��
�}���ܥu�n�_�u�W�L 15 �����Y�i :-) 
LONG
	);
	setup();
}

void init()
{
	if (!wizardp(this_player()) ) 
	add_action("block_cmd","",1);
	call_out("green", 2, this_player());
}

int block_cmd()
{
	if((string)query_verb() == "look") return 0;
	if((string)query_verb() == "help") return 0;
	return 1;
}

void green()
{
	tell_room(environment(this_player()),"�Ať�����ǨӺ�q�p�]�����q�n: \n\n"+
		"�o��q���@����  �b��]�̷n�ڷn\n"+
		"�h�Q�r�p�]�b�ڪ��߮����ư���\n"+
		"���ڪ��q�n�H���L��  �j�}�F�p����î\n"+
		"���ڪ��J���H���y��  ���_�a�V�p�ɶD\n"+
		"���l�𪺪��v������ڪ����N\n"+
		"���A�������ӫG�F�ڪ���\n"+
		"�o��q���]�w�g�o�˨I�R\n"+
		"�h�Q���p�������٬O�q�q�L�y\n\n");
	return;
}
