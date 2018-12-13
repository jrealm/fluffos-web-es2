//yu.c
#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("����", ({ "yu tan","yu","tan" }) );
	set_race("human");
	set_level(1);
	set("gender", "male");
	set("age", 25);
	set("long",
"�@�ܮ����n���x, �ۥ��W�t���a��, ���Ѥ������K�s, ���R�M�j�R���{�C\n"
"���Ѹ򳽮a�W���Ʋ`, �ڶǻD�����K�s��~�~���@�L�h��, ���Ǥ��p�k��\n"
", �ѩ󤣪���ʤ�a��, �G�q�p�b���a���j�B�W����. ���a��䦳�\\, ��\n"
"���ѤS���n�Z��, �K�H���a�귽, �U��b���}�]�����ݳc���f�C\n"
	);
	set("merchandise", ([
		"/d/snow/npc/obj/blue_jacket": 5,
		"/obj/armor/fur_hat": 5,
		"/obj/bottle": 5,
	]));
	set("chat_chance", 5);
	set("chat_msg", ({
		"���ѳ���D: ��, �W�Ӥ몺�Q�����F�G�ʤK�Q��ջ�, ���� ���� !\n",
		"���Ѿa�b�������j�d�O�W, �C�Y���ۻy, ���G���b��p��.\n",
	}));
	setup();
	carry_object(__DIR__"obj/blue_jacket")->wear();
}

int accept_fight()
{
	do_chat((: command("emote �D: ��! ���m�Ǩ����ޯ�, ���R����i�O�����Ϥ��F���!") :));
	return 1;
}

void init()
{
	::init();
	if( !userp(this_player()) )	return;
	add_action("do_vendor_list", "list");

	do_chat(({
		"���ѯ��}�F�j�L�D: �o��" + this_player()->rank("respectful") + "�K�Ǧ�A��a!\n",
		"���ѦV�A���йD: �n�s�����, �ڳ��O�]�O�w���S��b��!\n",
	}));
	if( this_player()->query("level")<=5 )
		// cancel call_out to test, by dragoon
		//call_out((:
		message("whisper",GRN
"���ѧA�����䮨�n���D: �e�X�ѧھߨ�F�Ӧn�F���, �����I���N�e�A, ���N��a!\n"NOR,
		//	this_player()):),5);
		this_player());
}

int accept_object(object me,object ob)
{
	int tmp;
	object tmp_ob;
	if( !ob->query("money_id") && !userp(ob) ){
		do_chat(({
"���ѻ��D: �o.. ���M���O�Ȩ�, ���L�]�����w���H�Q�R, �u�O���§A��.\n",
"�����ਭ�N"+ob->name()+"���J�F�d�x����.\n",
		}));
		return 1;					// lv <=5, 1 coin is enough
	}								// lv >5, cost silver or gold
	if( ob->query("money_id")!="coin")
		tmp=1;
	if( me->query("level")>5 && ob->query("money_id")=="coin" )
		tmp=2;
	if( me->query("level")<=5 )
		tmp=3;
	switch(tmp){
		case 3:
		case 1:
			do_chat(({
"���ѻ��D: �n, �o��ȩx���N��, �o���N��N�e���A��!\n",
"���ѱN�@�i�֭��浹�F�A.\n",
			}));
			tmp_ob=new(__DIR__"obj/note.c");
			if( !tmp_ob->move(me) )	ob->move(environment(me));
			return 1;;
		case 2:
			do_chat("�o��ȩx�]���D�ڪ��s���ë~? �ݨӳo���N���ȴX�ӿ���, �n, �X���Ȩ�N��!\n");
			return 1;;
		default:	return 1;
	}
}
