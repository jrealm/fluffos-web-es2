// qload.c

inherit F_CLEAN_UP;

int main()
{
    write(query_load_average() + "\n");
    return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : qload 

�o�ӫ��O��ܥX�ثe CPU ���t��, cmds/s �O�C��sĶ�X�� cmds
comp lines/s �O�C��X��C
HELP
    );
    return 1;
}
