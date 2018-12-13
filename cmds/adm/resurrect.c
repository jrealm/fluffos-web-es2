// resurrect command..

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;
        int i;

        seteuid(ROOT_UID);
        if(!str) return notify_fail("���O�榡: resurrect <�ϥΪ�>\n");
        ob = LOGIN_D->find_body(str);
        if(!ob) return notify_fail("�u�W���ϥΪ̤��S���o�ӤH�C\n");
        write(file_name(environment(ob))+"\n");
	CHAR_D->make_living(ob);
	ob->setup();

        // ok ..
        write("ok.\n");
        return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : resurrect <�Y�H>

�����O�i���A(�p)�N�Y�H�_���C
HELP
    );
    return 1;
}
