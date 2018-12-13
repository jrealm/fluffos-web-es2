/*  uptime.c

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

// This command is also called by LOGIN_D, so we don't want it use 
// arguments.
int main()
{
    seteuid(getuid());
    write("�F��G�Ƣ��w�g����F" + CHINESE_D->chinese_period(uptime()) + "�C\n");
    printf("�{�b�ɶ� "+ctime(time())+"\n");
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : uptime
 
�o�ӫ��O�i�D�A�F��G�� II �w�g�s�����F�h�[�C
�γo�x�����ثe���ɶ��C
 
HELP
    );
    return 1;
}
