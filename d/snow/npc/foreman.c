// foreman.c

#include <npc.h>

inherit F_VILLAGER;

void new_crate();


void create()
{
	set_name("�u�Y", ({ "foreman" }) );
	set_race("human");
	set_level(8);
	set_stat_maximum("kee", 60);
	set_attr("str", 18);
	set_attr("cor", 19);
	set_attr("cps", 15);
	set_attr("dex", 16);

	set("age", 48);
	set("long",
		"�o��N�O�o�a�f�̪��u�Y�M�t�d�����u�H�N�f���h�i�h�X�M�p�G\n"
		"�A�Q���u�Ȩǿ��M�i�H��L�ͽͬݡC\n");
	set("chat_chance", 10);
	set("chat_msg", ({
		(: new_crate :),
		"�u�Y�j�n�[�ܵۤu�H�N�f���q�ܮw�h�X�ӡC\n",
		"�u�Y�j�s�R�p���O�S���Ѧ��S���ӡS\n",
		"�u�Y���D�R�֦A�h�h��ǤH��M���M�����F�C\n",
		"�u�Y���D�R�n��u�����@�ӭӨ� ... �O�� ...\n"
	}) );
		
	setup();
	carry_money("coin", 220);
}

int accept_fight()
{
	do_chat("�u�Y���D�R��Z�S�A�ƤF�ܡS�ڤ~�S���ض��\\�ҡC\n");
	return 0;
}

void relay_say(object me, string msg)
{
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "�u��") >= 0 ) {
		int amount;
		object money;

		if( amount = me->query_temp("wage_deserved") ) {
			money = new("/obj/money/coin");
			money->set_amount(amount);
			money->move(this_object());
			command("say �n�M�n ... �`�@�O" + chinese_number(amount) + "����M���M���A�C");
			me->delete_temp("wage_deserved");
			do_chat((: command, "give coin to " + me->query("id"):));
		}
		else do_chat("�u�Y���D�R�h�@�ӽc�l�G�Q������M�l�a���ߤT���C\n");
		return;
	}
}

void new_crate()
{
	object ob;
	
	if( !environment()
	||	sizeof(all_inventory(environment())) >= 15 ) return;

	ob = new(__DIR__"obj/crate");
	ob->move(environment());
	say("�u�Y���D�R�ޡT������f���p�ߤ@�I�M�O���L�a�F�T\n");
}
