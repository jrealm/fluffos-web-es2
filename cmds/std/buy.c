/*  buy.c

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
    string item, targ;
    object ob, owner;
    mixed handle;
    int price, afford;

    if( me->is_busy() ) return notify_fail("�A�{�b�S���šT\n");

    if( !arg || sscanf(arg, "%s from %s", item, targ)!=2 )
        return notify_fail("���O�榡�Rbuy <�Y��> from <�Y�H>\n");

    if( !objectp(owner = present(targ, environment(me))) )
        return notify_fail("�A�n��ֶR�F��S\n");

    if( userp(owner) ) {
        message_vision("$N�Q�V$n�ʶR�u" + item + "�v�C\n", me, owner);
        return 1;
    }

    // add by dragoon
        if( objectp(owner) && owner->query("no_fight") )
                return notify_fail("����??\n");

    if( !living(owner) )
        return notify_fail("�ݰ_��"+owner->name()+"�w�g�L�k�R��F��F�C\n");
        
    if( owner->is_fighting() )
        return notify_fail("�ݰ_��" + owner->name() + "������ ... ���[�M�S�Ųz�A�C\n");

    notify_fail("���n�����@�N��A����C\n");
    if( !(handle = owner->affirm_merchandise(me, item)) ) return 0;
    price = owner->query_trading_price(handle);

    switch( me->can_afford(price) ) {
        case 0: return notify_fail("�A���W���������C\n");
        case 1:
            me->pay_money(price);
            owner->deliver_merchandise(me, handle);
            me->gain_score("survive", random(price/300 + me->query_attr("wis")/3) );
            return 1;
        case 2:
            return notify_fail("�A�S���������s���M�ӹ��]�䤣�}...�C\n");
    }

}

int help(object me)
{
   write( @HELP
���O�榡: buy <something> from <someone>

�o�@���O���A�i�H�q�Y�ǤH���W�R�쪫�~�C
HELP
   );
   return 1;
}
