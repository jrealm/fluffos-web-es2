// rehash.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        seteuid(geteuid(this_player(1)));
	if( !arg )
		return notify_fail("���O�榡�Rrehash <���|>\n");

	if( arg[strlen(arg)-1]!='/' ) arg += "/";
	if(  file_size(arg)!=-2 )
		return notify_fail("�S���o�ӥؿ��T\n");

	write("��s���O��R" + arg + "\n");
	seteuid(getuid());
	COMMAND_D->rehash(arg);
	return 1;
}

int help(object me)
{
	write(@HELP
���O�榡�Rrehash <�ؿ��W��>

�o�ӫ��O�|��s�t�Τ��������O��M�p�G�A�s�W�ΧR���F�Y�ӥؿ��U�����O�M������
�o�ӫ��O��s�ӥؿ��~��ϥΡC
HELP
	);
	return 1;
}
