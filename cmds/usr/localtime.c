/*  localtime.c

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

int main(object me, string arg)
{
    int time;
    seteuid(getuid());
    time = time();
    printf("%i\n",time);
    printf("%s\n",ctime(time));
    write("�{�b�O" + NATURE_D->game_time() + "�C\n");
    return 1;
}

int help(object me)
{
     write(@HELP
���O�榡: time

�o�ӫ��O���A(�p)���D�{�b���ɨ��C

HELP
    );
    return 1;
}
