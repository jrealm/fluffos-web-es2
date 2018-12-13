/*  get.c - get command

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

int do_get(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string from, item;
    object obj, *inv, env, obj2, obj3;
    int i, amount;

    if( me->query("life_form") == "ghost" )
        return notify_fail("�H���F�N�@�F�ʤF, �֥h�䫰���_���a!!\n");

    if( !arg ) return notify_fail("�A�n�߰_����F��S\n");
    if( me->is_busy() )
        return notify_fail("�A�W�@�Ӱʧ@�٨S�������T\n");

    if( !me->query_stat_maximum("HP") )
        return notify_fail("�A�S������M�L�k�B�����~�C\n");

    // Check if a container is specified.
    if( sscanf(arg, "%s from %s", arg, from)==2 ) {
	env = present(from, me);
	if(!env) env = present(from, environment(me));
	if(!env) return notify_fail("�A�䤣�� " + from + " �o�˪F��C\n");
	if( (living(env) || userp(env))
	&& (wiz_level(me) <= wiz_level(env)))
	    return notify_fail("�A���Ův���ť������谪�M�~��j���C\n");
    } else env = environment(me);

    // Check if a certain amount is specified.
    if(sscanf(arg, "%d %s", amount, item)==2) {
        if( !objectp(obj = present(item, env)) )
            return notify_fail("�o�̨S���o�˪F��C\n");
        if( !obj->query_amount() )
            return notify_fail( obj->name() + "����Q���}�����C\n");
        if( amount < 1 )
            return notify_fail("�F�誺�ӼƦܤ֬O�@�ӡC\n");

        if( amount > obj->query_amount() )
            return notify_fail("�o�̨S������h��" + obj->name() + "�C\n");
        else if( amount == (int)obj->query_amount() ) {
            return do_get(me, obj);

        } else {
            int old_amount;
            old_amount = obj->query_amount();
            
            obj2 = new(base_name(obj));
            obj2->move(env);    // for container
            obj2->set_amount( amount );            
            obj->set_amount( old_amount - amount );
            // Counting precise amount costs more time.
            if( me->is_fighting() ) me->start_busy(3);
            return do_get(me, obj2);
        }
    }

    // Check if we are makeing a quick get.
    if(arg=="all") {
	object ob;
	if( me->is_fighting() )
	    return notify_fail("�A�٦b�԰����T�u��@�����@�ˡC\n");

	if( !function_exists("receive_object", env) )
	    return notify_fail("�����O�e���C\n");

	inv = all_inventory(env);
	if( !sizeof(inv) )
	    return notify_fail("���̭��S������F��C\n");

	foreach(ob in inv) do_get(me, ob);

	return 1;
    }

    if( !objectp(obj = present(arg, env)) || living(obj) )
        return notify_fail("�A����S���o�˪F��C\n");

    return do_get(me, obj);
}
    
int do_get(object me, object obj)
{
    object from_ob, *enemy, *guard;
    int equipped;
    mixed msg;

    if( !obj ) return 0;
    from_ob = environment(obj);

    if( obj->is_character() ) 
	return notify_fail("����!\n");
/*
    {
        if( living(obj) ) return 0;
        // Don't allow player to move unconcious NPC
        if( !userp(obj) && !obj->is_corpse() )
            return notify_fail("�A�u��I�t��L���a������C\n");
    }
*/
    notify_fail("�o�˪F�讳���X�ӡC\n");
    if( from_ob->hold_object(obj) ) return 0;

    if( guard = obj->query_temp("guarded") ) {
	guard = filter_array(guard, (:
	    objectp($1)
	    && present($1, environment($2))
	    && living($1)
	    && ($1!=$2)
	    :), me);
	if( sizeof(guard) )
	    return notify_fail( guard[0]->name() 
		+ "���u�b" + obj->name() + "�@�ǡM�������H�����C\n");
    }

    if( (msg = obj->query("no_get")) )
	return notify_fail(stringp(msg) ? msg : "�o�ӪF�讳���_�ӡC\n");

    if( me->over_encumbranced() ) return notify_fail("�A�w�g�t���L���F�T\n");

    if( obj->query("equipped") ) equipped = 1;

    if( ! obj->move(me) ) return 0;
    if( me->is_fighting() ) me->start_busy(1);
    if( obj->is_character() )
	message_vision( "$N�N$n�ߤF�_�Ӵ��b�I�W�C\n", me, obj );
    else
	message_vision( sprintf("$N%s�@%s$n�C\n", 
	    from_ob==environment(me)? "�߰_":
		(from_ob->is_character() ?
		"�q" + from_ob->name() + "���W" + (equipped? "���U" : "�j�X"):
		"�q" + from_ob->name() + "�����X"),
		obj->query("unit")), me, obj );
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : get <���~�W��> [from <�e���W>]
 
�o�ӫ��O�i�H���A�߰_�a�W�ήe�������Y�˪��~�C
 
HELP
    );
    return 1;
}
 
