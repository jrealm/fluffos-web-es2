// junkman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("�B����Y", ({ "junkman" }));
	set_race("human");
	set_level(2);

	set("age", 66);
	set("long",
		"�@����ܼ���B����Y�M�a�߬B�o�����͡M�p�G�A�@�N���U�o�ˤ@��\n"
		"�ѤH�L�n�@�I���ͬ��M�Ϊ̬O�@�N�����W���Ův�̸`�٤@�I�O����\n"
		"�M�Ч�A���W�h�l���F�赹�L�M�i�H�o��@�I�� civism�C\n");
	set("bounty/mortal sin", 5);
	set("chat_chance", 8);
	set("chat_msg", ({
		(: random_move :),
		(: command, "get all" :),
	}));
	setup();

	// Always flee.
	set_stat_notify("gin", 100);
	set_stat_notify("kee", 100);
	set_stat_notify("sen", 100);
}

int accept_fight()
{
	do_chat("�B����Y�S�X�`�Ȫ������M���D�R�o ... �y ... �ǤF�p�H�a ...\n");
	return 0;
}
/* �Ȯɨ��� d-Dragoon
void junk_ob()
{
	object ob;

	command("emote ����a�I�Y�M���D�R���� ... �y ... ���� ... ");
	foreach(ob in all_inventory()) {
		if( function_exists("stuff_ob", ob) )
			command("eat " + ob->query("id"));
		else if( ob->query("wear_as") )
			ob->wear();
		else if( ob->query("wield_as") )
			ob->wield();
		if( ob && !ob->query("equipped") ) destruct(ob);
	}
}

int accept_object(object me, object ob)
{
	do_chat((: junk_ob :));
//	if( !ob->query_amount() )
//		me->gain_score("civism", 1);

	return 1;
}
*/
