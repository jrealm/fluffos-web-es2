// leather_boot.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
	set_name("�ֵu�u", ({ "leather boots", "boots" }));
	set_weight(1000);
	setup_feet_eq();

	if( !clonep() ) {
		set("unit", "��");
		set("long", "�o�O�@���ֻs���u�u�M�ݰ_�Ӧ����¤F�C\n");
		set("value", 400);
		set("wear_as", "feet_eq");
		set("apply_armor/feet_eq", ([
			"armor" : 1
		]) );
	}

	setup();
}
