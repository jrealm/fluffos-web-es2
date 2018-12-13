/*  status.c

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

int main(object me,string arg)
{
    string msg;

    msg = (string)mud_status(arg=="detail" ? 1 : 0);
    if( stringp(msg) ) write(msg);
    else write("�L�C\n");

    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡�Gstatus [detail]
 
�o�ӫ��O�i�H��ܥX�ثe�t�Ϊ��έp��ơC
 
HELP
    );
    return 1;
}
 
