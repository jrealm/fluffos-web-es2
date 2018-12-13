// longsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("���C", ({ "longsword", "sword" }) );
	set_weight(5000);
	setup_sword(3, 7, 50, 0);

	if( !clonep() ) {
		set("wield_as", "sword" );
		set("unit", "��");
		set("value", 4000);
		set("rigidity", 25);
		set("long", "�@����ű�������C�M�O�Z�L���H�`�Ϊ��Z���C\n");
		set("wield_msg", "$N�u�|�v�a�@�n��X�@����C���b�⤤�C\n");
	}
	setup();
}
