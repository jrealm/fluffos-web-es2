// shortsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("�u�C", ({ "short sword", "sword" }) );
	set_weight(4000);
	setup_sword(1, 15, 40, 1);

	if( !clonep() ) {
		set("wield_as", ({ "sword", "secondhand sword" }));
		set("unit", "��");
		set("value", 900);
		set("rigidity", 20);
		set("long", "�@����W���u�C�M�@��ȤH�a�b���䨾���Ϊ��Z���C\n");
		set("wield_msg", "$N��X�@��u�C��@�Z���C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�C");
}
