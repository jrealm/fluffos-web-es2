// crane_dye.c

inherit REAGENT_ITEM;

void create()
{
	set_name("�b����", ({ "crane dye", "dye" }));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "��");
		set("long", "�@�اt�@�r���ħ��A���O���Ǥ֨����Ĥ�ݭn�o���ħ��C\n");
		set("unit_value", 15);
	}
	setup();
}
