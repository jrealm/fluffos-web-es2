// ricedough.c

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("���{", ({ "rice dough", "dough", "rice" }));
	if( !clonep() ) {
		set("unit", "��");
		set("base_unit", "��");
		set("base_value", 25);
		set("base_weight", 80);
		set("food_stuff", 60);
		set("long",
			"�̶��@�����{�l�A�̭��]�ۤ@�Ǧ��P�B�γJ�B�o���q�઺�p��C\n");
	}
	setup();
}

