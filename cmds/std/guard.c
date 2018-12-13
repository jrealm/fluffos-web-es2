// guard.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

	if( me->query("life_form") == "ghost" )
		return notify_fail("�H���F�N�@�F�ʤF, �֥h�䫰���_���a!!\n");

        if( !arg || arg=="" ) {
                if( ob = me->query_guarding() ) {
                        write("�A�{�b�O�@����H�O" + ob->name() + "�C\n");
                        return 1;
                }
                write("�A�{�b�èS����w�O�@����H�C\n");
                return 1;
        }

        if( arg=="cancel" ) {
                write("Ok.\n");
                me->guard_ob(0);
                return 1;
        }

        ob = present(arg, environment(me));
        if( !ob ) return notify_fail("�o�̨S���o�ӤH�C\n");
        if( ob==me ) return notify_fail("�A�u�z�ҷ�M�v���|�O�@�ۤv�C\n");
        if( !userp(ob) )
                return notify_fail("�L���ݭn�A���O�@�C\n");
        if( me->query("level") < 5)
                return notify_fail("���A���j�I�A�ӫO�@�O�H\n");
        if( me->is_fighting(ob) )
                return notify_fail("�A�Q�O�@���b��A�԰������H\n");

        me->guard_ob(ob);
        write("Ok.\n");

        return 1;
}

int help(object me)
{
        write(@TEXT
���O�榡�Rguard [<�԰��ؼ�>|cancel]

�A�i�H�γo�ӫ��O�]�w�A�n�O�@����H�A��A�O�@����H�D�������ɡA�A���H���|�b
�Ĥ@�ɶ��[�J�԰��U�ԡC

�n���� guard �Ҧ��M�i�H�� guard cancel�M���[����Ѽƫh��ܧA�ثe�ҫO�@����
�H�E
TEXT
        );
        return 1;
}
