
// pen.c �P�x��
#include <weapon.h>

inherit F_DAGGER;

void create()
{
	set_name("�P�x��", ({ "pen" }));
	set_weight(3000);
	setup_dagger(3,8,80,3);

	if( !clonep() ) {
		set("wield_as", ({ "dagger", "secondhand dagger" }));
		set("unit", "��");
		set("value", 3000);
		set("rigidity", 30);
		set("long", 
		"�@��κ��ű�y���P�x���A�������¦�C\n"
		);
		set("wield_msg",
		"$N���X�@���P�x�����b��W�C\n"
		);
	}
	setup();
}
