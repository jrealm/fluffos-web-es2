// manto.c

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("���", ({"mooncake", "cake"}));
	if( !clonep() ) {
		set("unit", "��");
		set("base_unit", "��");
		set("base_value", 1);
		set("base_weight", 300);
		set("food_stuff", 140);
		set("long", "�@�ӤS��S�j�����A�N���ѤW����G�@�ˡC\n");
	}
	setup();
}

