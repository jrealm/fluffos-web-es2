/*  garrison.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("�x�L", ({ "garrison" }) );
    set_attr("con", 19);
    set_attr("str", 20);
    set_race("human");
    set_class("fighter");
    set_level(17);

    set_skill("twohanded sword", 60);
    set_skill("parry", 60);
    set_skill("unarmed", 50);
    set_skill("dodge", 50);
    set_skill("blade", 50);

    set("long",
        "�@��t�d���@�a��v�w���x�L�M�L�̨��L�۷��V�m�M���ɭ�\n"
        "�]�[�J�x���@�ԡC\n");
    set("vendetta_mark", "authority");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("broadsword") )->wield();
}

void init()
{
    ::init();
    add_action("intercept", "go");
}

int intercept(string arg)
{
    if( (arg!= "north") || !this_player()->visible(this_object()) ) return 0;

    if( this_player()->query_level() >= 10 ) return 0;
    write( name() + "�N�A�d�F�U�ӡC\n");
    do_chat((: command, "say ���Ϥs�̪񦳵s��X�S�M�A�̨��O�����a�C":) );
    return 1;
}

int accept_fight(object ob)
{
    do_chat((: command, "emote ���F�����M���D�R�u�}�u�}�T�֦b�o���o���T":));
    return 0;
}
