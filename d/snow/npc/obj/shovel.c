// shovel.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
	set_name("�K��", ({ "shovel" }) );
	set_weight(6000);
	setup_pike(2, 9, 70, 0);

	if( !clonep() ) {
		set("wield_as", ({ "twohanded pike" }));
		set("unit", "��");
		set("value", 700);
		set("rigidity", 20);
		set("long", "�@����g�Ϊ��K��C\n");
	}
	setup();
}
