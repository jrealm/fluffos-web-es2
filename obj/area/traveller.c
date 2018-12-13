//traveller.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("�L����", ({ "traveller" }) );
	set("unit", "��");
	set("gender", "female");
	set_race("jiaojao");
	set_class("thief");
	set_attr("con",36);
	set_level(20);
	set("age", 19);
	set_skill("parry",50);
	set_skill("dodge",50);
	set_skill("blade",60);
	advance_stat("kee",100);
	set("long",
"�@����^�^, ���y�������L����, �@���l��, ���G�H�ɤS�n�W���h.\n");
	set("chat_chance", 4);
	set("chat_msg", ({
"�L���ȳݤF�X�f��D: �I �I .. �n��, �u��.\n",
"�L���Ȧ��G�֪������X�ܨӤF.\n",
		(: command,"sweat":),
	}));
	setup();
	carry_money("silver", 30);
	carry_object(__DIR__"obj/cloth")->wear();
	carry_object(__DIR__"obj/whip")->wield();
}

int accept_fight(object ob)
{
	do_chat("�L�������F����l�W������, ���D: ��ԣ, ���ֲ�½�F�٥�!\n");
	return 0;
}
