// woman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("�ְ�", ({ "woman" }) );
	set_race("human");
	set_level(2);

	set("gender", "female");
	set("long", "�@�Ӯe��q�R���ְ��M��ۤQ������C\n");
	setup();
	carry_money("coin", 10);
	carry_object("/obj/area/obj/cloth")->wear();
}
