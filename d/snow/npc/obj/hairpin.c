// hairpin.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
	set_name("�j�ɾv¯", ({ "bronze hairpin", "hairpin" }));
	set_weight(400);
	setup_head_eq();
	if( !clonep() ) {
		set("unit", "��");
		set("value", 100);
		set("long", "�@��ͺ��ɺ�M���¤������v¯�C\n");
		set("wear_as", "head_eq");
		set("apply_armor/head_eq/spi", 1);
	}
	setup();
}
