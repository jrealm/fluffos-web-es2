// shortsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("�u�C", ({ "shortsword", "sword" }) );
	set_weight(3000);
	setup_sword(3, 6, 40, 0);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("wield_as", ({ "sword", "secondhand sword" }));
		set("unit", "��");
		set("value", 900);
		set("rigidity", 20);
		set("long", "�@����W���u�C�M�@��ȤH�a�b���䨾���Ϊ��Z���C\n");
		set("wield_msg", "$N��X�@��u�C��@�Z���C\n");
	}
	setup();
}
