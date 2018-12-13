// clothboot.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
	set_name("�m�B�u", ({ "black boots", "boots" }));
	set_weight(1000);
	setup_feet_eq();

	if( !clonep() ) {
		set("unit", "��");
		set("long", "�o�O�x�������B�L�Z�x�`�諸�u�l�M���K�@�ΡC\n");
		set("value", 1000);
		set("wear_as", "feet_eq");
		set("apply_armor/feet_eq", ([
			"armor" : 1,
			"dodge" : 1,
		]) );
	}
	setup();	
}