// coin.c

inherit ITEM;

void create()
{
	set_name("�j��", ({ "ancient coin", "coin" }));
	set_weight(3);
	if( !clonep() ) {
		set("unit", "�T");
		set("value", 60);
		set("long", "�@�T���K�K���j���A�ݤ��X������S�O�C\n");
		set("thief_token", 1);
	}
	setup();
}
