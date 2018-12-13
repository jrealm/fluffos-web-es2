// herbalist.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("�ľQ�x�d", ({"herbalist"}));
	set_race("human");
	set_class("alchemist");
	set_level(3);
	set_skill("unarmed", 5);
	set_skill("parry", 5);
	set_skill("dodge", 5);
	set_skill("dagger", 5);

	set("age", 44);
	set("long",
		"�ľQ�x�d���O��D�D�����~�k�l�M���M�~�����|���Q���F�M���L�ݰ_\n"
		"�Ө̵M���������B�믫�صo�M�A�i�H�� list �ݥL���̦������ġC\n");

	set("merchandise", ([
		STOCK_MEDICATION("black_pill") : 50,
		STOCK_MEDICATION("boar_berry") : 40,
		STOCK_MEDICATION("wild_ginseng") : 30,
		STOCK_MEDICATION("dragon_saliva") : 20,
	]));

	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_object(__DIR__"obj/fur_hat")->wear();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}
