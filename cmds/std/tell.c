/*  tell.c - the tell command

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
//#include <net/dns.h>

#define MIN_TELL_INTERVAL	3
#define MAX_TELL_MESSAGE	1024

inherit F_CLEAN_UP;

int help(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string target, msg, mud, uid, *ignore;
    object obj;
    int idle_time, tmp;

    if( time() - (int)me->query_temp("last_tell_time") < MIN_TELL_INTERVAL )
	return notify_fail("�A�����𮧤@�U�~��A�רϥγo�ӫ��O�C\n");
    me->set_temp("last_tell_time", time());

    if( !arg || sscanf(arg, "%s %s", target, msg)!=2 ) return help(me);
    if( strlen(msg) > MAX_TELL_MESSAGE )
	return notify_fail("�A���T���Ӫ��F�A�Ъ��ܵu���C\n");

    if( sscanf(target, "%s@%s", target, mud)==2 ) {
	//GTELL->send_gtell(mud, target, me, msg);
	write("�����T���w�e�X�A�i��n�y�Ԥ~��o��^���C\n");
	return 1;
    }

    obj = find_player(target);
    if( !obj
    || (!obj->visible(me) && wizardp(obj)) )
	return notify_fail("�S���o�ӤH....�C\n");

    // add by dragoon
    if( obj->query_temp("ignore/all") && !wizardp(me) ) {
        tell_object(me, "�o�ӤH�{�b����������H���͸ܡC\n");
        return 1;
    }

    if(!interactive(obj))
	return notify_fail("�o�ӤH�{�b�S��kť��A���T���C\n");

    // check for ignore
    uid = getuid(me);
    ignore = obj->query("ignore");
    if( arrayp(ignore) && member_array(uid, ignore) != -1 )
         return notify_fail("��褣�Qť�A���ܡC\n");

    // add by dragoon to let tell work in sneak
    if( me->query_temp("pending/hidden") ) {
          tmp = me->query_temp("pending/hidden");
          me->delete_temp("pending/hidden");
    }

    write("�A�i�D" + obj->name(1) + "�G" + HIG + msg + "\n" NOR);

    if( (idle_time = query_idle(obj)/60) > 2
    || in_input(obj)
    || in_edit(obj) ) {
	write(GRN+obj->name(1)+
	(idle_time>2 ? "�w�g�o�b "+idle_time+" �����F" : "")+
	(in_input(obj) ? " <��J��r��> " : "")+
	(in_edit(obj) ? " <�s���ɮפ�> " : "")+
	"�A�i�ण�|���W�^���A��...\n"+NOR);
    }
    tell_object(obj, sprintf("%s�i�D�A�R" + HIG + "%s\n" NOR,
	me->name(1)+"("+me->query("id")+")", msg));

    // reset hidden if it exist before use tell, -Dragoon
    if( tmp > 0 ) {
	me->set_temp("pending/hidden", tmp); }

    obj->set_temp("reply", me->query("id"));
    return 1;
}

int remote_tell(string cname, string from, string mud, string to, string msg)
{
    object ob;

    if( ob = find_player(to) ) {
	if( cname )
	    tell_object(ob, sprintf(HIG "%s(%s@%s)�i�D�A�R%s\n" NOR,
		cname, capitalize(from), mud, msg ));
	else
	    tell_object(ob, sprintf(HIG "%s@%s �i�D�A�R%s\n" NOR,
		capitalize(from), mud, msg ));
	ob->set_temp("reply", from + "@" + mud);
	return 1;
    } else
	return 0;
}

int help(object me)
{
    write(@HELP
���O�榡�Gtell <�Y�H> <�T��>

�A�i�H�γo�ӫ��O�M�u�W��L���ϥΪ̻��ܡC�p�G��西�b�o�b�A�γB���J��
�r�B�s���ɮ׵����A�A�i�ण�|�ߨ�ݨ�A���T���A�t�η|���ܧA�o�ت��p�C

���F����Y�ǤH�Q�γo�ӫ��O�c�N���Z�L�H�A�ҥH�t�Φb�Y�Ǳ��p�U�|��o�ӫ�
�O���@�ǭ���C�p�G���H�� tell ���O���_�a�e�T�����A�A��A�y���x�Z(�U��
�~�ȹ�)�A�A�i�H�� ignore ���O�өڵ��Ҧ��Ӧ۳o��ϥΪ̪� tell �T���C

��L�������O�Greply, ignore
HELP
    );
    return 1;
}
