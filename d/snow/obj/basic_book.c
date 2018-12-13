/*  basic_book.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("�i���ǿ�n�j", "book of elementary", "book");
    set_weight(1000);
    if( !clonep() ) {
        set("unit", "��");
        set("value", 200);
        set("long",
            "�o���ѬO�����@��p�ѱоɥ����һX�ҥΪ��Ь�ѡA���e\n"
            "�Q���L��A�j�P���@�ǴL�ˡB���g���򥻹D�z�C\n");
        set("required/skill", ([
	    "literate" : 1,
        ]));
        set("content", ([
	    "literate" : 10
        ]));
    }
    setup();
}

