/*  food.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <dbase.h>
#include <name.h>

int stuff_ob(object me)
{
    int stuff, heal;

    stuff = query("food_stuff");
    if( !stuff ) return 0;

    if( stuff + me->query_stat("food") > me->query_stat_maximum("food") )
        return notify_fail("�A���{�l�w�g�ˤ��U�o" + query("unit") + name() + "�F�C\n");

    me->supplement_stat("food", stuff);
    message_vision("$N�Y�U�@" + query( this_object()->query_amount() ? "base_unit" : "unit") + name() + "�C\n", me);

    if( heal = query("heal_gin") 
    &&    me->supplement_stat("gin", heal) )
        write("�A�Y�F��i�������M��_�F�@����O�C\n");

    if( heal = query("heal_kee") 
    &&    me->supplement_stat("kee", heal) )
        write("�A�Y�F��i�������Mı�o��O��_�F�@�ǡC\n");

    if( heal = query("heal_sen") 
    &&    me->supplement_stat("sen", heal) )
        write( "�Aı�o�M���h�F�C\n");

    if( this_object()->query_amount() )
        this_object()->add_amount(-1);
    else
        destruct(this_object());
    return 1;
}
