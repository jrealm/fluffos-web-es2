// comb.c

inherit ITEM;

void create()
{
	set_name("����ޤl", ({ "annatto comb", "comb" }));
	set_weight(300);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 170);
		set("long", "�@���a�۷�ӽo������ޤl�C\n");
	}
	setup();
}
