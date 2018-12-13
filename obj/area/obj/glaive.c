// glaive.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("���Y�M", ({ "glaive", "blade" }) );
	set_weight(9000);
	setup_blade(2, 10, 80, 0);

	if( !clonep() ) {
		set("wield_as", ({ "blade", "twohanded blade" }) );
		set("unit", "��");
		set("value", 6000);
		set("rigidity", 25);
		set("long",
			"���Y�M�O�@�حI�p�b�����j�M�A�M�����Ӫ��A�M�I�S�p�A���M��T�@�ΡA���q\n�o�O�����C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�M");
}
