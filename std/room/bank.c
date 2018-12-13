// bank.c

inherit ROOM;

void init()
{
    add_action("do_convert", "convert");
    add_action("do_deposit", "deposit");
    add_action("do_withdraw", "withdraw");
    add_action("do_new_account", "open");
}

int do_new_account(string arg)
{
    int bal;
    object bankbond;

    if( !arg || arg!="account" ) return 0;
    if( present("bankbond", this_player()) )
        return notify_fail("�A�w�g���@�Ӥ��Y�F�C\n");
    seteuid(geteuid(this_player()));
    bankbond = new("/obj/bankbond");
    if( !bankbond->move(this_player()) ) {
        write("�A���W���F��Ӧh�F�M�a���ʿ��������C\n");
        destruct(bankbond);
        return 1;
    }
    bankbond->set("owner_id", geteuid(this_player()));
    bal = this_player()->query("bank_account");
    if( bal>0 ) {
        write("�����d��bï�M�����@�����O�Ҫ��M���s�o���A�@�i�s�������C\n");
        bankbond->set_balance(bal*9/10);
    } else if( bal==0 ) {
        write("�A�M�����@�P�e�F�Ӫ��M�@���H��������Ӫ��̾ڡC\n");
        write("�������A�@�i�����M�W���O�ۧA�{�b���Y�پl�U�h�ֿ��C\n");
        bankbond->set_balance(0);
    } else {
        write("�A���bï�X�F�I���D, �Ч�Ův�����C\n");
        destruct(bankbond);
    }
    return 1;
}

int do_convert(string arg)
{
    string from, to;
    int amount, bv1, bv2;
    object from_ob, to_ob;

    if( !arg || sscanf(arg, "%d %s to %s", amount, from, to)!=3 )
        return notify_fail("���O�榡�Rconvert <�ƶq> <�f������> to <�f������>\n");

    seteuid(getuid());
    from_ob = present(from + "_money", this_player());
    to_ob = present(to + "_money", this_player());
    if( !to_ob && file_size("/obj/money/" + to + ".c") < 0 )
        return notify_fail("�A�Q�I�����@�ؿ��S\n");

    if( !from_ob )        return notify_fail("�A���W�S���o�سf���C\n");
    if( amount < 1 )    return notify_fail("�I���f���@���ܤ֭n�I���@�ӡC\n");
        
    if( (int)from_ob->query_amount() < amount )
        return notify_fail("�A���W�S������h" + from_ob->name() + "�C\n");

    bv1 = from_ob->query("base_value");
    if( !bv1 ) return notify_fail("�o�تF�褣�ȿ��C\n");

    bv2 = to_ob ? to_ob->query("base_value") : call_other("/obj/money/" + to, "query", "base_value" );
    if( !bv2 ) return notify_fail("�A�n�I�����@�سf���S\n");

    if( bv1 < bv2 ) amount -= amount % (bv2 / bv1);
    if( amount==0 )    return notify_fail("�o��" + from_ob->name() + "�����ȤӧC�F�M�����_�C\n");

    if( !to_ob ) {
        to_ob = new("/obj/money/" + to);
        to_ob->move(this_player());
        to_ob->set_amount(amount * bv1 / bv2);
    } else
        to_ob->add_amount(amount * bv1 / bv2);

    message_vision( sprintf("$N�q���W���X%s%s%s�M����%s%s%s�C\n",
        chinese_number(amount), from_ob->query("base_unit"), from_ob->name(),
        chinese_number(amount * bv1 / bv2), to_ob->query("base_unit"), to_ob->name()),
        this_player() );

    from_ob->add_amount(-amount);

    return 1;
}

int do_deposit(string arg)
{
    int amount;
    string money;
    object money_ob, bond;

    seteuid(getuid());
    if( !bond = present("bankbond", this_player()) )
        return notify_fail("�ЧA���}�@�Ӥ��Y�C\n");

    if( geteuid(this_player()) != bond->query("owner_id") ) {
        write("�����o�{�A����㤣��M�S���F�A�������C\n");
        destruct(bond);
        return 1;
    }

    if( bond->query_balance() != this_player()->query("bank_account") ) {
        write("�����o�{�����W���b�ؤ���M�S���F�A�������C\n");
        destruct(bond);
        return 1;
    }

    if( !arg || sscanf(arg, "%d %s", amount, money)!=2 )
        return notify_fail("���O�榡�Rdeposit <�ƶq> <�f������>�C\n");

    if( amount < 0 )
        return notify_fail("�A����s�J�s�H�U�������C\n");
        
    if( !money_ob = present(money + "_money", this_player()) )
        return notify_fail("�A���W�S���o�ؿ����C\n");

    if( money_ob->query_amount() < amount )
        return notify_fail("�A���W�S���o��h��" + money_ob->name() + "�C\n");

    bond->transact(amount * money_ob->query("base_value"));
    money_ob->add_amount( - amount );
    write("�A�N" + chinese_number(amount) + money_ob->query("base_unit")
        + money_ob->name() + "��ε������M�������s�o���A�@�i�s�������C\n");
    this_player()->save_autoload();
        this_player()->save();
    return 1;
}

int do_withdraw(string arg)
{
    int amount;
    string money;
    object money_ob, bond;

    seteuid(getuid());
    if( !bond = present("bankbond", this_player()) )
        return notify_fail("�ЧA���}�@�Ӥ��Y�C\n");

    if( geteuid(this_player()) != bond->query("owner_id") ) {
        write("�����o�{�A����㤣��M�S���F�A�������C\n");
        destruct(bond);
        return 1;
    }

    if( bond->query_balance() != this_player()->query("bank_account") ) {
        write("�����o�{�����W���b�ؤ���M�S���F�A�������C\n");
        destruct(bond);
        return 1;
    }

    if( !arg || sscanf(arg, "%d %s", amount, money)!=2 )
        return notify_fail("���O�榡�Rwithdraw <�ƶq> <�f������>�C\n");

    if( amount < 0 )
        return notify_fail("�A���ണ��s�H�U���f���C\n");

    if( amount > 30000) 
        return notify_fail("�A����@����Ӧh�C\n");    

    if( file_size("obj/money/" + money + ".c") < 0 )
	return notify_fail("�A�n������@�ؿ��S\n");

    if( catch(money_ob = new("/obj/money/" + money)) ) return 0;

    money_ob->set_amount(amount);
    if( bond->query_balance() < money_ob->value() ) {
        destruct(money_ob);
        return notify_fail("�A�����Y�̨S���o��h���C\n");
    }

    bond->transact(- money_ob->value());
    if( !money_ob->move(this_player()) ) {
        bond->transact(money_ob->value());
        destruct(money_ob);
        return notify_fail("�A���W�a���F�o�\\�h���M���֤@�I�a�C\n");
    }

    write("�����N" + chinese_number(amount) + money_ob->query("base_unit")
        + money_ob->name() + "��ε��A�M�í��s�o���A�@�i�s�������C\n");
        this_player()->save_autoload();
        this_player()->save();
    return 1;
}
