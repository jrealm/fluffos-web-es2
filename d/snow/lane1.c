// File: /d/snow/lane1.c
// Updated by annihilator (Wed Mar 15 17:20:06 2000)

inherit ROOM;

void create()
{
	  set("short", "���R�p��");
	  set("long", @LONG
�o�̬O�����R�p�Ѫ��ਤ�B�M�p�ѩ��_�i�H�q������M�q�o�̴N�i
�Hť��ˬy�F�F���n���M�F��O�@�ɯ}�ª��j�v�|�M���f���@���}�мg
�ۡu���֫J���v�M���L�̭��w�g�O�_�����z�F�M�p�ѫn�䦳�@�y�p�g�a
���q�C
LONG
	  );
	  set("outdoors", "snow");
	  set("exits", ([ /* sizeof() == 3 */
	"north" : __DIR__"lane2",
	"west" : __DIR__"epath",
	"east" : __DIR__"ruin1",
]));

	setup();
	  replace_program(ROOM);
}
