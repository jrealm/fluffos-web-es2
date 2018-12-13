// cost.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping before, after;
	int stime, usertime, eval_cost;

	if( me != this_player(1) ) me = this_player(1);

	seteuid(getuid());
   	if(!arg) return notify_fail("Αcost <> [<把计> ....]\n");

	before = rusage();
	eval_cost = eval_cost();
	me->force_me(arg);
	eval_cost -= eval_cost();
	after = rusage();
	usertime = after["utime"] - before["utime"];
	stime = after["stime"] - before["stime"];
	printf("\n╰参丁%d 稬\nㄏノ丁%d 稬\n磅︽计%d\n",
		stime, usertime, eval_cost );
		
	return 1;
}

int help()
{
	write( @TEXT
Αcost <> [<把计> .... ]

硂琵代秖磅︽┮惠丁
TEXT
	);
	return 1 ;
}
