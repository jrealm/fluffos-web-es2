// kris.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("�u�M", ({ "kris" }) );
	set_weight(4000);
	setup_blade(1, 17, 40, 1);

	if( !clonep() ) {
		set("wield_as", ({ "blade", "secondhand blade" }));
		set("unit", "��");
		set("value",600);
		set("long", "�o�O�@�ؾA�X�񨭦׷i�Ԫ��u�M�M�b���u���C�o�M�M�`�V���s���C\n");
		set("rigidity", 22);
	}
	setup();
}
