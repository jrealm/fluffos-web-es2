// medlar.c

inherit REAGENT_ITEM;

void create()
{
	set_name("�e��", ({ "medlar" }));
	set_weight(100);
	if( !clonep() ) {
		set("unit", "��");
		set("unit_value", 5);
		set("long", "�`�����ħ��A�h�Ω󴣷Ҫv�����e�����ġC\n");
	}
	setup();
}
