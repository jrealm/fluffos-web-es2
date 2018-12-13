// disassemble.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string target, file, f;
	object ob;

        seteuid(geteuid(this_player(1)));
	if( !arg || sscanf(arg, "%s %s", target, file) != 2 )
		return notify_fail("���O�榡�Rdisassemble <����> <��X�ɦW>\n");
	
	if( !ob ) ob = present(target, me);
	if( !ob ) ob = present(target, environment(me));
	if( !ob ) {
		f = resolve_path(me->query("cwd"), target);
		if( file_size(f + ".c") > 0 ) {
			f->foo();
			ob = find_object(f);
		}
	}

	if( !ob ) return notify_fail("�A�n�ϲ�Ķ���@�Ӫ���S\n");

	f = resolve_path(me->query("cwd"), file);
	write("�ϲ�Ķ��X�� " + f + "�C\n");
	dump_prog(ob, 3, f);
	write("Ok.\n");

	return 1;
}
