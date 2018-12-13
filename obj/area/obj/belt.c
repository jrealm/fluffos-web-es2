// belt.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
	set_name("�y�a", ({ "belt" }) );
	set_weight(100);
	setup_waist_eq();

	if( !clonep() ) {
		set("unit", "��");
		set("value", 200);
		set("long",
			"�@���Ψӧ���Ǥl���y�a�A����a�W���H�����οǤl�W���a�lô��A�y�L\n"
			"���I�n�W���H�~�|�A�~��W�[���y�a�C\n");
		set("wear_as", "waist_eq");
		set("apply_armor/waist_eq", ([
			"armor" :1,
		]));
	}

	setup();
}
