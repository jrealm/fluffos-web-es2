// coin.c

inherit MONEY;

void create()
{
	set_name("��", ({"coin", "coins", "coin_money" }));
	if( !clonep() ) {
		set("money_id", "coin");
		set("long", "�o�O�y�q�����̤p���f���M���n�@�ʤ���~�ȱo�@��Ȥl�C\n");
		set("unit", "��");
		set("material", "copper");
		set("base_value", 1);
		set("base_unit", "��");
		set("base_weight", 3);
	}
	set_amount(1);
	setup();
}

