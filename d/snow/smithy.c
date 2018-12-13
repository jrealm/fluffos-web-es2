// Room: /d/snow/smithy.c

inherit ROOM;

void create()
{
	set("short", "���K�Q�l");
	set("long", @LONG
�o�̬O�@�����K�Q�l�M��W���F�\�h�K�����b���~��u��M�Q�l��
���@�ӿN�ۺ������V�����l�M�o�A�b��W���v�l�@�̤@�̪��M�����٦�
�@�ӨH�����j�K�z�M�Q�l���X�f�N�b�F��C
LONG
	);
	set("detail", ([ /* sizeof() == 2 */
		"�K�z" : "�o�Ӥj�K�z�ݰ_�ӤQ���H���M�W�����O�V��������C
",
		"�K��" : "�o���K������l�B��l�B�K��B�ѥХΪ��S�Y�B�p�����C
",
]));
	set("no_clean_up", 0);
	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/smith" : 1,
]));
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"square_s",
]));

	setup();
	replace_program(ROOM);
}
