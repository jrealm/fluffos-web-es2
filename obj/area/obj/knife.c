// knife.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
	set_name("�p�M", ({ "knife" }) );
	set_weight(900);
	setup_dagger(1, 14, 20, 0);

	if( !clonep() ) {
		set("wield_as", ({ "dagger", "secondhand dagger" }));
		set("unit", "��");
		set("value",70);
		set("long", "�@�`���W���p�M�A�ݨӹ��O�p�y�������C\n");
		set("rigidity", 15);
	}
	setup();
}
