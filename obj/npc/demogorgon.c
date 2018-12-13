// demongorgon.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name( HIW "����" NOR, ({ "demogorgon" }) );
        set_level(100);
        set_race("human"); 
       set("long",
                "    �������N�Ŧa���b�A���e�A�L���j�����߸�@�ѥO�H������\n"
                "�i�ȱ������o�A�X�G�ݤ��L��ӡA�A���߸̦��G���@���n���b�i\n"
                "�D�A�R�u �����} �I�I�v\n");

        set("age", 500);

        advance_stat("kee",900);
        advance_stat("gin",900);

        set_attr("str",35);
        set_attr("dex",42);
        set_attr("con",35);
         set_attr("spi",45);
        set_attr("cor",45);

        setup();

}

void start_shutdown()
{
        if( geteuid(previous_object()) != ROOT_UID ) return;

        message("system",
                HIR "\n�Ať��ѪŤ��ǨӤ@�}�i�Ȫ��H�� ....\n\n"
                HIW     "����" HIR "�N�ŧC�I���n���ǤJ�A���դ��G\n\n"
                        "\t\t�Q�n�R���A�A���٦��������i�H�������}�a�I�I\n\n"
                        "\t\t���M���ܡA��G�ۦ�t�d���\n\n" NOR,
                users() );
        call_out("countdown", 240, 61);
}

private void countdown(int sec)
{
        sec--;
        if( sec > 59) {
                message("system",
                        HIW "\n����" HIR "�N�ŧC�I���n���Ƕi�A���դ��G\n\n"
                "\t\t�A���٦�" + chinese_number(sec) + "�����i�H���}�C\n\n"
                    "\t\t���n�R���A�N�ոլݧa�I�I\n\n" NOR,
                        users() );
                call_out("countdown", 49, 11);
        }else if( sec > 0) {
                message("system",
                        HIW "\n����" HIR "�N�ŧC�I���n���Ƕi�A���դ��G\n\n"
                                "\t\t�A���٦�" + chinese_number(sec) + "�������ɶ��i�H�k�I�I\n\n"
                                "\t\t���Q�����N���ְk�a�I�I�I\n\n" NOR,
                        users() );
                call_out("countdown", 1, sec);
        }
        else {
                message("system",
                        HIW "\n����" HIR "�μ��㪺�n���H���D�G\n\n"
                            "\t\t�Ѱڡ� �a�ڡ�  ���ڡ� \n\n" NOR,
                        users() );
                call_out("do_shutdown", 2);
        }
}

private void do_shutdown()
{
        message("system",
                HIW "\n\n����" HIR "�μ��㪺�n���ܹD�R\n\n"
                HIW "\t\t�q �q �M �� �@ �_ �U �a �� �a ����� �T\n\n"
                HIR "\t\t�n���@���A�Ѫťߨ��ܱo����A��....�A���e���@�����ܱo���...\n\n"
                        "\t\t�Ҧ����@�����b�������J����....\n\n"
                        "\t\t�M��A�����e�O�@���·t....�L��ɪ��·t....\n\n" NOR,
                users() );
        shutdown(0);
}

void die()
{
        object ob;

        if( !ob = query_temp("last_damage_from") )
                ob = this_player(1);

        if( !ob ) return;

        message("system",
                HIR "\n\n�Ať��@�n�a�ۼ���B�宣�B�P���~�몺�H���n�T����ӤѪšC\n\n"
                HIW "����" HIR "�R�צa�q�ۡR�i�c��" + ob->short() + "�M�ڤ@�w�|����������\n\n"
                        "�M��@�D�¦���K�I�S�۽ĤW���ݡM�j�a�S��_�F���R�C\n\n" NOR,
                users() );
        
        destruct(this_object());
}
