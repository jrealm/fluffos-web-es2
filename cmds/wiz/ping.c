/*  ping.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <intermud.h>
#include <command.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string addr;
    int port;

    SECURED_WIZARD_COMMAND;

    if( !arg || sscanf(arg, "%s %d", addr, port)!=2 )
	return notify_fail("���O�榡�Gping <IP �a�}> <UDP ��>\n");

    INTERMUD_SERVICE("ping")->send_request(addr, port);
    write("Ok.\n");
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡�Gping <IP �a�}> <UDP ��>

�o�ӫ��O�i�H�ΨӴ��ջ��ݪ� MUD �O�_���椤�C

�Ъ`�N�ĤG�ӰѼƪ��𸹬O Intermud �� UDP �𸹡A���O MUD �s�u�n�J��
�𸹡C�p�G���O ES2-based �� MUD �ӧA�����D�L�̪� UDP ��A�i�H��
�լ� ES2 mudlib ���w�]�ȡA�]�N�O�n�J���� +4�C

���������G
	mudlist
HELP
    );
    return 1;
}
