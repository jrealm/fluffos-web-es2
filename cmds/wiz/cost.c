// cost.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping before, after;
	int stime, usertime, eval_cost;

	if( me != this_player(1) ) me = this_player(1);

	seteuid(getuid());
   	if(!arg) return notify_fail("���O�榡�Rcost <���O> [<�Ѽ�> ....]\n");

	before = rusage();
	eval_cost = eval_cost();
	me->force_me(arg);
	eval_cost -= eval_cost();
	after = rusage();
	usertime = after["utime"] - before["utime"];
	stime = after["stime"] - before["stime"];
	printf("\n�t�ήɶ��R%d �L��\n�ϥΪ̮ɶ��R%d �L��\n������O�ơR%d\n",
		stime, usertime, eval_cost );
		
	return 1;
}

int help()
{
	write( @TEXT
���O�榡�Rcost <���O> [<�Ѽ�> .... ]

�o�ӫ��O���A���q�t�@�ӫ��O����һݪ��ɶ��C
TEXT
	);
	return 1 ;
}
