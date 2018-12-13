// gammer.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("�M���ѤӱC", ({ "blind gammer", "gammer", "__ID_GAMMER__" }) );
	set_attr("dex", 29);
	set_attr("con", 21);
	set_attr("cor", 22);
	set_attr("str", 19);
	set_race("human");
	set_class("thief");
	set_level(44);

	set_skill("staff", 40);
	set_skill("stealing", 70);
	set_skill("dodge", 90);
	set_skill("blade", 30);
	set_skill("sword", 30);
	set_skill("unarmed", 50);
	set_skill("dagger", 70);
	set_skill("secondhand dagger", 70);
	set_skill("killerhood", 60);
	set_skill("force", 90);
	set_skill("regular force", 100);
    map_skill("force", "regular force");

	advance_stat("gin", 270);
	advance_stat("kee", 180);
	advance_stat("sen", 90);

	set("gender", "female");
	set("age", 66);
	set("long",
		"�@�ӽM�F�������ѤӱC�M���y�K���M���O�o���H�@�ؿˤ����Pı�C\n");

	set("chat_chance", 8);
	set("chat_msg", ({
		"�M���ѤӱC���a���D�R���_�S�O�A�ܡS\n",
		"�M���ѤӱC���ۦզ����G�b��ť����C\n",
		(: random_move :)
	}) );

	set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		"�M���ѤӱC�s�D�R���_�T���c�H�b�ۭt�C�C���T�֥X�ӰڡT\n",
		(: random_move :),
	}) );
	set_stat_notify("kee", 40);

	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_object(__DIR__"obj/cane")->wield();
	carry_object(__DIR__"obj/syndicator")->wield("secondhand dagger");
}

private void give_coin(object who)
{
	object ob;

	if( environment(who) != environment() ) return;
	ob = new(__DIR__"obj/coin");
	if( !ob->move(who) )
		ob->move(environment());
}

void relay_say(object ob, string arg)
{
	int tmp = ob->query_temp("try/fon");
	// communicate with arbao
	if( !userp(ob) ){
		if( ob->id("__ID_ARBAO__") ){
			this_object()->delete("chat_msg");	// stop chat_msg
			this_object()->delete("chat_chance");
			if( strsrch(arg,"���Ӧn�F")>= 0 ) {
				do_chat((:command(
"say ���u�~�s�ڪ��_, �p�O���w�W�h�E�����p�l�F�a."):));
				return;
			}
			if( strsrch(arg,"�O")>= 0 ){
				do_chat(({
(:command("say �L�Q���p, �i�H, ������O�L���l�n�����A�ݷݳ��F��.
�o�˥L�a�P���̪�����~��@���Į�."):),
				}));
				call_out((:message_vision("�M���ѤӱC����, ��L�����F.\n",this_player()):),4);
				call_out((:destruct(this_object()):),6);
				return;
			}
		}
	}
	if( !tmp || tmp==0 ){
		if( arg=="������" && ob->query_temp("thief_qualified") ) {
			command("giggle");
			command("pat " + ob->query("id"));
			if( (string)ob->query_class() != "commoner" ) return;
			ob->set_class("thief");
			tell_object(ob, "�A���������@�W�s��F�C\n");
			ob->improve_skill("sneak", 20);
			ob->improve_skill("stealing", 20);
			do_chat(({
				"�M���ѤӱC���D�G��F�A�o�ӵ��A�C",
				(: give_coin, ob :),
				"�M���ѤӱC���D�G�p�G�A�Q�ǥ��ơA���o�F�赹���ݡC\n",
			}));
			return;
		}
		if( strsrch(arg, "���_") >= 0 )
			do_chat((: command, "say ���_�S�A�����_�b���̡S" :));
		else switch(random(10)) {
			case 0: do_chat((: command, "shake" :));
			case 1: do_chat((: command, "?" :));
			case 2: do_chat((: command, "steal coin from " + ob->query("id") :));
		}
		return;
	}
	switch(tmp) {
		case 8:
			if( strsrch(arg,"�h")>=0 ) {
				do_chat(({
"�M���ѤӱC�㤣�i�K, �ܹD: �u, �u, �u, �ڤ��Qť��o�өm.\n",
"�M���ѤӱC���ۻy�����}�F, �A��������ť��ƻ򦺰�, ���_, �ƻ򤳪�.\n",
"�A�Q��]�\\�ѤӱC���]�k�ા�D�������N��.\n",
				}));
				ob->set_temp("try/fon",10);
			}
			break;
		case 16:
			if( strsrch(arg,"����")>=0 ) {
				do_chat(({
"�M���ѤӱC���D: �ڨ��������b�T�~�h�e�Q�h�FĪ���`���F, �A�ݥL��ԣ?\n",
"�M���ѤӱC�S��㤣�𪺻��D: �L�n���O�Q�h�FĪ�ˤF, �̥L�ѤU�Ĥ@�����\\�����|
�Q�H����, �o���O�h�FĪ���r�`����.\n",
"�ݤF�b���٬O���M����, �A���T�ôb, �����h�FĪ��o��Ʀ���ʸ�.\n"
				}));
				ob->set_temp("try/fon",18);
			}
			break;
		case 45:
			if( strsrch(arg,"�p�޽�")>=0 ) {
				do_chat(({
"�M���ѤӱC��D: �o..�o.. �n�[�S���H�o�˥s�ڤF.. �ݨӳo�u���O���Y�l�g���F.\n",
"�A�ԲӪ��������������].\n", 
"�M���ѤӱC�I�u�F�@�U.\n",
(:command("say �p�l, ���ѱC�l�@�Ӧ�, �h�i�D�m�h��, �ѱC�l���|�A�h��L�M��
�F, ���r������, �L�i�O�Q��o�F�d��."):),
				}));
				ob->set_temp("try/fon",48);
			}
			break;
		default:        break;
	}
}

int accept_fight()
{
	do_chat((: command, "?" :));
	return notify_fail("�M���ѤӱC��A���Y�L�@ ...�C\n");
}

void init()
{
    if( environment(this_object())->query("connect-p") ) {
	command("say �f���F, �ӳܤf��...\n");
        message_vision("$N�w�w���^�j������C\n", this_object());
        this_object()->move("/d/snow/square");
        return;
    }
	// Dont call original init() to check autofight.
	if( !is_chatting() && this_player()->query_temp("try/fon")==43 ){
		do_chat(({
			"�A����F�ѤӱC, ���X�}���@��.\n",
			"�ѤӱC�ܹD: �ƻ�}��, ����.\n",
		}));
	}
}

private void ask_join(object player)
{
	if( !player || environment(player)!=environment() ) return;

	if( player->query_class() != "commoner" )
		command("say �� ... �H�ѤF�M�s�H�����ޤl���`�`�ᱼ�C\n");
	else {
		command("whisper " + player->query("id") + 
			" �n�å�M���M���A���h�F�S�Q�����p���O���O�S�s�n�u�������v�ڴN���A�J�o�� ...");
		player->set_temp("thief_qualified", 1);
	}
}

int accept_object(object player, object ob)
{
	if( player->query_temp("try/fon")!=43 ){
		if( !ob->id("annatto comb") ) return 0;
		command("say �x�S�o ... �o�O ... �ڪ��ޤl�T");
		do_chat((: ask_join, player :));
		return 1;
	}
	if( ob->id("__ID_CHALLIE__") )	{
		do_chat(({
			"�M���ѤӱC��D: �A�o�O�ۧڲ��M�ݤ���, �Q���F�ڶ�?\n",
			"�A�Q��ѤӱC���ʺ�, �]�\\�i�H�Ϧo�۫H����}��.\n"
		}));
		player->set_temp("try/fon", 45);
		return 1;
	}
}
