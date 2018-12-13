/*  ccmd.c - the cmd to use clan functions
        
    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <login.h>
#include <ansi.h>
inherit F_CLEAN_UP;

varargs int clan_line(string msg,int emote);

int main(object me, string arg)
{
    object who, obj;
    string target;

    // function 1: check all clans
    if( !arg ) {
	seteuid( getuid() );
	write("�ثe�w���������p�U: \n\n");
        write( read_file("/obj/CLAN") );
	write("\n���[�J�@�������Ч���ѯťH�W���a�ӽХ[�J�����C\n");
	return 1;
    }

    seteuid( getuid() );

    // function 2: verify - get clan symbol for a clan member
    if( arg == "verify" ) {	
	if( !me->query("clan/clan_name") ) 
	    return notify_fail("�A�ëD���������C\n");
	if( !present("clan symbol", me) ) {
	    obj = new("/obj/clan_symbol");
	    tell_object(me, "�A�o��@�ӷs�������H���C\n");
	    obj->move(me);
	    return 1; }
	else return notify_fail("�A�w�g���@�ӫH���F�C\n");
    }

    // function 3: leave - leave this clan
    if( arg == "leave" ) {
	if( me->query("clan/clan_level") > 1 )
	    return notify_fail("�Х���¾�쭰�ܤ@�������C\n");
	log_file("CLAN",sprintf("[%s] %s: %s(%s) leaves\n",
	    ctime(time()), me->query("clan/clan_name"), me->name(),
	    me->query("id")) );
	clan_line("���H�ŧG, �Y��_�h�X" + me->query("clan/clan_name")
	    + "�C\n");
	me->delete("clan/clan_name");
	me->delete("clan/clan_level");
	me->delete("clan/nick");
	me->delete("clan/rank");
	if( obj = present("clan symbol", me) )
	    destruct(obj);
#ifdef SAVE_USER
	me->save();
#endif
	return 1;
    }
 
    // following function should classify function name
    if( sscanf(arg, "%s %s", arg, target)!=2 ) 
	return notify_fail("�Х�help ccmd�d�ߥ��T�����O�榡�C\n");

    // function 4: nick - change clan nickname
    if( arg == "nick" ) {
	me->set("clan/nick", target);
	tell_object(me, "Ok.\n");
	return 1 ;
    }

    // searching target
    //who = present(target, environment(me));
    who = find_player(target);
    if( !who || !userp(who) ) return notify_fail("�S���o�ӤH�C\n");

    // function 5: join - apply to join a clan
    if( arg == "join" ) {
        if( me->query("clan/clan_name") ) 
	    return notify_fail("�A�w�[�J�L�����A�Х�������������C\n");
	if( who->query("clan/clan_level") < 2 )
	    return notify_fail("���H�ëD�������ѡC\n");

	if( !present(target, environment(me)) )
	    return notify_fail("�o�̨S���o�ӤH�C\n");

	message_vision(HIW"$N�V$n�ӽХ[�J"+who->query("clan/clan_name")
	+"�C\n"NOR, me, who);
	me->set_temp("clan/apply", 1);
	return 1;
    }

    // following cmds only clan member can use them
    if( !me->query("clan/clan_name") ) return notify_fail("�A�ëD���������C\n");
    // the cmds need clan_level > 1 
    if( me->query("clan/clan_level") < 2 )
	return notify_fail("���~���O�Ϊk�A������¾�������C\n");    

    // function 6: accept - accept somebody join my clan
    if( arg == "accept" ) {
	if( !arg ) return notify_fail("�A�Q���֤J��??\n");

        if( !present(target, environment(me)) )
            return notify_fail("�o�̨S���o�ӤH�C\n");

	if( who->query_temp("clan/apply") ) {
	    obj = new("/obj/clan_symbol");
	    obj->move(who);
	    seteuid( geteuid() );
	    who->delete_temp("clan/apply");
	    who->set("clan/clan_name", me->query("clan/clan_name"));
	    who->set("clan/rank", "����");
	    who->set("clan/nick", "�L");
	    who->set("clan/clan_level", 1);

	    log_file("CLAN", sprintf("[%s] %s: %s(%s) accepts %s(%s)\n",
		ctime(time()), me->query("clan/clan_name"), me->name(),
		me->query("id"), who->name(), who->query("id")));

	    tell_object(who, HIY+me->name() + "�浹�A�@�������H���C\n"NOR);
	    clan_line("�w��"+who->name()+"�[�J" +
		me->query("clan/clan_name") + "!!\n"); }
        else {
            tell_object(me, "���H�å��V�A�ӽХ[�J�����C\n");
	}
	return 1;
    }

    // check if same clan
    if( who->query("clan/clan_name") != me->query("clan/clan_name") )
	return notify_fail("�L���O���������C\n");

    // function 7: kickout - kickout someone from clan members  
    if( arg == "kickout" ) {
	if( target == me->query("id") ) 
	    return notify_fail("�n�q���Х�: ccmd leave.\n");
	if( who->query("clan/clan_level") == 2 
	&& me->query("clan/clan_level") != 3 ) 
	    return notify_fail("���ѥ��ݥ����D�˦۳B�z�C\n");
	if( who->query("clan/clan_level") == 3 )
	    return notify_fail("����C\n");

        seteuid( getuid() );
	if( who->query("clan/clan_level") == 2 ) {
	    // ���]���Ѽƥ�
	    me->add("clan/elder", -1); }
	clan_line("�Y��_, " + who->name() + "���A�O���������C\n");
	log_file("CLAN",sprintf("[%s] %s: %s(%s) kickouts %s(%s)\n",
	    ctime(time()), me->query("clan/clan_name"), me->name(),
	    me->query("id"), who->name(), who->query("id")) );
	tell_object(who, HIY"�A�w�g���A�O" +
	    who->query("clan/clan_name") + "�������F�C\n"NOR);
	who->delete("clan/clan_name");
	who->delete("clan/clan_nick");
	who->delete("clan/clan_level");
	who->delete("clan/rank");
	if( obj = present("clan symbol", who) )
	    destruct(obj);
#ifdef SAVE_USER
	me->save();
	who->save();
#endif
	return 1;
    }

    // the cmds for clan leader
    if( me->query("clan/clan_level") < 3 )
	return notify_fail("���~���O�Ϊk�A������¾�������C\n");

    // function : promote - promote the level of clan member
    if( arg == "promote" ) {
	if( target == me->query("id") ) return notify_fail("����!\n");
	if( who->query("class") == "commoner" )
	    return notify_fail("������O�����H����n¾�C\n");
	if( me->query_temp("clan/change_leader") ) {
	    me->delete_temp("clan/change_leader");
	    clan_line("���H�w�����������, �Y��_, ��"
		+ who->name() + "�~��" + me->query("clan/clan_name")
		+ me->query("clan/rank") + "��¾�C\n");

	    seteuid( getuid() );
	    who->set("clan/clan_level", 3);
	    who->set("clan/elder", me->query("clan/elder"));
	    who->set("clan/rank", me->query("clan/rank"));
	    tell_object(who, HIY"�A��¾��Ѫ��Ѥɬ�" +
	    	me->query("clan/rank") + "�C\n"NOR);
	    me->delete("clan/elder");
	    me->set("clan/clan_level", 2);
	    me->set("clan/rank", "����");
	    tell_object(me, HIY"�A��¾���" + who->query("clan/rank") +
		"�������ѡC\n"NOR);
#ifdef SAVE_USER
	    me->save();
	    who->save();
#endif
	    log_file("CLAN", sprintf("[%s] %s changes %s: %s(%s) to %s(%s)\n",
		ctime(time()), me->query("clan/clan_name"), 
		who->query("clan/rank"), me->name(), me->query("id"),
		who->name(), who->query("id")) );
	    return 1;
	}

	if( who->query("clan/clan_level") == 2 ) {
	    if( who->query("level") < 40 ) {
		tell_object(me, "���H��O�����H���"
		    + me->query("clan/rank")+"��¾�C\n");
		return 1;
	    }
	    tell_object(me, HIY"�`�N!! ���|�N��" + who->name() +
		"���N�A�ثe��" + me->query("clan/rank") + "�a��," +
		"�Y�O���T�ЦA��J�@���C\n"NOR);
	    me->set_temp("clan/change_leader", 1);
	    return 1;
	}

	if( me->query("clan/elder") > 2 )
	    return notify_fail("�������ѤH�Ƥw��, �L�k�A���s���ѡC\n");

	if( who->query("level") < 20 ) 
	    return notify_fail("���H��O�����H�����Ѥ�¾�C\n");

	clan_line("�Y��_, " + who->name() + "�ɬ�" + 
	    me->query("clan/clan_name") + "���ѡC\n");
	seteuid( getuid() );
	me->add("clan/elder", 1);
	if( who->query("clan/elder") )
	    who->delete("clan/elder");
	who->set("clan/clan_level", 2);
	who->set("clan/rank", "����");
	log_file("CLAN", sprintf("[%s] %s: %s(%s) promotes %s(%s)\n",
	    ctime(time()), me->query("clan/clan_name"), me->name(),
	    me->query("id"), who->name(), who->query("id")) );
#ifdef SAVE_USER
	me->save();
	who->save();
#endif
	return 1;
    }

    // function 9 : demote - demote the level of clan member
    if( arg == "demote" ) {
	if( target == me->query("id") ) 
	    return notify_fail("�A���ݥ��Ǧ쵹����\n");

	if( who->query("clan/clan_level") == 1 )
	    return notify_fail("�L��¾���w�O�̧C�F, �L�k�A���C\n");

	clan_line("�Y��_, ���� " + who->name() + "���Ѥ�¾, �����@�������C\n");
	seteuid( getuid() );
	me->add("clan/elder", -1);
	who->set("clan/clan_level", 1);
	who->set("clan/rank","����");
	log_file("CLAN", sprintf("[%s] %s: %s(%s) demotes %s(%s)\n",
	    ctime(time()), me->query("clan/clan_name"), me->name(),
	    me->query("id"), who->name(), who->query("id")) );
#ifdef SAVE_USER
	me->save();
	who->save();
#endif
	return 1;
    }
}

varargs int clan_line(string msg, int emote) 
{
    object *usr, me, obj;
    int i, tmp;

    me = this_player();

    if(!msg) return notify_fail("�A�n�糧�������P�񻡤���S\n");

    if( me->query_temp("pending/hidden") ) {
        tmp = me->query_temp("pending/hidden");
        me->delete_temp("pending/hidden");
    }

    if( !obj = present("clan symbol", me) )
	return notify_fail("�Х����o�����H���C\n");

    usr = filter_array(users(), "filter_clan", obj);
    if(sizeof(usr))
        for(i=0; i<sizeof(usr); i++)
            if (emote)
                message("system", HIY"�i"+me->query("clan/clan_name")+"�j"
                HIW+msg+"\n"NOR, usr[i]);
            else
                message("system", HIY"�i"+me->query("clan/clan_name")+"�j"
                +me->name()+"("+me->query("id")+")�G"HIW
                +msg+"\n"NOR, usr[i]);

    if( tmp > 0 ) {
        me->set_temp("pending/hidden", tmp); }
    return 1;
}

int help(object me)
{
write(@HELP
�����O�������M�Ϋ��O, ���O�榡:
   1. ccmd: �i�d�ߥثe�w���ߪ������έt�d�H
   2. ccmd verify: �ɵo�H��
   3. ccmd leave: �q��
   4. ccmd nick <�ԭz>: ���A�b�������κ�
   5. ccmd join <���aid>: �ӽХ[�J����
HELP
	);

    if( me->query("clan/clan_level") > 1 ) {
write(@HELP
   6. ccmd accept <���aid>: �����[�J�����ӽ�
   7. ccmd kickout <���aid>: �����Ӫ��a���������
HELP
        );
    }

    if( me->query("clan/clan_level") > 2 ) {
write(@HELP
   8. ccmd promote <���aid>: ���@����¾��
   9. ccmd demote <���aid>: ���C����¾��
HELP
	);
    }
	return 1;
}
