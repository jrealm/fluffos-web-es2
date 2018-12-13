// weirblade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("�j�M", ({ "weirblade", "blade" }) );
	set_weight(15000);
	setup_blade(2, 14, 60, 0);

	if( !clonep() ) {
		set("wield_as", ({ "blade", "twohanded blade" }) );
		set("unit", "��");
		set("value", 6500);
		set("rigidity", 25);
		set("long", "�S�p�S�����j�M�A�O�H��ӥͬȡA�p�G���ⴤ�����ܡA�¤O��O�j�j�C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�M");
}
