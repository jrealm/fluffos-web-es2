// which.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string f;

	if( !arg ) return notify_fail("���O�榡�Rwhich <���O>\n");

	if( f = me->find_command(arg) ) {
		write(f + "\n");
		return 1;	
	}
	write("�A�����O���|���S���o�ӫ��O�M�иո� localcmds �o�ӫ��O�C\n");
	return 1;
}

int help(object me)
{
	write(@Help
���O�榡: which <���O>

��X���O�Ҧb���ؿ��C

Help
	);
	return 1;
}
