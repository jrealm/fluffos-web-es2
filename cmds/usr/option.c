/*  option.h

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
    string term;
    mixed v;

    if( !arg )
    {
        mapping opt = me->query("option");
        string str = "�A�]�w���ﶵ�F\n";

        if( !mapp(opt) || !sizeof(opt) )
            str += "    �L�C\n";
        else
            foreach(term, v in opt)
                str += sprintf("    %-20s�G%O\n", term, v);
        write(str);
        return 1;
    }

    if( sscanf(arg, "%s %d", term, v)==2
    ||	sscanf(arg, "%s %s", term, v)==2 ) {
	if( !v ) me->delete("option/" + term);
	else me->set("option/" + term, v);
    } else
	return notify_fail("���O�榡�Goption <�ﶵ> <�]�w��>\n");

    write("Ok.\n");
    return 1;
}

int help()
{
    write(@TEXT
���O�榡�Goption <�ﶵ> <�]�w��>

�o�ӫ��O���A�]�w�@�Ǧ����ϥΪ̤������ﶵ�C

BRIEF_ROOM
  0 - ���ʮ��[��ж����Բӱԭz�C(�w�]��)
  1 - ���ʮɤ���ܩж����Բӱԭz�C

BRIEF_SHORT
  0 - ��ܪ��~�ΤH��������P�^��W�١C(�w�]��)
  1 - �u��ܪ��~�ΤH��������W�١C
TEXT
    );
    return 1;
}
