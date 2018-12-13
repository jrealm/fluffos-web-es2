// leather_whip.c

#include <weapon.h>

inherit F_WHIP;

void create()
{
	set_name("���@", ({ "leather whip", "whip" }) );
	set_weight(2000);
	setup_whip(4, 5, 70, 0);

	if( !clonep() ) {
		set("wield_as", "whip");
		set("unit", "��");
		set("value",1800);
		set("long", "�@�����E�ئh�������@�A�i�H�Ψӷ�@�L�b�ϥΡC\n");
		set("rigidity", 15);
	}
	setup();
}
