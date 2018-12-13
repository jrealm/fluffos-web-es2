/*  greatsword.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("�j�C", "great sword", "sword" );
    set_weight(24000);
    setup_sword(3, 13, 100, 5);

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "��");
        set("value", 11000);
        set("rigidity", 25);
        set("long",
            "�@������ت������C�M���o�򥨤j�����C�h�b�O�I�b�I��A�u��ѻM�O\n"
            "�L�H�����~�ϥΡC\n");
        set("wield_msg", "$N�N�I�᪺�C�n�@��A�u�I�v�a�@�n��X�@��j�C�C\n");
    }
    setup();
}

void varify_template(object owner)
{
    int i = owner->query_level();
    
    ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "�C");
}
