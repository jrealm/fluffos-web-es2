/*  look.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

//#pragma optimize
#pragma save_binary

#include <room.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);

void create() {seteuid(getuid());}

int main(object me, string arg)
{
    object obj;
    int result;

    if( me->query_temp("block_msg/vision") )
        return notify_fail("�A�{�b����]�ݤ���T\n");

    if( arg ) {
        if( (obj = present(arg, me))
        ||    (obj = present(arg, environment(me)))) 
            if( obj->is_character() ) result = look_living(me, obj);
            else result = look_item(me, obj);
    }

    if( !result && environment(me) )
        return environment(me)->do_look(me, arg);
    return result;
}

int look_item(object me, object obj)
{
    mixed *inv;

    me->start_more(obj->long());
    inv = all_inventory(obj);
    if( sizeof(inv) ) {
	// if too many items, show a simple message -dragoon
	if( sizeof(inv) < 30 ) {
            inv = map_array(inv, "inventory_look", this_object() );
            message("vision", sprintf("�̭����R\n  %s\n",
                implode(inv, "\n  ") ), me); }
	else tell_object(me, YEL"�̭����C���K����۳\�h�F��..\n"NOR);
    }
    return 1;
}

int look_living(object me, object obj)
{
    string str, pro, race;
    mixed *inv;
    int age;

    if( me!=obj )
        message("vision", me->name() + "���n�ۧA�ݡM�����D���Ǥ���D�N�C\n", obj);

    str = obj->long();

    pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

    race = obj->query_race();
    if( (string)obj->query("humanoid") && intp(age = obj->query("age")) ) {
        if( race=="human" )
            str += break_chinese_string(
                sprintf("%s%s�A%s�ݰ_��%s�C",
                    obj->name(), RACE_D(race)->query_appearance(obj),
                    pro, (age > 10) ? ("��" + chinese_number(age / 10 * 10) + "�h��") : "����Q��"),
                70 ) + "\n";
        else
            str += break_chinese_string(
                sprintf("%s�ݩ�%s�ڡA%s%s�A%s�ݰ_��%s�C",
                    obj->name(), to_chinese(race),
                    pro, RACE_D(race)->query_appearance(obj),
                    pro, (age > 10) ? ("��" + chinese_number(age / 10 * 10) + "�h��") : "����Q��"),
                70 ) + "\n";
    }

    inv = all_inventory(obj);
    if( sizeof(inv) ) {
        inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
        inv -= ({ 0 });
        if( sizeof(inv) )
            str += sprintf( obj->is_corpse() ? "%s���򪫦��R\n%s\n" : "%s���W�a�ۡR\n%s\n",
                pro, implode(inv, "\n") );
    }

    message("vision", str, me);

    return 1;
}

string inventory_look(object obj, int flag)
{
    string str;

    str = obj->short();
    if( obj->query("equipped") )
        str = HIY "  ��" + str + NOR;
    else if( !flag )
        str = "    " + str;
    else
        return 0;

    return str;
}

int help (object me)
{
    write(@HELP
���O�榡: look [<���~>|<�ͪ�>|<��V>]
 
�o�ӫ��O���A�d�ݧA�Ҧb�����ҡB�Y�󪫫~�B�ͪ��B�άO��V�C
 
HELP
);
    return 1;
}
