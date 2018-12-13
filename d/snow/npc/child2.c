// child2.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("�p��", ({ "child" }) );
	set_race("human");
	set_stat_notify("kee", 100);
	set_level(1);

	set("long", "�@�Ӭ��C�B�K���j���k�ġM���N�N�a��ۧA�C\n");
	set("chat_chance", 10);
	set("chat_msg", ({
		"�p�ĥs�D�R�r �� �r ��\n",
		"�p�����������a���ۡM¶�ۧA�]�Ӷ]�h�C\n",
		"�p�ĥs�D�R�� �� �� ��\n"
	}) );
	setup();
	carry_money("coin", 1);
	carry_object(__DIR__"obj/woodsword")->wield();
}

int accept_fight(object ob)
{
	do_chat("�p�Ŀ��Ħa���ۡR�n�r�T�Ӥ�Z�T�w�T\n");
	return 1;
}

int notify_stat(mapping flag)
{
	command("emote �u�z�v�a�@�n���F�_�ӡR�u�A���ڡT�A�O�a�H�T�v");
	return ::notify_stat(flag);
}

