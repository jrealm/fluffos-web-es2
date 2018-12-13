// Room: /d/snow/river1.c
/*
    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�o�̬O�ˬy�Ǫ��å��y�A�ˬy�⩤�����@�V�h���A�u�����B�]����
�y�s�D�R�n�A�Φ��@�B�p���y�A���y�ĿE���n���g�L�˨����^���_�ձ�
Ť�A���n�@���p���i�H�^�쩤��C
LONG
        );
        set("resource", ([ /* sizeof() == 1 */
                "water" : "1",
]));
        set("outdoors", "snow");
        set("exits", ([ /* sizeof() == 1 */
		"south" : "/d/snow/npath3",
		"north" : "/d/chixiao/river2",
]));

        setup();
        replace_program(ROOM);
}
