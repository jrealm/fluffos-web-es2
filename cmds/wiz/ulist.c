// user list

inherit F_CLEAN_UP;

int main(string str)
{
        object *ob;
        int i;
        ob=users();
        i = sizeof(ob);
        while (i--) {
        write(sprintf("%15s : %30s\n",ob[i]->query("id"),
        file_name(ob[i])));
        }
        return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : ulist

�N�u�W�Ҧ����a��/obj/user number ��ܥX�ӡC
HELP
    );
    return 1;
}
