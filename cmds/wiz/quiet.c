// quiet command..

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;
        int i;

        seteuid(getuid(me));
        if(!str) return notify_fail("���O�榡: quiet <�ϥΪ�>\n");
        ob = LOGIN_D->find_body(str);
        if(!ob) return notify_fail("�u�W���ϥΪ̤��S���o�ӤH�C\n");

	seteuid(geteuid(ob));
	if (ob->query("no_chat") == 1) {
		ob->set("no_chat", 0) ; 
		tell_object(ob, "�Ův("+me->query("id")+")�����A���T��\n");
		tell_object(me,"�A�����F���a("+ob->query("id")+")���T��\n");
		}
	else {
		ob->set("no_chat", 1) ;
		tell_object(ob, "�Ův("+me->query("id")+")�T��A�ϥΤ��@�W�D\n");
                tell_object(me,"�A�Ұʪ��a("+ob->query("id")+")���T��\n");
		}
        return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : quiet <�Y�H>

�Q�T���̦A���ϥ�quite �N�i�H�����T��
�����O�i���A(�p)�N�Y�H�T��ϥΤ����W�D�C
HELP
    );
    return 1;
}
