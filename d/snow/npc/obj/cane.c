// cane.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
	set_name("���", ({ "cane" }) );
	set_weight(2400);
	setup_staff(1, 19, 130, 0);

	if( !clonep() ) {
		set("wield_as", ({ "staff", "twohanded staff" }) );
		set("unit", "��");
		set("value", 600);
		set("rigidity", 12);
		set("long",
			"�@�ڵw�����M�]���g�~�ϥΦ���o���ơC\n");
	}
	setup();
}
