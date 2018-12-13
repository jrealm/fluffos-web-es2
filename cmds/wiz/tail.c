// tail.c

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string file;

	seteuid(geteuid(this_player(1)));
    if (!arg) return help(me);
	file = resolve_path(me->query("cwd"), arg);
	if( file_size(file)<0 ) return notify_fail("�S���o���ɮסC\n");
	tail(file);
	return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : tail <�ɮ�>

�����O�i���A(�p)����Ū���Y�ɮ׳̥������X��C
HELP
    );
    return 1;
}
