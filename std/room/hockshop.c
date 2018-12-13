/*  hockshop.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit ROOM;

static object storage;

void remove()
{
    if( storage ) destruct(storage);
}

void setup()
{
    ::setup();
    seteuid(getuid());
    if( !storage ) {
        storage = new(__DIR__"hockshop_storage");
        storage->set("shop_ob", this_object());
        set("storage_ob", storage);
    }
}

void init()
{
    add_action("do_value", "value");
    add_action("do_pawn", "pawn");
    add_action("do_sell", "sell");
    add_action("do_retrieve", "retrieve");
    add_action("do_list", "list");
    add_action("do_buy", "buy");
    add_action("do_store", "store");
}

string value_string(int value)
{
    if( value < 1 ) value = 1;
    else if( value < 100 )
        return chinese_number(value) + "���";
    else
        return chinese_number(value/100) + "��"
            + (value%100? "�S" + chinese_number(value%100) + "���": "");
}

void pay_player(object who, int amount)
{
    object ob;

    if( amount < 1 ) amount = 1;
    if( amount/100 ) {
        ob = new(SILVER_OB);
        ob->set_amount(amount/100);
        if( !ob->move(who) ) ob->move(environment(who));
        amount %= 100;
    }
    if( amount ) {
        ob = new(COIN_OB);
        ob->set_amount(amount);
        if( !ob->move(who) ) ob->move(environment(who));
    }
}

int do_value(string arg)
{
    object ob;
    int value;

    if( !arg || !(ob = present(arg, this_player())) )
        return notify_fail("�A�n�����򪫫~����Q�����S\n");

    if( ob->query("money_id") )
        return notify_fail("�o�O�u���v�M�A�S���L�ܡS\n");

    value = ob->query("value");
    if( !value ) printf("%s�@�夣�ȡC\n", ob->query("name"));
    if( ob->query("sinister") )
        printf("%s����%s�C\n���O�o�ئ��H���W���˷��F���Q�ܤ��@�N���C\n"
            "���(pawn)�ν��_(sell)�u��o��%s�C\n",
            ob->query("name"), value_string(value), value_string(value / 100 ));
    else 
        printf("%s����%s�C\n�p�G�A�n���(pawn)�M�i�H����%s�Τ@�i���C\n�p�G���_(sell)�M�i�H����%s�C\n",
            ob->query("name"), value_string(value),
            value_string(value * 60 / 100), value_string(value * 80 / 100));

    return 1;
}

int do_pawn(string arg)
{
    object ob, stamp;
    int value;

    if( !arg || !(ob = present(arg, this_player())) )
        return notify_fail("�A�n����򪫫~�S\n");

    if( ob->query("money_id") )    return notify_fail("�A�n��u���v�S\n");

    value = ob->query("value");
    if( !value ) return notify_fail("�o�˪F�褣�ȿ��C\n");

    if (ob->query("no_sell")) return notify_fail("�o�˪F�褣����C\n");

    message_vision("$N�⨭�W��" + ob->query("name") + "���X�Ө��F"
        + value_string(value * 60 / 100) + "�M���o�@�i���C\n", this_player());

    if( ob->query("sinister") ) {
        int v;
        message_vision("��Q�©^��o�ئ��H���W���˷��F��ܤ����@�a���U�F ...\n", this_player());
        v = value / 100;
        if( v > 100 ) v = 100;
        pay_player(this_player(), v);
    }
    else
        pay_player(this_player(), value * 60 / 100);

    ob->move(storage);
    stamp = new(__DIR__"obj/pawn_stamp");
    stamp->set("pawned_item", ob);
    stamp->set("long", "������\n    " + this_player()->name(1)
        + "���" + ob->name() + "�A" + ob->query("unit")
        + "�W�M�}��ʷl�����C\n    ū�^ (retrieve) ���I" + value_string(value * 120/100)
        + "��M�@�����M�@���f�C\n");
    stamp->move(this_player());

    return 1;
}

int sell_item(object ob)
{
    int value;

    if( ob->query("money_id") )    return notify_fail("�A�n��u���v�S\n");
    value = ob->query("value");
    if( !value ) return notify_fail("�o�˪F�褣�ȿ��C\n");

    if (ob->query("no_sell")) return notify_fail("�o�˪F�褣���C\n");

    message_vision("$N�⨭�W��" + ob->query("name") + "�汼�C\n",
        this_player());

    if( ob->query("sinister") ) {
        int v;
        message_vision("��Q�©^��o�ئ��H���W���˷��F��ܤ����@�a���U�F ...\n", this_player());
        v = value / 100;
        if( v > 100 ) v = 100;
        pay_player(this_player(), v);
    }
    else
        pay_player(this_player(), value * 80 / 100);

    ob->delete("sinister");

    if( storage ) {
        int s;

        // Make a simple storage management, when we have more goods in
        // storage, only keeps higher price goods.
        s = sizeof(all_inventory(storage));
        if( value >= (s * 50) ) {
            ob->add("pawned_time", 1);
            ob->move(storage);
        }
        else destruct(ob);
    }
    else destruct(ob);

    return 1;
}

int do_sell(string arg)
{
    object ob;

    if( !arg ) return notify_fail("�A�n���_���򪫫~�S\n");

    if( arg=="all" ) {
        object *inv;
        
        inv = all_inventory(this_player());
        foreach(ob in inv) {
            if(!ob) continue;
            if( ob->query("keep_this") ) continue;
            sell_item(ob);
        }
        write("Ok�C\n");
        return 1;
    }

    if( !(ob = present(arg, this_player())) )
        return notify_fail("�A�n���_���򪫫~�S\n");

    return sell_item(ob);
}

int do_retrieve(string arg)
{
    object stamp, ob;
    int value;

    if( !arg || arg=="" || !(stamp = present(arg, this_player())) )
        return notify_fail("�A�nū�^���@�i���W���媫�S\n");

    if( !stamp->id("pawn stamp") )
        return notify_fail("�o���O���C\n");

    if( !(ob = stamp->query("pawned_item")) ) {
        write("�o�i���W���媫�]���A�Ӥ[�S����ū�M�w�g�Q��Q�汼�F�C\n");
        write("�A�H��N���������F�C\n");
        destruct(stamp);
        return 1;
    }

    if( !present(ob, storage) )
        return notify_fail("�o���O�o�a��Q�}�X�����C\n");

    value = (int)ob->query("value") * 120 / 100;
    if( (int)this_player()->can_afford(value) != 1 )
        return notify_fail("�A���W��(�s)�������C\n");

    message_vision("$N���X���M��F" + value_string(value) + "ū�^�F"
        + ob->name() + "�C\n", this_player());

    this_player()->pay_money(value);
    ob->move(this_player());
    ob->delete("pawned_time");
    destruct(stamp);

    return 1;
}

int do_list(string arg)
{
    int i;
    object *inv;
    string msg;

    if( !storage ) return notify_fail("��Q�̲{�b�S���f���C\n");
    if( wizardp(this_player()) )
        inv = all_inventory(storage);
    else
        inv = filter( all_inventory(storage), (: $1->query("pawned_time") :));
    if( !sizeof(inv) ) return notify_fail("��Q�̲{�b�S���i�ѥX�⪺�f���C\n");
    if( arg ) inv = filter( inv, (: $1->id($(arg)) :) );

/*
    msg = "��Q�̲{�b���H�U�f���X��R\n  ";
    msg += implode( map(inv, (: sprintf("%-50s%s", $1->short(),
        value_string((int)$1->query("value") * 2)) :)), "\n  ");
    msg += "\n";
    this_player()->start_more(msg);
    return 1;
*/

    msg = "��Q�̲{�b���H�U�f���X��R\n\n";
    for ( i = 0; i < sizeof(inv); i++)
        msg += sprintf("     %-5d  %-50s%s\n",
        i+1,
        inv[i]->short(),
        value_string(inv[i]->query("value") * 2));
    this_player()->start_more(msg);
    return 1;
}

int do_buy(string arg)
{
    int i, index;
    object *inv, ob;

    if( !arg ) return notify_fail("�A�n�R����F��S\n");

    if( !storage ) return notify_fail("��Q�̲{�b�S���f���C\n");
    inv = filter_array( all_inventory(storage), (: $1->query("pawned_time") :));
    if( !sizeof(inv) ) return notify_fail("��Q�̲{�b�S���f���C\n  ");

// This is a crasher! Dunno why .... Annihilator(11/01/95)
//    if( !parse_command(arg, inv, "%o", ob) )
//        return notify_fail("�A�n�R����F��S\n");

    if( sscanf(arg, "%s %d", arg, index) != 2 ) index = 1;
    index--;
    for(i=0; i<sizeof(inv); i++)
        if( inv[i]->id(arg) && !(index--)) break;

    if( i==sizeof(inv) )
        return notify_fail("�A�n�R����F��S\n");
    ob = inv[i];

    if( (int)this_player()->can_afford((int)ob->query("value") * 2) != 1 )
        return notify_fail("�A��(�s)�������C\n");
    message_vision("$N�ǥX���R�U�@" + ob->query("unit") + ob->name() + "�C\n",
        this_player() );
    this_player()->pay_money((int)ob->query("value") * 2);
    ob->delete("pawned_time");
//     fix if pay money....and player can't get....drop in environment
    if(!ob->move(this_player()))
        ob->move(environment(this_player()));
    else
        ob->move(this_player());

    return 1;
}

int do_store(string arg)
{
    if( !wizardp(this_player()) ) return 0;
    if( !storage ) return notify_fail("�ܮw���󤣦s�b�C\n");
    this_player()->move(storage);
    write("Ok.\n");
    return 1;
}
