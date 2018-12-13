/*  save.c

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

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object link_ob;
    int last_save, delta_t;
    
    seteuid(getuid());

    if( !objectp(link_ob = me->link()) )
        return notify_fail("�A���O�g�ѥ��`�s�u�i�J�M�����x�s�C\n");

    if( environment(me)->query("valid_startroom") ) {
        me->set("startroom", base_name(environment(me)));
        write("��A�U���s�u�i�ӮɡM�|�q�o�̶}�l�C\n");
    }

    if( !wizardp(me)
    &&  (last_save = me->query_temp("last_save"))
    &&  (delta_t = (time()/60 - last_save)) < 5 ) {
        return notify_fail("���Ϋ�, " +delta_t+ " �����e�A�~���x�s�L, " +(5 - delta_t)+ " ������A�էa�C\n");
    }

#ifdef SAVE_USER
    if( (int)me->save() ) {
        write("�ɮ��x�s�����C\n");
        me->set_temp("last_save", (int)(time()/60) );
        return 1;
    } else {
        write("�x�s���ѡC\n");
        return 0;
    }
#else
    return notify_fail("�t�Υثe���x�s�ϥΪ̸�ơC\n");
#endif
}

int help(object me)
{
    write(@HELP
���O�榡�Rsave

��A���W�İ������G�s�_�ӡC���F���ɨt�ήĲv, �ثe�⦸ save ���ɶ����Z�̵u��
�������C quit �ɨt�η|�յ����A save�C
see also: quit, backup
HELP
    );
    return 1;
}
