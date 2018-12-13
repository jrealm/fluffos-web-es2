// Room: /d/snow/inn_hall.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "�p�ȴ�");
	set("long", @LONG
�o�̬O�@�a�p�ȴ̡M���ª���Ȧ]���g�~���ϥΦ��ܱo�Q���K�G�M
����j�ۤ@�h��î�����ǨӤ@�}�}���ꪺ�n���M�j���O�ȴ̪��p�СM�a
�_�䪺�����W���@�D�q���G�Ӷ��y���ӱ�M�ӱ�U�N�O�d�O�M�F��O
�ȴ̪��X�f�M���f�@��Ƚk�OŢ�H���n�\�M�W���g�ۡu�����ȴ̡v�M�N
��O�Y�ϧA�S�����M�]�w��ӳo�̲��ť�ѡM�ܦ�_���C��n�䦳�@��
����q���ȴ̫᭱�����СC
LONG
	);
        set("objects", ([
		"/d/snow/npc/waiter" : 1,
		"/d/snow/npc/innkeeper" : 1,
        ]));
	set("valid_startroom", 1);
	set("no_fight",1);
	set("detail", ([ /* sizeof() == 8 */
		"�s��" : "�A�J�Ӧa�@�F�@�s���W�K�����ȡM���o�F�M�����w�~�������d�M��
������l�s�{�����ʦL���u�ަްs�v�M���|�u�����@�~�K���H�M��
���n�X»�K�ۦ譥�j���Ӫ����~�Ѱs�C
",
		"�OŢ" : "�@��Ƚk���j�OŢ�����a���b�Ϋe���X���W�M�@�O���ӡM���O�g��
�u�����ȴ̡v�|�Ӥj�r�M�̤U�����OŢ�e�ۤ@�Ӹ�Ī�C
",
		"���" : "�o�Ǯ�ȹs�s�����a��m�b�ȴ̪��U���M�ݨӬ۷���¤F�C
",
		"�ӱ�" : "�o�D�ӱ�q���G�Ӫ����y��ȩСC
",
		"��î" : "��î�Ψӹj�}�ȤH�ο���p�Ъ��l�_�M���O�פ���q�p���ƥX�Ӫ�
����C
",
		"�d�O" : "�d�O�᭱���C�ۤ@»»�K�۬��ȱ����s���M�o�ǬO�ȴ̴x�d���p��
�R�����~�Ѱs�M�p�G�A������M�����ݰݴx�d�����o�ǳ��~�Ѱs��
�O����C
",
		"west" : (: look_door,     "west" :),
		"east" : (: look_door,     "east" :),
	]));
	set("exits", ([ /* sizeof() == 2 */
		"west" : __DIR__"inn_kitchen",
		"east" : __DIR__"square_w",
	]));

	setup();
	load_object("/daemon/board/wizard_board");
}
void init()
{
//	if (!wizardp(this_player()))
//	load_object("/daemon/board/wizard_board");
//	add_action("block_cmd", "post", 1);
}

int block_cmd()
{
	if( !wizardp(this_player())) 
		return notify_fail("�@�몱�a���i�b���G��d���C\n");
	return 1;
}
