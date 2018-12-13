// smith.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
        set_name("�K�K", ({ "smith" }) );
        set_race("human");
        set_level(13);
        set_stat_maximum("kee", 80);
        set_attr("str", 19);
        set_attr("cor", 17);
        set_attr("cps", 15);
        set_attr("dex", 18);

        set("long",
                "�@�Ө����ʧ����K�K�M�����L�a�u�@�ۡC\n"
                "�p�G�A�Q�R�@���K���M�i�H�� list �ݦ����ǪF��M�� buy �V�K�K�ʶR�C\n");

        set("merchandise", ([
                __DIR__"obj/hoe": 3,
                __DIR__"obj/shovel": 5,
                "/obj/area/obj/dagger": 10,
                "/obj/area/obj/shortsword": 5,
        ]));

        set("chat_chance", 5);
        set("chat_msg", ({
                "�K�K�N�@���N�����K���u��v�a�@�n���J�@�Ǫ����c���C\n",
                "�K�K�Τ⤤���K��b�K�z�W�ΤO�V���C\n",
                "�K�K���D�R���}�I�M�p�ߧO�S�ۤF�C\n",
                "�K�K���D�R�� ... �u��ڵ����a�F�C\n",
        }));
        setup();
        carry_object(__DIR__"obj/smock")->wear();
}

int accept_fight()
{
        do_chat("�K�K���F�����M���D�R���}�M�ڥ����ۡC\n");
        return 0;
}

void init()
{
        ::init();
        add_action("do_vendor_list", "list");
}
int accept_object(object who, object ob)
{
        object thing;
        if ( !ob->id("lo iron") ) return 0;
        call_out((:command("say ��I�n�s���b��, ��²��, ���W�N�i�H���n.\n"):),1);
        thing=new(__DIR__"obj/arrow");
        thing->move(who);
call_out((:message_vision("�K�K��谵�n���b�浹�F$N�C\n",this_player(),) :),2);
        return 1;
}



