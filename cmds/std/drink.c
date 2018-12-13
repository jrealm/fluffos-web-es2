/*  drink.c

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

    notify_fail("�A�n�ܤ���S\n");
    if( !arg || arg=="" ) return 0;

    if( !me->query_stat_maximum("kee") ) // changed by dragoon
        return notify_fail("�A��Y�嵷�A�L�k�ܤU����F��C\n");

    if(me->query_stat_maximum("water") <= me->query_stat("water"))
        return notify_fail("�A�A�]�ܤ��U�F��F�C\n");

    // Drink from liquid containers.
    if( sscanf(arg, "from %s", arg) ) {
        object liq;

        ob = present(arg, me);
        if( !ob ) ob = present(arg, environment(me));
        if( !ob ) return notify_fail("�o�̨S���o�˪F�� ...�C\n");
        if( !ob->query("liquid_container") )
            return notify_fail( ob->name() + "�ä��O�ˤ����e���C\n");
        foreach(liq in all_inventory(ob))
            if( liq->query_volume()) {
                liq->drink_ob(me);
                me->start_busy(1);
                return 1; }

        return notify_fail( ob->name() + "�̨S�������ܪ��F��C\n");
    }

    return environment(me)->do_drink(arg);
}

int help()
{
    write(@TEXT
���O�榡�G drink from <something>, drink <something>

�o�ӫ��O�i�H�ΨӶ����γܤU�Y�ǲG��, �p�s�u�B�e���B�s���CSomething �i�ର��
��r, �ݤ�����e�����]�\���ݭn�Ψ��� from�C

TEXT
    );
    return 1;
}
