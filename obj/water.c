// water.c

inherit LIQUID_ITEM;
inherit F_DRINK;

void create()
{
	set_name("�M��", ({ "water" }));
	if( !clonep() ) {
		set("long", "... ���N�O���M�Sԣ�n�ݪ��C\n");
		set("density", 1);
	}
	setup();
	set_volume(1000);
}
