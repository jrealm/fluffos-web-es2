// ROOM: /d/snow/bazar.c
#include <room.h>
inherit BANK;

void create()
{
	set("short", "���O�p�Q");
	set("long", @LONG
�o�̬O�@���p���Q, �k���\�F�Ӫ��[, ���ư_�����X���`�Ϋ~�s
�s�����a�\�b�[�W, �A�ݨ�F���~��, �ֳQ, �J�L�˸_������, ���L�W
���������Ǧǹж��g, ���G�o����󤣱`�M��. ���U���Ӥj���, �W��
�\�F�ǥ��ǪA��. �������Ӱ��j���d�O, �W����F�Ӱ��B  (look ��
�B ), �ݨӹ��O�Ӥp����.
LONG
	);
	set("detail", ([ /* sizeof() == 2 */
		"���B" :
			"�y	�p	��	�Y	�|	��\n"
			"	��	��	��	��	��	�z\n\n"
			"�s�ڡR	deposit  <�ƶq> <����>,	�}��R	open account\n"
			"���ڡR	withdraw <�ƶq> <����>,	�I���R	convert <�ƶq> <����> to <�t������>\n"
			"�����Ч����O�ޡM�p���򥢡M�ܥ����ɵo�M�ݦ��@���O�Ҫ��C\n",
		"�d�O" : "�@�y���¬����ҿ��J�Ӧ�, ���o�X�@�ؿ@���������, �ݨӻ��Ȥ���.\n",
	]));
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"sstreet1",
	]));
	set("objects", ([
		__DIR__"npc/yu": 1,
	]));

	setup();
	replace_program(BANK);
}
