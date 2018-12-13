// Room: /d/snow/nstreet1.c

inherit ROOM;

void create()
{
	set("short", "��D");
	set("long", @LONG
�o�̬O���F��_�䪺�D�n��D�M���n�q����W�̼��x���s���M���_
�h�q����_���s���M�A�����䳣�O�@�ǽ����f�����Q�M�o�@�N���F����
����l�M�ä��`���Ӧh�H���ʡC
LONG
	);
	set("detail", ([ /* sizeof() == 1 */
		"���Q" : "�U���U�˪����Q�����M���L�ݰ_�Ӥ����O�A�|�αo�۪��a��C
",
]));
	set("exits", ([ /* sizeof() == 2 */
		"south" : __DIR__"square_n",
		"north" : __DIR__"nstreet2",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
