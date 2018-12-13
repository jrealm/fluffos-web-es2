// child1.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("�p��", ({ "child" }) );
	set_race("human");
	set_level(1);
	set_stat_maximum("gin", 20);
	set_stat_maximum("kee", 20);
	set_stat_maximum("sen", 20);
	set_stat_notify("kee", 100);

	set("age", 6);
	set("long", "�@�Ӭy�ۻ�����p�ġM�C�ۤ@���L����������ۧA�C\n");
	setup();
	carry_money("coin", 1);
	carry_object(__DIR__"obj/tummy_cover")->wear();
}

int accept_fight(object ob)
{
	do_chat("�p�ķn�F�n�Y�M���D�G�ڨS�ť��[�A�ڦb�Υ\\��ѡA�N�ӭn�Ҫ������C\n");
	return 0;
}

int notify_stat(mapping flag)
{
	command("emote �u�z�v�a�@�n���F�_�ӡR�u�A���ڡT�����T�����T�v");
	return ::notify_stat(flag);
}
