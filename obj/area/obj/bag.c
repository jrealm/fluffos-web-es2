// bag.c

inherit ITEM;

void create()
{
	set_name("�¥��U", ({ "bag" }));
	set_weight(700);
	set_max_encumbrance(30000);
	if( !clonep() ) {
		set("unit", "��");
		set("value", 130);
		set("long", "�@���¥��f�U�A�ݨӥi�H�ˤ��֪F��C\n");
	}
	setup();
}

int accept_object() { return 1; }
