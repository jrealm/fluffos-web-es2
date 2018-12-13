/*  cleanup.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string str)
{
    object ob, where, *ob_list;
    int old_size, i;

    if (!str) return notify_fail("���O�榡�Rcleanup <�ɦW>\n"); 

    str = resolve_path(me->query("cwd"), str);
    ob_list = children(str);
    old_size = sizeof(ob_list);
    ob_list->clean_up();
    foreach(ob in ob_list)
        if( ob && clonep(ob) && !environment(ob) )
//        if( ob && ob->query_volume()==0 )
            destruct(ob);
    ob_list -= ({ 0 });
    printf("�M�� %d �Ӫ���C\n", old_size - sizeof(ob_list));
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡�Rcleanup <�ɦW>

��Ҧ����w�ɦW������I�s clean_up�M�åB�M���Ҧ��Q�ƻs�X�Ӫ��M���O�S�S��
�Q��b�t�@�Ӫ��󤤪���������C
HELP
    );
    return 1;
}

