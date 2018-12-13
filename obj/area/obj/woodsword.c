// woodsword.c : an example weapon

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("��C", ({ "wooden sword", "sword" }) );
	set_weight(2000);
	setup_sword(1, 14, 40, 0);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("wield_as", "sword");
		set("unit", "��");
		set("value", 400);
		set("rigidity", 10);
		set("long", "�@��εw��d�������C�M�Q�����t�o�¶ª��C\n");
	}
	setup();
}
