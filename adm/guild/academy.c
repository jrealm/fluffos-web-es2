// Room: /adm/guild/academy.c

inherit ROOM;

void create()
{
	set("short", "�Ův�ǰ|");
	set("long", @LONG
�o�̬O�Ův�̬�s LPC ���a��M�p�G�A�O�s��Ův�M�w��Ө�o��
�M��L�H���۰Q�סM�p�G�A�O�Ѥ�M�]�Ф��[�^���s�⪺���D�C
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"guildhall",
	]));

	setup();
	load_object("/daemon/board/lpc");
	replace_program(ROOM);
}
