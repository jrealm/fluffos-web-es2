/*  keep.c

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

int main(object me, string arg)
{
    object ob, *all_ob;
    int i;

    if( !arg ) return notify_fail("���O�榡�Gkeep <���W���~>\n");
    if( arg=="all" ) {
        all_ob = all_inventory(me);
        i = sizeof(all_ob);
        while( i-- )
            all_ob[i]->set("keep_this", 1);
        write("�A�N�Ҧ����W���F��O�F�Ӥp�O�����C\n");
        return 1;
    }
    if( arg=="none" ) {
        all_ob = all_inventory(me);
        i = sizeof(all_ob);
        while( i-- )
            all_ob[i]->set("keep_this", 0);
        write("�A�N�Ҧ����W���F�褧�p�O�����M���C\n");
        return 1;
    }
    ob = present(arg, me);
    if( !ob ) return notify_fail("�A���W�S���o�˪F��C\n");
    if( userp(ob) ) return notify_fail("����C\n");
    if( ob->query("keep_this") ) {
        ob->delete("keep_this");
        write("�A�� " + ob->name() + " �W�����p�O�����M���F�C\n");
    }
    else {
        ob->set("keep_this", 1);
        write("�A�b " + ob->name() + " �W�����F�Ӥp�O�����C\n");
    }
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡�Gkeep <���W���~>|<all>|<none>

�Ҧp:
keep none    �N�Ҧ����~�Ѱ� keep
keep sword    �w�� sword �]�w keep �θѰ� keep

�]�w���W���n���~���|�Q���p�ߥ��(�p drop all �� sell all)�A�i�H inventory
���O�d�ݬO�_�w�]�w keep ���C

�]�w���H�N��󪺪F��u����A���w���/��X�o�ӪF��ɤ~�|�Q���ν�X�A�åB��
�]�w�|�Q�Ѱ��C�Y�A�N�]�w���H�N��󪺪��~���a�W�A�A�߰_�ӥ������s�]�w�@���C
HELP
    );
    return 1;
}
