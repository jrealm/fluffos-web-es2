// waiter.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int on_service = 0;

void create()
{
	set_name("���p�G", ({ "waiter", "snow_inn_waiter" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 21);
	set("long",
		"�@�Ӭ��G�Q�X�Y���~���p�٭p�M�����i���X�۩I�ȤH�M�A�i�H��\n"
		"list �ݥi�H�I�����M�� buy �򩱤p�G�I��C\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"���p�G���۵L��M��_�p����ӡC\n",
		"���p�G���Y�X�h��F��Ѧ�M���D�R�o�X�ѤѮ𤣿��M�u�Q�X�h�����C\n",
		"���p�G���D�R�����Ѫ������ͤ����D�n�I�F�S�M�֤F���Ѫ��o�̹�b��e�C\n",
		"���p�G���D�R�ȭ����ѫ�򦳪šM�̪�i���s�A�Ư໡��ťť�ܡS\n",
	}));
	set("merchandise", ([
		"/obj/food/dumpling": 50,
		"/obj/food/manto": 50,
		"/obj/food/pork": 30,
		__DIR__"obj/roast_chicken": 30,
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}


int accept_fight(object ob)
{
	do_chat("���p�G��F�Ӱ��y�M���D�R�ȭ��n���[���ܡM�p���ڥi���O���C\n");
	return 0;
}

mixed affirm_merchandise(object customer, string item_name)
{
	if( on_service )
		return notify_fail("���p�G�����۩۩I��L�ȤH�M�ЧA���@�|��C\n");
	return ::affirm_merchandise(customer, item_name);
}

private void handover(object customer, mixed item)
{
	on_service = 0;
	if( !customer || environment(customer)!=environment() ) {
		command("say �x�S��診��ȭ��H�O�S���I�F���H�S�����F ...");
		say("���p�G��ݥX�Ӫ�" + item->name() + "�S�ݤF�^�h�C\n");
		return;
	}
	command("say �ȭ��M�z��" + item->name() + "�ӰաT");
	message_vision("$N���q�p�кݥX�Ӫ�" + item->name()
		+ "�e��$n���e�C\n", this_object(), customer);
	::deliver_merchandise(customer, item);
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "�O�a�S���W�ӡT");
	say("���p�G��ۼp�г۹D�R" + item->name() + "�@���T\n");
	on_service = 1;
	do_chat((: handover, customer, item :));
}
