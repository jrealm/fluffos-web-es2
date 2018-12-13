// broadsword.c

#include <weapon.h>

inherit F_SWORD;
inherit F_BLADE;

void create()
{
	set_name("��C", ({ "broadsword", "sword" }) );
	set_weight(12000);
	setup_sword(2, 12, 60, 1);
	setup_blade(2, 12, 80, 0);

	if( !clonep() ) {
		set("wield_as", ({ "sword", "twohanded sword", "blade" }));
		set("unit", "��");
		set("value", 4000);
		set("rigidity", 25);
		set("long", "�@����ű���������K�C�M�o�O�x���x�h�`�Ϊ��Z���C\n");
	}
	setup();
}
