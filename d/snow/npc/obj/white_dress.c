// white_dress.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("�պ��Эm", ({ "white dress", "dress" }) );
	set_weight(2000);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "��");
		set("value", 3200);
		set("long", "�@��զ⪺�����k�l��m�M�N�_�ӻ��X�L��C\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 3,
			"spi": 1
		]));
	}

	setup();
}
