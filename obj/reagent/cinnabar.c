// cinnabar.c

inherit REAGENT_ITEM;

void create()
{
	set_name("����", ({ "cinnabar" }));
	set_weight(500);
	if( !clonep() ) {
		set("unit", "�]");
		set("long", "�@�ج��⪺�q��A�[���i�H�o��E�A�O�Ҥ������n���ơC\n");
		set("unit_value", 0.6);
	}
	setup();
}
