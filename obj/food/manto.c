// manto.c

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("�C�Y", ({ "manto" }));
	if( !clonep() ) {
		set("unit", "��");
		set("base_unit", "��");
		set("base_value", 10);
		set("base_weight", 100);
		set("food_stuff", 80);
		set("long", "�C�Y ... ��A�Q�������@�Ҥ@�ˡM�P�ʧa�C\n");
	}
	setup();
}

