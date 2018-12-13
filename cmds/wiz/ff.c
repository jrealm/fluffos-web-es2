// ff.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string dest, func, file;

	if(!arg || sscanf(arg, "%s %s", dest, func)!=2 )
		return notify_fail("���O�榡�Rff <����> <��ƦW��>\n");

	if( dest=="me" ) ob = me;
	else if( dest=="here" ) ob = environment(me);
	else ob = present(dest, me);

	if( !ob ) ob = present(dest, environment(me));
	if( !ob ) ob = find_object(resolve_path(me->query("cwd"), dest));
	if( !ob ) return notify_fail("�o�̨S���u" + dest + "�v�C\n");

	file = function_exists(func, ob);
	if(!file)
		printf("���� %O �èS���w�q %s �o�Ө�ơC\n", ob, func);
	else
		printf("���� %O �� %s ��Ʃw�q�b %s.c�C\n", ob,	func, file );
	return 1;
}

int help()
{
	write(@TEXT
���O�榡�Rff <����> <��ƦW��>

�o�ӫ��O�i�H��X���w���󤤪��Y�Ө�Ʃw�q�b���@���ɮ׸̡C
TEXT
	);
	return 1;
}
