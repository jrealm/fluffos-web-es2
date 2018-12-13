// broadaxe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
	set_name("�O��", ({ "broadaxe", "axe" }) );
	set_weight(10000);
	setup_axe(2, 11, 100, 0);

	if( !clonep() ) {
		set("wield_as", ({ "axe", "twohanded axe" }) );
		set("unit", "��");
		set("value", 5000);
		set("rigidity", 25);
		set("long", "�@��j���O��A���q�۹�I���A���L�O�򪺩�b�ܪ��A�O�۷�F�`���L�b�C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "��");
}
