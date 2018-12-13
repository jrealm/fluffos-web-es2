// smock.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name("���K�o�l", ({ "work smock", "smock" }) );
	set_weight(5500);
	setup_armor();

	if( !clonep() ) {
		set("unit", "��");
		set("value", 720);
		set("long", "�o�O�@���K�K�u�@�ɥΨӾB�פ��P���q���u�@�A�C\n");
		set("wear_as", "armor");
		set("apply_armor/armor", ([
			"armor": 2,
			"armor_vs_fire": 5,
		]));
	}

	setup();
}
