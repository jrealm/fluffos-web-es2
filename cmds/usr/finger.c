/*  finger.c - inquiry other users' information

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

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    SECURED_COMMAND;

    if( !arg ) {
	if( !wizardp(me) )
	    return notify_fail("�A�n�d�߭���ϥΪ̪���ơH\n");
	me->start_more( FINGER_D->finger_all() );
    } else
	write( FINGER_D->finger_user(arg) );

    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡�Gfinger [<�ϥΪ̩m�W>]
 
�o�ӫ��O�i��ܬY�Ӫ��a���s�u�A�v������ơA�p�G�A�O�Ův�A�h�����w�ϥΪ̩m�W
�|��ܥX�Ҧ����b�u�W�����a���s�u��ơC
 
��L�������O�Gwho
HELP
    );
    return 1;
}
 
