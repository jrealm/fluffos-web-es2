// Room: /d/snow/square_w.c

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "�s��");
    set("long", @LONG
�o�̬O���F��s��������M���F�i�H�ݨ��s���������j�_��M�@�a
�p�ȴ̮y���b���䤣���B�M�ȴ̫e���@��OŢ�W�g�ۡu�����ȴ̡v�|��
�j�r�M�s���W�Q�۾�����۪O�C
LONG
    );
    set("exits", ([ /* sizeof() == 3 */
	"south" : __DIR__"square_sw",
	"west" : __DIR__"inn_hall",
	"east" : __DIR__"square",
	"north" : __DIR__"bug_room",
    ]));
    set("objects", ([
	"/d/snow/obj/stone" : 1,
    ]));
    set("outdoors", "snow");
    set("no_fight", 1);	// prevent pk when post

    setup();
    load_object("/daemon/board/common");
    create_door("west", "����", "east", 0);
}
