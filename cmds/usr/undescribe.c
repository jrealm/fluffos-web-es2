/*  undescribe.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me)
{
    me->delete("long");
    write("Ok�C\n");
    return 1;
}

int help()
{
    write(@TEXT
���O�榡�Rundescribe

�o�ӫ��O���A�����A�ۤv���y�z�C
TEXT
    );
    return 1;
}
