// crate.c

inherit ITEM;

void create()
{
	set_name("�j��c", ({ "big crate", "crate"}));
	set_weight(40000);
	if( !clonep() ) {
		set("unit", "��");
		set("long", "�o�O�@�ӥΨӸ˳f�����j��c�M�ݰ_�Ӭ۷�H���C\n");
		set("value", 1);
		set("wage", 25);
	}
	setup();
}

void init()
{
	add_action("do_get", "get");
}

int do_get(string arg)
{
	if( environment() != environment(this_player())
	||	!id(arg) ) return 0;

	if( (int)this_player()->query_stat("kee") < 10 ) {
		write("�A���O�𤣰��F�M�𮧤@�U�A���a�C\n");
		return 1;
	}

	if( move(this_player()) ) {
		message_vision("$N�s�U�y�N�a�W��" + name() + "���F�_�ӡC\n", this_player());
		return 1;
	}
}

