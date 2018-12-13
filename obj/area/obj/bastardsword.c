// bastardsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("�j�C", ({ "bastardsword", "sword" }) );
	set_weight(16000);
	setup_sword(3, 9, 80, 2);

	if( !clonep() ) {
		set("wield_as", ({ "twohanded sword", "sword" }) );
		set("unit", "��");
		set("value", 8500);
		set("rigidity", 25);
		set("long",
			"�@������ت������C�M���o�򥨤j�����C�h�b�O�I�b�I��A�u��ѻM�O\n"
			"�L�H�����~�ϥΡC\n");
		set("wield_msg", "$N�N�I�᪺�C�n�@��A�u�I�v�a�@�n��X�@��j�C�C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�C");
}
