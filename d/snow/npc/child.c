// child.c

#include <npc.h>

inherit F_VILLAGER;

void timeto_eat();

void create()
{
	set_name("���_", ({ "arbao", "__ID_ARBAO__" }) );
	set_attr("spi", 18);
	set_attr("int", 19);
	set_attr("dex", 19);
	set_attr("con", 17);
	set_race("human");
	set_class("thief");
	set_level(10);

	set_skill("stealing", 40);
	set_skill("dodge", 35);
	set_skill("lightswift", 45);
	set_skill("dagger", 40);
	set_skill("sword", 30);
	
	map_skill("dodge", "lightswift");

	set("age", 16);
	set("gender", "female");
	set("long",
		"�o�ӤQ���B�������p�h�Q�N�O�u���_�v�F�M�o���W���M��۲ʥ�\n"
		"��A�M���o�Q���O�Ӭ��H�F�l�M�@�����L�L���j�������L�L�a��\n"
		"�ۡM�٤��ɨn�ۧA�ݡM�ϧA���Tı�o���ǵo�~�C\n");

	// set arbao to consume food -dragoon
	set("schedule", ([
	    700: (: timeto_eat :),
	    1200: (: timeto_eat :),
	    1900: (: timeto_eat :),
	]));

	setup();
	carry_money("coin", 30);
	carry_object(__DIR__"obj/blue_cloth")->wear();
	carry_object("/obj/area/obj/dagger")->wield();
}

int hungry = 1;

void timeto_eat()
{
	this_object()->consume_stat("food", 
	    this_object()->query_stat("food")+1);
	return;
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	
	if( this_player()->query_temp("try/fon")==10 ){
		do_chat("���_�}�ߪ��V�A�n�n��, ��ݹD: ����h�j���F�� ? �L�n���n?\n");
		//this_player()->set_temp("try/fon",13);
	}

	// if trying fon, wont join thief
	if( this_player()->query_temp("try/fon") )
		return;

	if( hungry )
		do_chat((: command, "say �� ... �ڨ{�l�n�j�M���S���Y���S" :));
	else if( this_player()->query_class() == "thief" ) {
		do_chat(({
			"���_��ۧA�A���M���D�G�x�H�A���O�W�����ڪF��Y������ ...\n",
			"���_�L�����D�G�S�b�o�̹J��A�A�u���C\n"
		}));
	}
	else
		do_chat((: command, "say �N ... �O���C�C���D�ڦb�o�� ..." :));
}

private void give_comb(object player)
{
	object comb;

	if( !player || environment(player)!=environment() ) {
		command("say �x ... �H�O�S");
		return;
	}
	comb = new(__DIR__"obj/comb");
	comb->move(this_object());
	command("give comb to " + player->query("id"));
}

private void exchange(string food_name, object player)
{
	set_stat_current("food", 0);
	command("eat " + food_name);
	if( !player || environment(player) != environment() ) return;

	command("say ��F ... ���ӥզY�A���F��M�o�Ӱe���A�a�T");
}

private void do_follow(object me,object ob)
{
	if( !ob->move(me) )	ob->move(environment(me));
	message_vision("���_��@�󪫫~�����F$N.\n",me);
	command("follow "+me->query("id"));
	me->set_temp("try/fon",43);
}

int accept_object(object me, object ob)
{
	if(me->query_temp("try/fon")!=40){
		if( !hungry || !inherits(F_FOOD, ob) ) {
			do_chat((: command, "say ���ڳo�ӷF���S" :));
			return 0;
		}

		hungry = 0;
		command("smile");
		command("say �� .. �Ӧn�F�T�u���§A�T ...");
		do_chat(({ (: exchange, ob->query("id"), me :), (: give_comb, me :) }));
		return 1;
	}
	if(ob->id("__ID_CHALLIE__")){
		do_chat(({
			"���_�J�ӬݤF�ݯ}��.\n",
			"���_���D: �o....��..�ڴN���D��h�a�L��..��...�ݷ�..\n",
			"���_�ˤߪ����F�_��.\n",
			"���_���F�n�@�}�l, �~�S��A���D: ���§A, �ڭ̳o�N�h�������a.\n",
			(: do_follow,me,ob :),
		}));
		hungry=0;		// stop talking about another quest by init
		return 1;
	}
}

void relay_say(object ob,string msg)
{
	int tmp = ob->query_temp("try/fon");

	// communicate with gammer
	if( !userp(ob) ){
		if( ob->id("__ID_GAMMER__") ){
			if( strsrch(msg,"���|�A�h��L�M��")>= 0 ) {
				do_chat(
(:command("say �u��! ���Ӧn�F!"):));
				return;
			}
			if( strsrch(msg,"���w�W�h�E��")>= 0 ) {
				do_chat(({
"���_�y���F�@�U.\n",
(:command("say �O."):),
				}));
				return;
			}
			if( strsrch(msg,"���A�ݷݳ��F��")>= 0 ) {
				all_inventory(environment())->set_fon_temp(this_player());
				call_out((:do_chat(
"���_���D: �����߱����n, �ڭn�h�����o, �ЧA�����ڥh�i�D�h�j���o�Ӧn����, 
�h�§A�F.\n"):),4);
				call_out((:do_chat(
"���_����, �]��榣���l�۽M���ѤӱC���h.\n"):),5);
				call_out((:destruct(this_object()):),8);
			}
		}
		return;
	}
	// communicate with user
	switch(tmp){
		case 0:
		case 1:
			if( (strsrch(msg, "�h�j�����~����|�^��") >= 0) ) {
				do_chat(({
"���_�y�@���M���D�G�A .. �A�����O�ʤs�����h�E���h�j���ܡS\n",
"���_���D�G�o�i�V�F�M�L�o�ɭԦ^�ӡM�C�C�w�n���F�L�� ... ����O�S\n",
"���_���D: �o��"+ob->rank("respectful")+"�i�_���p�k�l�@�Ӧ�?\n",
				}));
				ob->set_temp("try/fon",3);
			}
			break;
		case 3:
			if( strsrch(msg,"�i")>=0 || strsrch(msg,"�n")>=0 ){
				do_chat(({
"���_�D: �p�G�A��J�W�h�j������, �ЧA�i�D�L�Ȯ��٬O�O�ӳ��F��, ���M, �n�O�L
�M�C�C�_�F�Ĭ�,�ڷ|�ܬ�����.�٦�.....\n",
"���_�����y, ���n�D: ...�ЧA�i�D�L���_�ܷQ�L....\n",
				}));
				ob->set_temp("try/fon",5);
			}
			break;
		case 10:
			if( strsrch(msg,"����")>=0 || strsrch(msg,"�n")>=0 ) {
				do_chat(
"���_�y�W�x�_�}�}���w, ����۬h�j��, �ӫ�ݹD: ���W���ƻ���D��?\n"
				);
				ob->set_temp("try/fon",13);
			}
			break;
		case 13:
			if( strsrch(msg,"����")>=0 ) {
				do_chat(({
"���_�D: ��, �h�j����A���F�o��Ƴ�, �����̰Q���F, �������ť, �H�a�����n
�z�o�F.\n",
"���_�D: �ڷݷݥs����, ����W���n�ͺ٥L����, �@�����\\ <�N�P��> ���B����, ��
�����M�s�L����, �i�O�L�ǷP���ܦn, �j�a�����D�O.\n",
"���_��M�������F�_��, �D: �i�O�T�~�h�e�ݷݤ����Q�ַt��, ���b�Ѩ���~��...\n",
"���_���۹D: �H�a�����D�F, ��..  �h�j���~������j, �@�w�O�o�ڷݷݻ�������.\n",
				}));
				ob->set_temp("try/fon",15);
			}
			break;
		default:	break;
	}
}

void set_fon_temp(object me)
{
	if( me->query_temp("try/fon")!=48 )	return;
	me->set_temp("try/fon",50);
}
