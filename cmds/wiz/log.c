// log.c

inherit F_CLEAN_UP;

int main(object me, string msg)
{
	string *lines;

	if( !msg || msg=="" ) return 0;

	lines = explode(msg, "\n");
	for(int i=0; i<sizeof(lines); i++)
		lines[i] = "    " + lines[i];
	msg = implode(lines, "\n") + "\n";

	seteuid(geteuid(this_player(1)));
	write_file(me->query("cwd") + ".ChangeLog",
		"\n" + ctime(time()) + " By " + capitalize(getuid(me)) + "\n\n" + msg);
	write("Ok.\n");
	return 1;
}

int help(object me)
{
	write(@Help
���O�榡: log <msg>

�N�Ұ��L�����ܰO���b�ӥؿ��U�� .ChangeLog ��
�p�G�ҭn�W�L���@��, �i�� to log �ӰO���C
Help
	);
	return 1;
}
