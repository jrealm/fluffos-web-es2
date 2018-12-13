// innkeeper.c

#include <localtime.h>
#include <npc.h>

inherit F_VILLAGER;

void open_inn();
void close_inn();

int on_business = 0;

void create()
{
	mapping gt;

	set_name("�x�d", ({ "innkeeper", "keeper" }) );
	set_race("human");
	set_level(4);

	set("age", 52);
	set("long", "�o��K�O�o�a�ȴ̪��x�d�M�ݰ_�Ӻֺ֮������O�ӦѦn�H�C\n");
	set("schedule", ([
		700: (: open_inn :),
		2200: (: close_inn :),
	]));
	setup();
	carry_money("coin", 160);

	gt = NATURE_D->game_time(1);
	if( gt[LT_HOUR] < 7 || gt[LT_HOUR] > 22 ) on_business = 0;
	else on_business = 1;
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat( (: command, "say �w��T�w��T�и̭����T" :) );
}

void relay_emote(object from_ob, string verb)
{
	command("smile");
}

int accept_fight(object player)
{
	do_chat((: command, "say �o��" + player->rank("respectful")
	 + "�u�R�}�����M�p�Ѩ��٭n���ͷN�O�C\n":));
	return 0;
}

void accept_kill(object player)
{
	object ob;

	// �w�g�b���[�F�A���H kill �x�d�A��������ơC
	if( is_fighting() ) return;

	// �}�l���[�A���۱ϩR( �o�̥� command() �|���ۥX�� )
	command("emote �j�s�R���H���M�ϩR���T");

	// �ݬݲ{�����S���x�L�b�H������ present() �|�Ǧ^�ж����Ĥ@�өx�L�C
	ob = present("garrison");

	// �S�����ܡA�s�@�ӥX�ӡC
	if( !ob ) {
		ob = new(__DIR__"patrol");
		ob->move(environment());

		// ��N�x�L���X�{�A�`�N�e���x�d�w�g�� command() �ۥX�n�F�A�p�G
		// �� do_chat() ��T���n��U�@�� heart beat �~�|�X�ӡC
		tell_room(environment(), "���ީx�Lť��s�n�M�]�F�L�ӡC\n");
	}

	// protect() �w�q�b�x�L���W�A�]�O�j�n�W�W�X�y�����ܡC
	ob->protect(this_object());

	// �o�O���x�L���U�⬰�j�C
	ob->kill_ob(player);
}

void open_inn()
{
	command("emote ���F�Ө���M���D�R�Ϊ��u�n�M�}�����ͷN�a�C");
	environment()->open_door("east");
	environment()->open_door("west");
	environment()->set("no_fight", 1);
}

void close_inn()
{
	object ob;

	command("say ��.. �G��F�M���L�a�M�U��ȭ�����Ц��C");
	command("emote �N�A�e�X�ȴ̡C");
	environment()->close_door("east");
	environment()->close_door("west");
	environment()->set("no_fight", 0);
	foreach(ob in all_inventory(environment()) ) {
		if( ob==this_object()
		||	!ob->is_character()
		||	ob->id("snow_inn_waiter") ) continue;
		ob->move(environment()->query("exits/east"));
	}
}
