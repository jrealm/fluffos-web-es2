// girl.c

#include <npc.h>

inherit F_FIGHTER;

object *dest = ({});

void create()
{
    set_name("�զ�k�l", ({ "girl" }) );
    set_attr("con", 23);
    set_attr("str", 23);
    set_attr("spi", 27);
    set_attr("int", 22);
    set_attr("dex", 26);
    set_race("human");
    set_class("fighter");
    set_level(55);

    set_skill("sword", 140);
    set_skill("dodge", 120);
    set_skill("parry", 120);
    set_skill("blade", 70);
    set_skill("dagger", 70);
    set_skill("unarmed", 90);
    set_skill("force", 80);
    set_skill("celestial force", 80);
    map_skill("force", "celestial force");
    set("defensive", 60);

    advance_stat("gin", 160);
    advance_stat("kee", 160);
    advance_stat("sen", 80);

    set("age", 19);
    set("gender", "female");
    set("long",
        "�@�Ө���զ窺�k�l�M�ݰ_�Ӧ~�����|�W�L�G�Q���M�e�������Ƭ��M�o\n"
        "�O���@���F�q����M�O�H���M�������V�C\n" );
    setup();
    carry_object(__DIR__"obj/white_dress")->wear();
    carry_object(__DIR__"obj/slasher_sword")->wield();
}

void relay_emote(object ob, string verb)
{
    do_chat((: command, "shake" :));
}

void attack_intruder(object ob)
{
    if( !ob || member_array(ob, dest)==-1 ) return;
    dest -= ({ ob });
    if( environment(ob) != environment() ) return;
    if( wizardp(ob) ) {
	command("say ��ӬO" + ob->name() + "�j�H�A�p�k�l�A�~�_�ǡA�ٽШ��̡C");
	return;
    }
    command("say �A�u�O���n�R�F�T\n");
    kill_ob(ob);
    ob->fight_ob(this_object());
}

void listen_request(object ob)
{
    set("pending_requester", ob);
    command("hmm");
    command("say �A�Q�n����S���a�C");
}

int accept_object(object who, object ob)
{
    if( ob->id("bronze hairpin") ) {
        command("say �o ... �o�O�ڪ��v¯�T�ٵ��ڡT");
        dest -= ({ who });
        if( is_fighting(who) ) {
            remove_killer(who);
            who->remove_killer(this_object());
        }
        do_chat( (: listen_request, who :) );
        return 1;
    } else {
        command("say �o�O����}�����K�S���}�T");
        return 0;
    }
}

void drop_invitation()
{
    object ob;

    command("say ��T�ڹD�O����S���F�ֺu�a�T");
    ob = new(__DIR__"obj/invitation");
    ob->move(this_object());
    command("drop invitation");
    delete("pending_requester");
}

void relay_say(object ob, string msg)
{
    if( ob==this_object() ) return;
    if( ob != query("pending_requester") ) 
        do_chat((: command, "say �o�̨S���A���ܪ��l�a�M���ڳ��L�T":));
    else {
        if( msg!="�^����" ) {
            do_chat((: command, "say �o�تF��ڨS���M���@�ءT" :));
            return;
        }
        do_chat((: drop_invitation :));
    }
}

void init()
{
    ::init();
    if( this_player() && (!this_player()->query_temp("hairpin_quest")) ) {
        do_chat((: command, "say �A�O�֡S�u�T�u�X�h�T���M�ڱ��F�A�T" :));
        if( member_array(this_player(), dest)==-1 ) {
            dest += ({ this_player() });
            call_out((: attack_intruder, this_player() :), 5);
        }
    }
}
