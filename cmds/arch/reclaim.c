// reclaim.c

int main(object me, string arg)
{
	int mem;

	write("��z���G�M�@�M�� " + reclaim_objects() + " ���ܼơC\n");
	return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : reclaim

�γB : �N�s�b��O����̵L�Ϊ��ܼƲM����, �H��ְO���骺�ϥΡC
HELP
     );
     return 1;
}
