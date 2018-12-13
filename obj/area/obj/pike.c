// pike.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
	set_name("���j", ({ "long pike", "pike"}));
	set_weight(11000);
	setup_pike(2,11,60,1);

	if( !clonep() ) {
		set("wield_as", ({ "twohanded pike", "pike" }));
		set("unit", "��");
		set("value", 6000);
		set("rigidity", 25);
		set("long",
"�@��j�Y�κ��ű�y�Ӧ������j�A�j�������A�j�Y�j���α����a��j�ۤ@�����y�A�M
�O�j���H�`�`�ϥΪ��Z���C\n"
		);
		set("wield_msg",
		"$N������q�����X�@����j���b��W�C\n"
		);
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();
	
		ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�j");
}
