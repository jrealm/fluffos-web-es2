/*  quit.c

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
#include <action.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

void create() 
{
    seteuid(getuid());
    set("channel_id", "���u���O");
}

int main(object me, string arg)
{
    int i;
    object link_ob, ob;

    if( me->is_busy() ) {
// ���\��i�Ϫ��a�ΨӮ��hstart_busy���@��, cancel interrupt by dragoon
//        me->interrupt(me, INTR_QUIT);
        write("�A�����۩O, �иյ۰��U�Ҧ����ơC\n");
        return 1;
    }

    if( me->query("life_form") == "ghost" && arg != "!" )
	return notify_fail("�A�{�b���}�N�|�L�k�_���M�p�G�T�w�n���}\n"
		"�Х� 'quit !'�C\n");

    if( me->query_team() )
	me->dismiss_team();
        
    if( !wizardp(me) ) {
	foreach(ob in all_inventory(me)) {
	    if( ob->query_autoload() ) continue;	/* �۰��x�s�����󤣥�� */
	    if( !ob->query("value") ) continue;		/* �S�����Ȫ����󤣥�� */
	    DROP_CMD->do_drop(me, ob);
	}
    }

    link_ob = me->link();

    // We might be called on a link_dead player, so check this.
    if( link_ob ) {

        // Are we possessing in others body ?
        if( link_ob->is_character() ) {
            write("�A����z�^��" + link_ob->name(1) + "�����W�C\n");
            exec(link_ob, me);
            link_ob->setup();
            return 1;
        }

        link_ob->set("last_on", time());
        link_ob->set("last_from", query_ip_name(me));
#ifdef SAVE_USER
        link_ob->save();
#endif
        destruct(link_ob);
    }

    // if pking, set a pker mark before quit -dragoon
    if( time() - (int)me->query("last_pk_time") < 60 * 60 )
	me->set("pker", 1);

    write("�w��U���A�ӡT\n");
    message("system", me->name() + "(" + me->query("id") + ") ���}�C���C\n",
	environment(me), me);

    CHANNEL_D->do_channel(this_object(), "sys",    me->name() + "("+ me->query("id") +") ���}�C���F�C");

#ifdef SAVE_USER
    me->save();
#endif
    // log in USAGE include login and logout 
    log_file( "USAGE", sprintf("[%s] %12s quit\n",
        ctime(time()), (string)me->query("id")));

    // if ghost quit, log it -Dragoon
    if( me->query("life_form") == "ghost" )
	log_file( "GHOST_QUIT", sprintf("[%s] %s quit in ghost form\n",
	    ctime(time()), (string)me->query("id")));

    destruct(me);

    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : quit

��A(�p)�Q�Ȯ����}��, �i�Q�Φ��@���O�C
HELP
    );
    return 1;
}
