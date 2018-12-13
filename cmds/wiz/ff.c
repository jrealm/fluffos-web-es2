// ff.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string dest, func, file;

	if(!arg || sscanf(arg, "%s %s", dest, func)!=2 )
		return notify_fail("Αff <ン> <ㄧ计嘿>\n");

	if( dest=="me" ) ob = me;
	else if( dest=="here" ) ob = environment(me);
	else ob = present(dest, me);

	if( !ob ) ob = present(dest, environment(me));
	if( !ob ) ob = find_object(resolve_path(me->query("cwd"), dest));
	if( !ob ) return notify_fail("硂柑⊿Τ" + dest + "\n");

	file = function_exists(func, ob);
	if(!file)
		printf("ン %O ⊿Τ﹚竡 %s 硂ㄧ计\n", ob, func);
	else
		printf("ン %O  %s ㄧ计﹚竡 %s.c\n", ob,	func, file );
	return 1;
}

int help()
{
	write(@TEXT
Αff <ン> <ㄧ计嘿>

硂т﹚ンい琘ㄧ计﹚竡郎柑
TEXT
	);
	return 1;
}
