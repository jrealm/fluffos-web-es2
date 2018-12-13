// patrol_garrison.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("���ީx�L", ({ "patrol garrison", "patrol", "garrison" }) );
    set_race("human");
    set_class("fighter");
    set_level(15);
    set_skill("sword", 60);
    set_skill("parry", 60);
    set_stat_maximum("gin", 150);
    set_stat_maximum("kee", 150);

    set("pursuer", 1);
    set("long",
        "�@��t�d���@�a��v�w���x�L�M�L�̨��L�۷��V�m�M���ɭ�\n"
        "�]�[�J�x���@�ԡC\n");
    set("vendetta_mark", "authority");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    // Wiled the sword when protecting someone. (Just for cool :P)
    carry_object( STOCK_WEAPON("broadsword"));
}


int accept_fight(object ob)
{
    do_chat((: command, "emote ���F�����M���D�R�u�}�u�}�T�֦b�o���o���T":));
    return 0;
}

void protect(object ob)
{
    command("emote �j�ܡR�ϤF�ϤF�T���ѤƤ餧�U�������H�x���S�ǩR�ӡT");
    command("wield sword");
    guard_ob(ob);
}
