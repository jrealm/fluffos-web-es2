// axe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
	set_name("���Y", ({ "axe" }) );
	set_weight(10000);
	setup_axe(2, 12, 80, 0);

	if( !clonep() ) {
		set("wield_as", ({ "axe", "twohanded axe" }) );
		set("unit", "��");
		set("value", 2700);
		set("long", "�o�O�@��M�`�����Y�A�h�b�ΨӬ��A��ΡC\n");
		set("rigidity", 22);
	}
	setup();
}
