//blue_jacket.c
#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("�Ŧ�M", ({ "blue jacket", "jacket" }) );
	set_weight(2000);
	setup_cloth();
	if( !clonep() ) {
		set("unit", "��");
		set("value", 500);
		set("long", "�@��`�Ŧ⪺�j��M�W��¸�F�Ѥj�@��\"��\"�r�C\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 2,
		]));
	}
	setup();
}