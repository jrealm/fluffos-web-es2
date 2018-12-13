// broadsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("��C", ({ "broadsword", "sword" }) );
	set_weight(10000);
	setup_sword(2, 12, 70, 1);

	if( !clonep() ) {
		set("wield_as", ({ "sword", "twohanded sword"}) );
		set("unit", "��");
		set("value", 5500);
		set("rigidity", 25);
		set("long", "�@����T�ت�����C�M���q�����A�ݭn���p���M�O�~�ധ�R�o�تZ���C\n");
		set("wield_msg", "$N�u�|�v�a�@�n��X�@��S���S������C���b�⤤�C\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�C");
}
