// blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("��M", ({ "blade" }) );
	set_weight(8000);
	setup_blade(2, 10, 60, 0);

	if( !clonep() ) {
		set("wield_as", "blade" );
		set("unit", "��");
		set("value", 3500);
		set("rigidity", 25);
		set("long", "�@���ű��M�M�O�Z�L���H�`�Ϊ��Z���C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�M");
}
