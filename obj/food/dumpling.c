// dumpling.c

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("���ץ]�l", ({ "beef dumpling", "dumpling" }) );
	if( !clonep() ) {
		set("unit", "��");
		set("base_unit", "��");
		set("base_value", 10);
		set("base_weight", 60);
		set("food_stuff", 80);
		set("long", "�@�ӭ��Q�Q�����ץ]�l�C\n");
	}
	setup();
}

