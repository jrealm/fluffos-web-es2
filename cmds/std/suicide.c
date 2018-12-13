/*  suicide.c

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
#include <command.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    object link_ob;
    string passwd;

    SECURED_COMMAND;

    if( !(link_ob = me->link()) )
        return notify_fail("�A���s�u���󤣨��F�M�{�b�L�k�۱��C\n");

    if( !arg ) return notify_fail("���O�榡�Rsuicide <�K�X>\n");

    passwd = link_ob->query("password");
    if( crypt(arg, passwd) != passwd )
        return notify_fail("�K�X���~�T\n");

    log_file("static/SUICIDE",
        sprintf("[%s] %s committed suicide from %s\n",
	    ctime(time()), geteuid(me), query_ip_name(me)) );
    CHANNEL_D->do_chnnel(me, "sys", me->name() + "�۱��F�C\n");

    rm( link_ob->query_save_file() );
    rm( me->query_save_file() );
    
    write("�n�a�A�Ʊ��ٯ�ܧ֦A ES2 ���ݨ�z�C\n");
    tell_room(environment(me), me->name() +
        "�۱��F�M�H��A�A�]�ݤ���o�ӤH�F�C\n", ({me}));

    destruct(link_ob);
    destruct(me);

    return 1;
}

int help (object me)
{
    write(@HELP
���O�榡�Rsuicide <�K�X>
 
�p�G�]���Y�ح�]�A���Q���F�M�A�i�H�γo�Ӧ۱����O�ӧR���A���H���M�۱�
�H��|�N�A���H���s�ɧ����۵w�ФW�����M�L�k�Ϧ^�F�M�ҥH�۱��e�аȥ��T
��C

�o�ӫ��O�ä��O�����a���Ӯ����a�¯٧Ův�� mud�޲z�̪��M�۱��@�ӤH����
���a��Ův�Ө��M�����O�ַN���쪺�M�]���o�M�{��ͬ������u���`�v�b�Y��
�h���W�O�㦳�ۦP�N�q���M�]����ܦ۱����~�|���e�Х��T�w�A�w�g�Q�M����
�T����ճo�ӫ��O���\�ΡC
HELP
    );
    return 1;
}
