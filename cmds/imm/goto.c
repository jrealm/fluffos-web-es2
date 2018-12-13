/*  goto.c

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
    int goto_inventory = 0, goto_object = 0;
    object obj, oldenv;
    string msg;

    SECURED_COMMAND;

    if( !arg ) return notify_fail("�A�n�h���̡S\n");

    if( sscanf(arg, "-i %s", arg) ) goto_inventory = 1;
    if( sscanf(arg, "-o %s", arg) ) goto_object = 1;

    if( !arg ) return notify_fail("�A�n�h���̡S\n");

    obj = find_player(arg);
    if(!obj) obj = find_living(arg);
    if(!obj && goto_object ) obj = present(arg, environment(me));
    if(!obj || !obj->visible(me)) {
        arg = resolve_path(me->query("cwd"), arg);
        if( !sscanf(arg, "%*s.c") ) arg += ".c";
        if( !(obj = find_object(arg)) ) {
            if( file_size(arg)>=0 ) {
                message("vision", "�@�}������_�M" + me->name() + "�����v�v���U�k�C\n", environment(me), me);
                return me->move(arg);
            }
            return notify_fail("�S���o�Ӫ��a�B�ͪ��B�Φa��C\n");
        }
    }

    if(!goto_inventory && !goto_object && environment(obj))
        obj = environment(obj);

    if( !obj ) return notify_fail("�o�Ӫ���S�����ҥi�H goto�C\n");

    oldenv = environment(me);
    if( !me->move(obj) )
        return notify_fail("�]���Y�زz�ѡA�A�� goto ���ѤF�C\n");

    message("vision", "�u���@�}�����L��M" + me->name() + "�����v�w�g�����F�C\n", oldenv);
    message("vision", me->name() + "�����v��M�X�{�b�@�}���������C\n", environment(me), me);

    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : goto [-i] <�ؼ�>
 
�o�ӫ��O�|�N�A�ǰe����w���ؼ�. �ؼХi�H�O�@��living �Ωж�
���ɦW. �p�G�ؼЬOliving , �A�|�Q����򨺭ӤH�P�˪�����.
�p�G���[�W -i �ѼƥB�ؼЬO living, �h�A�|�Q����� living ��
�� inventory ��.
 
HELP
    );
    return 1;
}
