// Room: /adm/guild/guildhall.c

inherit ROOM;

void create()
{
	set("short", "�Ův���|");
	set("long", @LONG
�o�̴N�O�Ův���|�F�M�@�ӥb�y�����j�B�q�}�B�b�C�m�������M��
�Z���a���Q�ۤ@�h�Ѻ��֡M��a���Y�O�@�ɯ¥ժ��j���ؿv�M��þ��
����W��i�����檺�곻�M��y�X�@�ز��Y����^�M���_�O�}�|�Ϊ��|
ĳ�U�M�F��O��s LPC ���Ův�ǰ|�M����h�O�q���@�ɦU�a���ǰe���C
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"east" : __DIR__"academy",
		"north" : __DIR__"meetingroom",
]));

	setup();
	load_object("/daemon/board/wizard");
	replace_program(ROOM);
}
