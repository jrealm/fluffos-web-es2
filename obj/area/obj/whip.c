//t_whip.c
#include <weapon.h>
inherit F_WHIP;

void create()
{
	set_name("���@", ({ "horse whip","whip" }));
	set_weight(8000);
        setup_whip(3, 5, 40, 3);
	if( !clonep() ) {
		set("wield_as", ({ "whip" }));
		set("unit", "��");
		set("value", 2000);
		set("long",
"�@���M�������@, �S�¤S��, �s�W�g���d�g���t, �@�W�������D�����D.\n"
		);
        }
	setup();
}
