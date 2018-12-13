/*  okip.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#pragma optimize
#pragma save_binary

#include <command.h>
#include <login.h>

//inherit F_CLEAN_UP;

void create()
{
    seteuid(getuid());
    set_reset(this_object(), 86400);
}


int main(object me, string str)
{
    object link_ob;
    string *args, *okip, ip;

    SECURED_COMMAND;

    if( stringp(str) ) args = explode(str, " ") - ({ "" });
    else args = ({});

    if( wizhood(me)=="(admin)" && sizeof(args) > 0 && args[0][0] != '-' ) {
	link_ob = FINGER_D->acquire_login_ob(args[0]);
	args = args[1..];
    }
    else link_ob = me->link();

    if( ! link_ob ) return notify_fail("�䤣��s�u����C\n");

    if( stringp(link_ob->query("okip")) )
	okip = explode(link_ob->query("okip"), ":");
    else
	okip = ({});

    if( ! sizeof(args) ) {
	write( sprintf( "%s �� okip �ثe�]�w���G\n\t%s\n",
		link_ob->query("id"),
		implode(okip, "\t\n")) );
	return 1;
    }

    switch(args[0])
    {
    case "-a":
	foreach(ip in args[1..])
	    if( member_array(ip, okip)== -1 ) okip += ({ ip });
	break;
    case "-d":
	okip -= args[1..];
	break;
    default:
	return notify_fail("���O�榡�Gokip [-a|-d] �s�u��m ...\n");
    }

#ifdef	SAVE_USER
    link_ob->set("okip", implode(okip, ":"));
    link_ob->save();
    if( ! link_ob->body() ) destruct(link_ob);
#endif

    write("Ok�C\n");
    return 1;
}

int help()
{
        write(@TEXT
���O�榡�Gokip [-a|-d ] [IP:IP:...]

�o�ӫ��O�i�H�]�w�A���ӷ���}, �̦h�i�]�w�Q�ձ`�Ϊ���}, ��ӷ���
�}���Ů�, �t�αN�ڵ��ӳs�u�n�D, �H����Q�Ӧ۳o�Ǧ�}�~�������H�h
�ҫI�J�C�]�w��}�ɽФp�߳]�w, �Y�O�]���ӳy������s�u�i�J��, �г�
���U�C���mail��arch�ťH�W�Ův�B�z:
1. ��char���骺�W�uIP (�O�o����, �̦n��okip�]������]�g�W�h)
2. ��char���S�x (�]�A�ݩ�, ���, �ޯ൥)
3. ��char���K�X

�d��
okip -a 111.222.333.444 �N�O�W�[�F 111.222.333.444 ���A�ӷ����|
okip -d 111.222.333.444 �N�O�R���F 111.222.333.444 ���A�ӷ����|

��}���]�w�䴩�H*�N�������X, ���@��IP��, *�u��Τ@��, �p
okip -a 140.113*	���IP�}�Y�u�n�O140.113����}���i�s�J
okip -a *.hinet.net 	���IP�u�n�̫��X����}�Ohinet.net����
			�i�s�J
TEXT
        );
        return 1;
}
