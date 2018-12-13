#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�p�s��");
	set("long", @LONG
�o�جO�Ӥp�s���A�X�ʾ�}�}���������b����A�������Ӥp����
�d�����A�i�ѥ����^���ҾD�J���ǲ��{�H�A���n�i�^��H�n���m����
�F��s���C
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
		"south" : "/d/snow/square_w",
	]));
	set("outdoors", "snow");
	set("no_fight", 1);			// prevent pk when post

	setup();
	load_object("/daemon/board/bug_board");
}
