// Room: /d/snow/sgate.c

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�o�̬O���F��n�䪺�J�f�M���_��L��׳q�����F����D�M�X��
�ש���~��������M���F�n������L���F�n�誺�ѪQ�L�M�q�������쳱
�M�o�������M�����M���O��Ӥ@�s�ۺ٦ѪQ�몺�g��`�`�b�o�@�a�X
�S�M���誺�@���u�ۦѪQ�L�~���j���q���F�񪺤�����M�q�쳱������
�Ѩ��ꪺ�ӮȲ{�b�j�h¶�D���o�@�����M�]�������������W���@�B�_
�x���V�m�s�L���x��M�`���x�h���ޡM�d���j�H�h�b�������ơC
LONG
	);
	set("outdoors", "snow");
	set("connect-p", 1);
	set("exits", ([ /* sizeof() == 1 */
		"north" : __DIR__"sstreet1",
		"southeast" : "/d/oldpine/road1",
		"west" : "/d/newcamp/gate",
	]));

	setup();
}
