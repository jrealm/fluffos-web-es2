// pawn_stamp.c

inherit ITEM;

void create()
{
	set_name("��", ({ "pawn stamp", "stamp" }));
	set_weight(5);
	if( !clonep() ) {
		set("unit", "�i");
		set("long", "�@�i�ťշ��C\n");
	}
	setup();
}
