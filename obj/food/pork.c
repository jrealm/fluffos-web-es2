// pork.c

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("�դ���", ({ "pork" }) );
	if( !clonep() ) {
		set("unit", "��");
		set("base_unit", "��");
		set("base_value", 200);
		set("base_weight", 400);
		set("heal_kee", 10);
		set("food_stuff", 90);
		set("long", "���q�����N�դ��� ... �C\n");
	}
	setup();
}

