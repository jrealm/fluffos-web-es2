// roast_chicken.c

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("���N��", ({ "roast chicken", "chicken" }) );
	if( !clonep() ) {
		set("unit", "��");
		set("base_unit", "��");
		set("base_value", 800);
		set("base_weight", 1500);
		set("food_stuff", 190);
		set("heal_kee", 30);
		set("long", "�@�����Q�Q�����N���M�z�M�A���f�����֬y�X�ӤF�C\n");
	}
	setup();
}

