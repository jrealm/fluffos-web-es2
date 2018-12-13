/*  pwd.c

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

int main(object me, string arg)
{
    write("�ثe�u�@�ؿ��G" + (string)me->query("cwd") +  "\n");
    write("�ثe�u�@�ɮסG" + (string)me->query("cwf") +  "\n");
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : pwd
 
�o�ӫ��O�|��ܥX�A�ثe���u�@�ؿ�(cwd)�Τu�@�ɮ�(cwf)�A��A�ϥ� ls �Ψ�L
�P�ɮצ��������O�ɡA�|���j�M�ثe���u�@�ؿ��C

�u�@�ɮ׬O�A�W�@���ϥ� update �ҧ�s���ɮסC 
HELP
    );
    return 1;
}
