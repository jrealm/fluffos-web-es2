// robe.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("���T", ({ "robe" }) );
	set_weight(1000);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "��");
		set("value", 600);
		set("long", "�@�M���q���֥��T�l�A�W�����@�ǦǹСC\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 1,
		]));
	}

	setup();
}
