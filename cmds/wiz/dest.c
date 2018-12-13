/*  dest.c

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
    string option, target, msg;
    object obj;

    SECURED_WIZARD_COMMAND;

    seteuid(geteuid(this_player(1)));

    if (!arg) return notify_fail("���O�榡 : dest <���󤧦W�٩��ɦW>\n" );

    if( sscanf(arg, "-%s %s", option, target)!=2 ) target = arg;

    if( option == "r" ) {
	if( wizhood(me)=="(admin)" ) seteuid(ROOT_UID);
	else return notify_fail("�A�S���o���v���C\n");
    }

    obj = find_object(target);
    if (!obj) obj = present(target, me);
    if (!obj) obj = present(target, environment(me));
    if (!obj) obj = find_object( resolve_path(me->query("cwd"), target) );
    if (!obj) return notify_fail("�S���o�˪���....�C\n");

    if( environment(me)==environment(obj) )
    if( !stringp(msg = me->query("env/msg_dest")) )
        msg = "$N�l��X�@�Ӷ¬}�M�N$n�]�S�F�C\n";
    else
        message_vision(msg + "\n", me, obj);

    destruct(obj);
    if(obj) write("�A�L�k�N�o�Ӫ���j��R���C\n");
    else write("Ok.\n");

    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : dest [-r] <���󤧦W�٩��ɦW>

�Q�Φ��@���O�i�N�@�Ӫ���(object)�Ϊ���w�q(class)�q�O���餤�M���M�Y�M����
��w�q(�Y�R���w�ɦW�����p�U)�h�U�@���ѦҨ�o�Ӫ��󪺮ɭԷ|���s�N���sĶ�C

�㦳 (admin) �������Ův�i�H�� -r �ﶵ�H ROOT_UID �����ӲM���Q�O�@������p
�ϥΪ̡C

�Y����b�Q�M���L�{���o�ͤF���~�M���ϥΪ̥H�~�����󤴵M�|�Q�j��M��( �ϥΪ�
����u���b�ϥ� ROOT_UID �����ɤ~��j��M�� )�M�Ө���~�T���|�Q�g��
/log/destruct ���C
  
�ѦҸ�ơR destruct()
HELP
    );
    return 1;
}
