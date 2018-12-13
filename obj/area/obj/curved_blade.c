// curved_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("�s�M", ({ "curved blade", "blade" }) );
	set_weight(9000);
	setup_blade(2, 12, 60, 0);

	if( !clonep() ) {
		set("wield_as", "blade" );
		set("unit", "��");
		set("value", 4200);
		set("rigidity", 25);
		set("long", "�o�O�@�ا�}������M�A�M�����e���s�A�Ω󴧱٫¤O�n���M�j�C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�M");
}
