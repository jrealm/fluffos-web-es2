// gold.c

inherit MONEY;

void create()
{
	set_name("����", ({"gold", "ingot", "gold_money"}));
	if( !clonep() ) {
		set("money_id", "gold");
		set("long", "����᪺���l�M�H���H�R�����l�M�ڡ����l�T\n");
		set("unit", "��");
		set("material", "gold");
		set("base_value", 10000 );
		set("base_unit", "��");
		set("base_weight", 37);
	}
	set_amount(1);
	setup();
}

