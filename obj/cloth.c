// cloth.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("����", ({ "cloth" }) );
	set_weight(2000);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "��");
                set("value",60);
		set("long", "�@��ʥ��_�s������M�ݰ_�ӹ��O�m�U�H����A�C\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 1,
		]));
	}

	setup();
}
