// child1.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("小孩", ({ "child" }) );
	set_race("human");
	set_level(1);
	set_stat_maximum("gin", 20);
	set_stat_maximum("kee", 20);
	set_stat_maximum("sen", 20);
	set_stat_notify("kee", 100);

	set("age", 6);
	set("long", "一個流著鼻涕的小孩﹐睜著一雙無邪的眼睛望著你。\n");
	set_temp("pending/sit_learning_literate", 1);
	setup();
	carry_money("coin", 1);
	carry_object(__DIR__"obj/tummy_cover")->wear();
}

int accept_fight(object ob)
{
	do_chat("小孩搖了搖頭﹐說道：我沒空打架，我在用功\唸書，將來要考狀元的。\n");
	return 0;
}

int notify_stat(mapping flag)
{
	command("emote 「哇」地一聲哭了起來﹕「你打我﹗媽媽﹗媽媽﹗」");
	return ::notify_stat(flag);
}
