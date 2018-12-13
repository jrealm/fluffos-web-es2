// bankbond.c

inherit ITEM;

int balance = 0;

void create()
{
	set_name("��������", ({ "bankbond" }));
	set_weight(1);
	if( !clonep() ) {
		set("unit", "�i");
		set("long",
			"�o�O�@�i�����ΨӰO����Ȥ�������Ӫ������M�W�������誺����\n"
			"���l�C\n");
        set("no_sell", 1);
	        set("value", 1);
	}
	set("keep_this", 1);
	setup();
}

string query_autoload() { return balance + ""; }

void autoload(string param)
{
	if( sscanf(param, "%d", balance) )
		set("owner_id", geteuid(previous_object()));
}

void transact(int amount)
{
	if( environment()->query("bank_account") != balance ) return;

	balance = environment()->query("bank_account") + amount;
	environment()->set("bank_account", balance);
}

void set_balance(int b) { balance = b; environment()->set("bank_account", b); }
int query_balance() { return balance; }

string long(int raw)
{
	string str;
	int amount;

	str = ::long(raw);
	if( balance > 0 ) {
		str += "�A�{�`�@���l�R";
		amount = balance;
	} else if( balance < 0 ) {
		str += "�A�{�b�ٻ�������R";
		amount = - balance;
	}
	if( balance != 0 ) {
		if( amount >= 100 ) {
			str += chinese_number(amount/100) + "��";
			if( amount%100 ) str += "�S";
		}
		if( amount%100!=0 )
			str += chinese_number(amount%100) + "����C";
		str += "\n";
	}

	return str;	
}
