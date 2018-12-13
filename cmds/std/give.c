/*  give.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <command.h>
#include <login.h>

inherit F_CLEAN_UP;

int do_give(object me, object item, object who);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string target, item;
    object obj, who, *inv, obj2, fwho;
    int i, amount;

    if(!arg) return notify_fail("�A�n���֤���F��S\n");

    if( !(sscanf(arg, "%s to %s", item, target)==2
        || sscanf(arg, "%s %s", target, item)==2) )
        return notify_fail("�A�n���֤���F��S\n");

    if( !objectp(who = present(target, environment(me)))
    ||  !living(who))
        return notify_fail("�o�̨S�� \"" + target + "\" �o�ӤH�C\n");

    if(who==me) return notify_fail("�A���ۤv�F��F�¡S\n");

    // add by dragoon
    if( objectp(who) && who->query("no_fight") )
        return notify_fail("����??\n");

    if(sscanf(item, "%d %s", amount, item)==2)
    {
        if( !objectp(obj = present(item, me)) )    
            return notify_fail("�A���W�S���o�˪F��C\n");
        // �W�[����⪱�a���H���ˬd -Dragoon
        if( obj->query("no_drop") || userp(obj) )
            return notify_fail("�o�˪F�褣���H�K���H�C\n");
        if( !obj->query_amount() )    
            return notify_fail( obj->name() + "����Q���}���H�C\n");
        if( amount < 1 )
            return notify_fail("�F�誺�ƶq�ܤ֬O�@�ӡC\n");
        if( amount > obj->query_amount() ) 
            return notify_fail("�A�S������h��" + obj->name() + "�C\n");
        else if( amount == (int)obj->query_amount() )
            return do_give(me, obj, who);
        else {
            seteuid(MUDLIB_UID);
            obj2 = new(base_name(obj));
            seteuid(getuid());
            obj2->set_amount(amount);
            if( do_give(me, obj2, who) ) {
                obj->add_amount(-amount);
                return 1;
            } else {
                destruct(obj2);
                return 0;
            }
        }
    }

    if( arg=="all" ) {
        foreach(object ob in all_inventory(me))
            do_give(me, ob, who);
        write("Ok.\n");
        return 1;
    }

    if(!objectp(obj = present(item, me)))
        return notify_fail("�A���W�S���o�˪F��C\n");

    return do_give(me, obj, who);
}

private int
do_give(object me, object item, object who)
{
    if( item->query("no_drop") )
        return notify_fail("�o�˪F�褣���H�K���H�C\n");

    if( who->over_encumbranced() )
        return notify_fail( who->name() + "�w�g�t���L���M�A�]�h���ʥ���F��F�C\n");

    notify_fail("�ݰ_��" + who->name() + "�ä��@�N���U�o" + item->query("unit")
        + item->name() + "�C\n");

    if( !userp(who) ) {
        if( !who->accept_object(me, item) ) return 0;
        if( item->value() ) {
            /* �� NPC �����ɭԡA�����N���P�� */
            message_vision("$N���X" + item->short() + "�浹$n�C\n", me, who);
            destruct(item);
            return 1;
        }
    }

    if( !item->move(who) ) return 0;

    if( wizardp(me) && (userp(who) && !wizardp(who)) )
        log_file( "static/GIVE", sprintf("[%s] %s gived %s to %s\n",
                ctime(time()), geteuid(me), item->name(), geteuid(who)) );
    message_vision("$N�浹$n�@" + item->query("unit") + item->name()
        + "�C\n", me, who );

    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : give <���~�W��> to <�Y�H>
           give <�Y�H> <���~�W��>

�o�ӫ��O�i�H���A�N�Y�˪��~���O�H�C
 
HELP
    );
    return 1;
}
