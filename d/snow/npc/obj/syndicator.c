// syndicator.c

#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;
inherit F_UNIQUE;

void create()
{
	set_name("�u�خQ�v", ({ "syndicator" }));
	set_weight(3000);
    setup_dagger(3, 14, 100, 5);

	if( !clonep() ) {
		set("wield_as", ({ "dagger", "secondhand dagger" }));
		set("unit", "��");
		set("value", 32000);
		set("rigidity", 40);
		set("long",
			"�o�O�@������|�o���P���M�b�W�κ�Ӫ��J�u��ťX�@�Ӭ���\n"
			"�k�l���y�M�_�S���O�o�k�l�������O���X���Y�b�Q�L�䪺��\n"
			"��M�P�����`�_�u�M�u��ΨⰦ�������C\n");
	}
	setup();
}

int inflict_damage(string strength, object victim)
{
	int dam = ::inflict_damage(strength, victim);

    if( dam && random(100) < 40 ) {
		environment()->add_temp("fight_msg", HIW "�خQ���M�o�X�@�}��檺���n�A" NOR);
        victim->act(15);
	}
	return dam;
}
