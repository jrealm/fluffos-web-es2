// follow.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if( !arg ) return notify_fail("���O�榡�Rfollow <�Y�H>|none�C\n");

	if( arg=="none")
		if( me->query_leader() ) {
			me->set_leader(0);
			write("Ok.\n");
			return 1;
		} else {
			write("�A�{�b�èS�����H����H�C\n");
			return 1;
		}

	if( !objectp(ob = present(arg, environment(me))) )
		return notify_fail("�o�̨S�� " + arg + "�C\n");

        // add by dragoon
        if( userp(ob) && !interactive(ob) )
                return notify_fail("�o�H�{�b���b�u�W�C\n");   

	if( !ob->is_character() )
		return notify_fail("����S���H...." + ob->name() + "�C\n");

	if( ob==me )
		return notify_fail("���H�ۤv�S\n");

	me->set_leader(ob);
	message_vision("$N�M�w�}�l���H$n�@�_��ʡC\n", me, ob);

	return 1;
}

int help (object me)
{
	write(@HELP
���O�榡�Rfollow [<�Y�H>|none]
 
�o�ӫ��O���A����H�Y�H�Υͪ��C
�p�G��J follow none �h������H�C
 
HELP
	);
	return 1;
}
