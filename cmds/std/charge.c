// charge.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if( !arg || arg=="" ) {
		if( ob = me->query_charging() ) {
			write("�A�{�b�H" + ob->name() + "�����n�����ؼСC\n");
			return 1;
		}
		write("�A�{�b�èS����w���n�����ؼСC\n");
		return 1;
	}

	if( arg=="cancel" ) {
		write("Ok.\n");
		me->remove_charge();
		return 1;
	}

	ob = present(arg, environment(me));
	if( !ob ) return notify_fail("�o�̨S���o�ӤH�C\n");

	if( !me->is_fighting(ob) )
		return notify_fail("�A�{�b�èS���b��" + ob->name() + "�԰��C\n");
	me->charge_ob(ob);
	write("Ok.\n");

	return 1;
}

int help(object me)
{
	write(@TEXT
���O�榡�Rcharge [<�԰��ؼ�>|cancel]

�o�ӫ��O���A��w�@�ӥ��b�M�A�԰������ĤH�����n�����ؼСM�ҿ׭��n����
�ؼЬO����o�ӥؼ��٦b��A�԰����ɭԡM�|������L�ĤH�ӱM�D�o�ӥؼЧ�
���M�p���@�ӧA�i�H���������O��������i�Ȫ��ĤH�M���O�۹諸�M�A���L
�ĤH���������m�v�N�u�����`�� 2/3�C

�n���� charge �Ҧ��M�i�H�� charge cancel�M���[����Ѽƫh��ܧA�ثe��
����������H�C
TEXT
	);
	return 1;
}
