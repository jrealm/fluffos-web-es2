// invitation.c

inherit ITEM;

void create()
{
	set_name("�^����", ({ "invitation" }) );
	set_weight(20);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "�i");
		set("long",
			"�@�i�ѪZ�L���D�����ݼݩҵo���^�����M�u���@�y�����a�쪺�Z�L\n"
			"�H���~�ব��o�i�^�����C\n");
		set("value", 1);
	}
}
