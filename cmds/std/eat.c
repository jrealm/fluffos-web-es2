/*  eat.c

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

int main(object me, string arg)
{
    object ob;

    if( me->is_busy() ) return 0;

    if( !arg || arg=="" ) return notify_fail("�A�n�Y����S\n");

    if( !me->query_stat_maximum("kee") )
        return notify_fail("�A�S������M�L�k�i���C\n");

    ob = present(arg, me);
    if( !ob ) ob = present(arg, environment(me));
    if( !ob ) return notify_fail("�o�̨S���o�˪F�� ...�C\n");
    if( inherits(COMBINED_ITEM, ob) && !ob->query_amount() )
	return notify_fail("�A�o����f���������]�U�h�I\n");

    notify_fail("�o�˪F�褣��Y�C\n");
    if( ob->stuff_ob(me) ) {
        me->start_busy(1);
        return 1;
    }
    return 0;
}

int help()
{
    write(@TEXT
���O�榡�Geat <���~>

�o�ӫ��O�Ψ����A���H���i���ΪA���Ī��Aes2 ���M�]�w�F�����A���O�q�`�A������
�u��ͬ��@�ˤ@�ѦY�T�\�A�u�n�{�l�j�ɦA�Y�N�i�H�F�C

�԰����Y�����|���h�@���������|�C
TEXT
    );
    return 1;
}
