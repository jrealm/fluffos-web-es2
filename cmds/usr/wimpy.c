/*  wimpy.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <statistic.h>

inherit F_CLEAN_UP;

void create() {seteuid(getuid());}

int main(object me, string arg)
{
    string stat, dir;
    int ratio;

    if( !arg )
    {
	string* stat_name = me->query_stat_name();
	string msg = "�A���U�����Ʀb�C��U�C��Үɷ|�۰ʰk�R�G\n";
	if( arrayp(stat_name) && sizeof(stat_name) )
	    foreach(stat in stat_name)
	    {
		ratio = me->query_stat_notify(stat);
		if( ratio > 0 )
		    msg += sprintf("  %s\t%d%%\n", to_chinese(stat), ratio);
	    }
        else
            msg += "�S���]�w�C\n";
        if( dir = me->query("wimpy_dir") )
            msg += "�A���w�]�k�]��V�O " + dir + "�C\n";
        write(msg);
        return 1;
    }

    if( sscanf(arg, "%s at %d", stat, ratio) == 2 )
    {
	if( !me->query_stat_maximum(stat) )
            return notify_fail("�A�S���o�����ƶ��ءC\n");

        if( (ratio < 0) || (ratio > 80) )
            return notify_fail("��ҥ����b 0 �� 80 �����C\n");

        me->set_stat_notify(stat, ratio);
        write("Ok�C\n");

        return 1;
    }
    else if( sscanf(arg, "to %s", dir) ) {
        me->set("wimpy_dir", dir);
        write("Ok�C\n");
        return 1;
    }
    else if( arg=="random" ) {
        me->delete("wimpy_dir");
        write("Ok.\n");
        return 1;
    }

    return notify_fail("���O�榡�Rwimpy <���ƶ���> at <���>\n");

}

int help()
{
    write(@TEXT
���O�榡�Rwimpy <���ƶ���> at <�ʤ���>
          wimpy to <��V>
          wimpy random

�o�ӫ��O���A�]�w�b�H�����Y�����ƧC��@�Ӧʤ��񪺮ɭԡM�۰ʰk�]�C
(�C�ӫ��ƶ��س��i�H�]�M�u�n�䤤�@�ӧC��A�]���ʤ���M�N�|�k�])

�i�H�]�w�����ƶ��إ]�A�R

HP        �ͩR�I��
gin       ��
kee       ��
sen       ��
food      ����
water     ����

wimpy to <��V> �i�H���A���w�k�]�ɥ������@�Ӥ�V�]�C
wimpy random �i�H��������o�w���k�]��V�C
TEXT
    );
    return 1;
}
