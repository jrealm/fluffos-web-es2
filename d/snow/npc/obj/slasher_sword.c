/*  slasher_sword.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>
#include <weapon.h>

inherit F_UNIQUE;
inherit F_SWORD;

void create()
{
    set_name( HIW "¶���X�C" NOR, "slasher sword", "sword" );
    set_weight(2000);
    setup_sword(5, 7, 60, 10);

    if( !clonep() ) {
	set("replica_ob", STOCK_WEAPON("longsword"));
        set("wield_as", "sword");
        set("unit", "��");
        set("value", 26000);
        set("long",
            "�@��S�ӤS�����C�M���b��W�C�b�N���_�ݰʡM�ݨӭn�ϥγo��C�o�n\n"
            "�۷�ӱ�������~���|�~�˦ۤv�C\n");
        set("rigidity", 70);
        set("apply_weapon/sword", ([
            "dex":		2,
            "attack":		20,
            "intimidate":	20,
            "parry":		-10,
        ]) );
    }
    setup();
}
