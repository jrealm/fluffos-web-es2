// teacher.c

#include <npc.h>

inherit F_VILLAGER;

string *literate_text = ({
    "�H����", "�ʥ���",
    "�ʬ۪�", "�߬ۻ�",
    "�e����", "�ʤD�E",
    "�Ф��D", "�Q�H�M",
    "���s��", "�ܾF�B",
    "�l����", "�_���V",
    "�u�P�s", "���q��",
    "�Ф��l", "�W�Ѵ�",
    "�i����", "�����L",
    "�Ф��Y", "�v���k",
    "���H�l", "��֮�",
    "�ˮv��", "��§��",
});

int text_cnt = 0;
object picked_student;

void teach_literate();
void pick_student(object ob);
void cancel_pick(object ob);

void create()
{
    set_name("���h��", ({ "wang whaiz", "wang", "whaiz" }) );
    set_race("human");
    set_level(5);
    set_stat_maximum("sen", 50);

    set_skill("literate", 60);
    set("long",
        "���h�۬O��W�����~���W�l�M�e�X�~�W�ʦҸո��ġM�I�����ӤҤH�L�@\n"
        "�M�]���d�b�a�m�A��M���v�L�ơM�K�}�F���p�ѱ���W�ĤlŪ�ѡC\n");
    set("chat_chance", 8);
    set("chat_msg", ({
        (: teach_literate :)
    }));
    setup();
}

void init()
{
    add_action("do_sit", "sit");
}

int do_sit(string arg)
{
    // add by dragoon
    if( this_player()->query_skill("literate") > 29 ) 
	return notify_fail("�A��Ū���Ѧr�ڰ򤣿��A���ݭn�Ať�T�r�g�F�C\n");
	
    if( this_player()->query_temp("pending/sit_learning_literate") )
        return notify_fail("�A�w�g���۱M��ť���F�C\n");
    message_vision("$N��F�@�ӪŦ짤�F�U�ӡM�}�l��ۤ��Ѯv��ѡC\n",
        this_player() );
    this_player()->set_temp("pending/sit_learning_literate", 1);
    return 1;
}

void teach_literate()
{
    object *students, ob;
    string txt;

    if( text_cnt >= sizeof(literate_text) ) {
        command("say �� ... �@���ФӦh�A�̤]�O����M�n�a�M�ڭ̦A�q�Y�Ʋߤ@���C\n");
        text_cnt = 0;
    }
    txt = literate_text[text_cnt++];
    command("say �j�a��ۧک��R" + txt + "�C\n");

    students = all_inventory(environment());
    foreach(ob in students)
    {
	if( !ob->query_temp("pending/sit_learning_literate")
	||  !living(ob)
	||  ob->is_fighting()
	||  ob->query_skill("literate",1) >= 30 ) continue;

	ob->improve_skill("literate", random(ob->query_attr("int")+1));
	message_vision("$N��۩��D�R" + txt + "�C\n", ob);

	/* �D��ѥͪ����� */
	// �[��random, ���M�C���@�y�N�� -Dragoon
	if( interactive(ob) && random(10) > 7 
	&&  ob->query_class()=="commoner"
	&&  ob->query_skill("literate") >= 5
	&&  member_array(ob->query_race(), ({
		"human", "woochan", "jiaojao", "rainnar"
	    })) != -1
	&&  ob->query_attr("int") > random(20) )
	    do_chat( (: pick_student, ob :) );
    }
}

int accept_fight()
{
    do_chat("���h�ۻ��D�R�o ...�Z�\\�ڥi�O�b�I���|�M�o��B�ͤ��p�h��ڭ̮a�����Y���R���R�S\n");
    return 0;
}

string rank(string politeness, int raw)
{
    if( raw ) return ::rank(politeness, raw);
    switch(politeness) {
        case "self": return "�p��";
        case "respectful": return "���Ѯv";
        default:
            return ::rank(politeness, raw);
    }
}

int accept_info(object ob, string type)
{
    return type=="skills";
}

int acquire_skill(object who, string skill)
{
    if( skill=="literate" ) {
	command("say �QŪ���Ѧr�ܡS�b�o�̧���(sit)ť�a�C\n");
	command("smile");
	command("say Ū�ѥi���e���M���L�ǤF�h�֤@���l���O�A���C\n");
	return 1;
    }
    return 0;
}

void pick_student(object ob)
{
    if( ! (ob && present(ob) && interactive(ob)) ) return;

    command("say " + ob->name() + "�A�A�b�ڳo���Ѧ��@�q�ɶ��F�C\n");
    command("say �ڬݧA��Ū�ѻᦳ����A�ѥ��]�����C\n");
    command("say �Q���Q�M�Ѯv�@�ˡA��@�Ӯѥ͡H\n");

    ob->set_temp("pending/picked_by_whaiz", 1);
    call_out( (: cancel_pick, ob :), 20);
}

void cancel_pick(object ob)
{
    if( ! ob ) return;

    ob->delete_temp("pending/picked_by_whaiz");
    if( present(ob) ) {
	command("pat " + ob->query("id"));
	command("say �]�}�A�H�U���ӡC");
    }
}

void make_new_scholar(object ob)
{
    if( !ob || !present(ob) || !interactive(ob)) return;

    ob->set_class("scholar");
    command("smile");
    tell_object(ob, "( �A�����@��ѥ� )\n");
}

void relay_say(object who, string msg)
{
    if( ! who->query_temp("pending/picked_by_whaiz") ) return;
    if( member_array(msg[0..1], ({"�Q", "�O", "�n"})) != -1 ) {
	do_chat((: make_new_scholar, who :));
	who->delete_temp("pending/picked_by_whaiz");
    }
}
