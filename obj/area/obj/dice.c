// dice.c

inherit ITEM;

void create()
{
	set_name("��l", ({ "dice"}));
	set_weight(3);
	if( !clonep() ) {
		set("unit", "��");
		set("value", 5);
		set("long",
			"�@�ɻ�l�A�A�i�H�� roll �Y��l���C\n");
	}
	setup();
}

void init()
{
	add_action("do_roll", ({ "roll", "throw" }));
}

int do_roll(string arg)
{
	if( !id(arg) ) return 0;

	message_vision("$N���X��l�@�Y�A��l�u�F�u���U�ӡA���G�O��"
		+ (random(6)+1) + "�I�C\n", this_player());
	return 1;
}
