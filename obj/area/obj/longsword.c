// longsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("���C", ({ "long sword", "sword" }) );
	set_weight(7500);
	setup_sword(2, 10, 50, 1);

	if( !clonep() ) {
		set("wield_as", "sword" );
		set("unit", "��");
		set("value", 4000);
		set("rigidity", 25);
		set("long", "�@����T�ت������C�M�O�Z�L���H�`�Ϊ��Z���C\n");
		set("wield_msg", "$N�u�|�v�a�@�n��X�@����C���b�⤤�C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�C");
}
