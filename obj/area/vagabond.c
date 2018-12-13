// vagabond.c

#include <npc.h>

inherit F_BANDIT;

void create()
{
	set_name("�����L��", ({ "vagabond" }));
	set_race("human");
	set_class("fighter");
	set_level(2);
	set_skill("unarmed", 5);
	set_skill("dodge", 3);
	set_skill("dagger", 7);

	set("age", 24);
	set("long", "�@�Ӻ��y���ۡA�c��c�����L��~�A�̦n�O�a�L�Ӫ�C\n");
	set("chat_chance", 6);
	set("chat_msg", ({
		"�L��~�u�K�K�v�a�ǯ��ۡA�@�䤣�h�n�N�a�n�ۧA�C\n",
		"�L��~�˧@�Y�L��ƪ��ˤl����A����A�M��X�䤣�N�a���A�@�U�C\n",
		"�L��~�Ϋ����ߪ��覡��F���ˡA�M�᩹�A�o��@�u ... �ָ��I\n",
	}));

	setup();
	carry_object(__DIR__"obj/knife")->wield();
	carry_object(__DIR__"obj/dice");
}
