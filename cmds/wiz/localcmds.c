// localcmds.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mixed *cmds;
	int i;

	cmds = me->query_commands();
	write("�A���W�Υ|�P�����~�P�Ҧb�����Ҵ��ѥH�U���O�R\n");
	for(i = 0; i<sizeof(cmds); i++) {
		if( cmds[i][2]==me ) continue;
		printf("%-15s  %2d %O\n", cmds[i][0], cmds[i][1], cmds[i][2]);
	}
	return 1;
}

int help()
{
	write(@TEXT
���O�榡�Rlocalcmds

�C�X�A���W�Υ|�P�����~�P�Ҧb�����Ҵ��Ѫ��Ҧ����O�C
TEXT
	);
	return 1;
}

