// blue_cloth.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("�ť����m", ({ "blue cloth", "cloth" }) );
	set_weight(2000);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "��");
		set("value", 600);
		set("long", "�@��ʥ��_�s������M�ݰ_�ӹ��O�m�U�h�Q����A�C\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 2,
		]));
	}

	setup();
}
