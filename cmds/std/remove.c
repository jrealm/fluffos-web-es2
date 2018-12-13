/*  remove.c

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

inherit F_CLEAN_UP;

int do_remove(object me, object ob);

int main(object me, string arg)
{
    object ob, *inv;
    int i;

    if( me->is_busy() ) return notify_fail("�A�{�b�S���šT\n");

    if( !arg ) return notify_fail("�A�n�汼����S\n");

    if(arg=="all") {
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
            do_remove(me, inv[i]);
        write("Ok.\n");
        return 1;
    }

    if( !objectp(ob = present(arg, me)) )
        return notify_fail("�A���W�S���o�˪F��C\n");
    return do_remove(me, ob);
}

int do_remove(object me, object ob)
{
    string str, equipped;

    if( !stringp(equipped = (string)ob->query("equipped"))
    ||    !sscanf(equipped, "armor/%*s") )
        return notify_fail("�A�èS���ϥγo�˪F�谵�@��C\n");

    if( ob->unequip() ) {
        if( !stringp(str = ob->query("unequip_msg")) )
            switch(ob->query("armor_type")) {
                case "cloth":
                case "armor":
                case "surcoat":
                case "boots":
                    str = YEL "$N�N$n��F�U�ӡC\n" NOR;
                    break;
                case "bandage":
                    str = YEL "$N�N$n�q�ˤf�B��F�U�ӡC\n" NOR;
                    break;
                default:
                    str = YEL "$N����$n���˳ơC\n" NOR;
            }
        message_vision(str, me, ob);
        return 1;
    } else
        return 0;
}

int help(object me)
{
  write(@HELP
���O�榡 : remove all | <���~�W��>
 
�o�ӫ��O���A�汼���W�Y�󨾨�.
 
HELP
    );
    return 1;
}
 
