// ssilversword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("�~�ȼC", ({ "silver sword", "sword" }) );
	set_weight(7000);
	setup_sword(2, 15, 40, 4);

	if( !clonep() ) {
		set("wield_as", ({ "sword" }));
		set("unit", "��");
		set("value", 19000);
		set("rigidity", 40);
		set("long", "�@��Ȼs���u�C�Mű�y�o�Q������C\n");
		set("wield_msg", "$N��X�@��{�{�o�G���u�C��@�Z���C\n");
	}
	setup();
}
