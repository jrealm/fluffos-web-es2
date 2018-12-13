// Room: /d/snow/fireplace.c

inherit ROOM;

void create()
{
    set("short", "�j�_��");
    set("long", @LONG
�A�{�b���l�Y�����b�@�Ӥj�_����, �Y���W�������i�ݨ�ϧw���X
�f, ���L��M�S����k���X�h, �o�̪�����]�����~�N�����ܱo�Q��, 
�a���W�n�F�@�h�p�p�����.
LONG
    );
    set("exits", ([ /* sizeof() == 1 */
	"out" : __DIR__"inn_kitchen",
    ]));

    set("objects", ([
	__DIR__ "npc/obj/woodsword": 1,
	__DIR__ "npc/obj/woodblade": 1
    ]));

    setup();
    replace_program(ROOM);
}
