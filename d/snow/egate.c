// egate.c

inherit ROOM;

void create()
{
	set("short", "�e��");
	set("long", @LONG
�}�¤j�v�~�A�A���e�O����e�y���׬y�B�A�Ӧۦ�_�B�F�_�����
�p�e�׬y��A�w�w���V��n�y�h�C��_�䪺�e�y�W���@�y�p���A�L�F��
�A�u�۪F�_��e�y���p�ۤl���i�H�q�����a���C�@
LONG
	);
	set("detail", ([ /* sizeof() == 2 */
		"�p��" : "�@�y���̤���d�f�������.\n",
	]));
	set("outdoors", "snow");
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"ruin1",
		"northeast" : "/d/lee/r1",
	]));

	setup();
}
