// man.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("���H", ({ "man" }) );
	set_race("human");
	set_level(2);
	set("long", "�@�Ӵ��q�����H�M���o�˪��H�@�ѥi�H�b���W�I���X�Q�ӡC\n");
	setup();
	carry_money("coin", 30);
	carry_object("/obj/area/obj/cloth")->wear();
	carry_object("/obj/area/obj/shortsword")->wield();
}
