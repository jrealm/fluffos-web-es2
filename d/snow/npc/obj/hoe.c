// hoe.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
	set_name("�S�Y", ({ "hoe" }) );
	set_weight(6000);
	setup_pike(2, 10, 50, 0);

	if( !clonep() ) {
		set("wield_as", ({ "twohanded pike" }));
		set("unit", "��");
		set("value", 800);
		set("rigidity", 20);
		set("long", "�@�⭫�l�l���S�Y�C\n");
	}
	setup();
}
