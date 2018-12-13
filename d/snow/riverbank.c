// Room: /d/snow/riverbank.c

inherit ROOM;

void create()
{
	set("short", "�e��Ŧa");
	set("long", @LONG
�o�̬O�e�䪺�@�B�Ŧa�M���檺�e�y�q�A���_�䩹�F�n��y�h�M��
�o�̪��e�����_�@�V�h�����a��i�H�ݨ��@�Ӥ����M�n��h�O�@���}��
���j�v�|�M����W�@�Ӥj�ʤf�����i�H���H�q�L�C
LONG
	);
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"ruin2",
]));

	setup();
	replace_program(ROOM);
}
