// tummy_wear.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("�{��", ({ "tummy cover", "tummy", "cover" }) );
	set_weight(1000);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "��");
		set("value", 400);
		set("long", "�@����ب��誺�ʥ��Mô�W���÷��Ψӵ��p�Ĭ諸�窫�C\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 1,
		]));
	}

	setup();
}
