// fur_hat.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
	set_name("��ִU", ({"fur hat", "hat"}));
	set_weight(1000);
	setup_head_eq();

	if( !clonep() ) {
		set("unit", "��");
		set("long", "�@�������O�����٬O쯥��_�s���p�U�C\n");
		set("value", 500);
		set("wear_as", "head_eq");
		set("apply_armor/head_eq", ([
			"armor" : 1,
		]) );
	}
	setup();	
}