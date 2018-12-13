// leather_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name("�w�֥ҫ`", ({ "leather armor", "armor" }));
	set_weight(10000);
	setup_armor();

	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"�@��Τ��ּߵw�_�X�M�ΨӫO�@���骺�ҫ`�M���M���@�ĪG�񤣤W\n"
			"���ݻs�����Z�ҡM���O���K�K�y�]�O�o���ֻs�ҫ`���u�I�C\n");
		set("value", 1400);
		set("wear_as", "armor");
		set("apply_armor/armor", ([
			"armor": 6
		]) );
	}
	setup();
}
