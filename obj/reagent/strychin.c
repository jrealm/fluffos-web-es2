// strychin.c

inherit REAGENT_ITEM;

void create()
{
	set_name("�f��ž", ({ "strychin" }));
	set_weight(30);
	if( !clonep() ) {
		set("unit", "��");
		set("long", "�@�اt�@�r���Ӫ��Ҵ��Ҫ��ħ��A���椣�D�C\n");
		set("unit_value", 35);
	}
	setup();
}
