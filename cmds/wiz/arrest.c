// arrest command..

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;
        int i;

        seteuid(getuid(me));
        if(!str) return notify_fail("���O�榡: arrest <�ϥΪ�>\n");
        ob = LOGIN_D->find_body(str);
        if(!ob) return notify_fail("�u�W���ϥΪ̤��S���o�ӤH�C\n");
	if(ob->query("level") > 4 ) 
		return notify_fail("�L���b�O�Q�O�@�����Ť��Ψ����L���O�@\n");

	seteuid(geteuid(ob));
	if (ob->query("get_kill") == 1) {
		ob->set("get_kill", 0) ; 
		tell_object(ob, "�Ův("+me->query("id")+")��_�A���O�@\n");
		tell_object(me,"�A��_�F���a("+ob->query("id")+")���O�@\n");
		}
	else {
		ob->set("get_kill", 1) ;
		tell_object(ob, "�Ův("+me->query("id")+")�����A���O�@\n");
                tell_object(me,"�A�������a("+ob->query("id")+")���O�@\n");
		}
        return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : arrest <�Y�H>

�����O�i���A�����S�w�c�H���a�����ūO�@
HELP
    );
    return 1;
}
