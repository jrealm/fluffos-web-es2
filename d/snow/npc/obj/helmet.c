// helmet.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
	set_name("�ɲ�", ({ "brass helmet", "helmet"}));
	set_weight(4000);
	setup_head_eq();

	if( !clonep() ) {
		set("unit", "��");
		set("long", "�o�O�@���ɻs���Y���M�ݩ�x�������C�ŪZ�x�����C\n");
		set("value", 900);
		set("wear_as", "head_eq");
		set("apply_armor/head_eq", ([
			"armor" : 3,
			"dodge" : -3,
		]) );
	}
	setup();	
}