/*  wield.c

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

varargs int do_wield(object me, object ob);

int main(object me, string arg)
{
    string skill;
    object ob, *inv;
    int i, count;

    if( me->is_busy() ) return notify_fail("�A�{�b�S���šT\n");

    if( !arg ) return notify_fail("�A�n�˳Ƥ���Z���S\n");

    if(arg=="all") {
        inv = all_inventory(me);
        for(count=0, i=0; i<sizeof(inv); i++) {
            if( inv[i]->query("equipped") ) continue;
            if(do_wield(me, inv[i]) ) count ++;
        }
        write("Ok.\n");
        return 1;
    }

    // Get skill type if specified.
    sscanf(arg, "%s as %s", arg, skill);

    if( !objectp(ob = present(arg, me)) )
        return notify_fail("�A���W�S���o�˪F��C\n");

    return do_wield(me, ob, skill);
}

varargs int do_wield(object me, object ob, string skill)
{
    string str;

    if( ob->wield(skill) ) {
        if( !stringp(str = ob->query("wield_msg")) )
            str = "$N�˳�$n�@�Z���C\n";
        message_vision(str, me, ob);
        return 1;
    } else
        return 0;
}

int help(object me)
{
    write(@HELP
���O�榡�Rwield <�Z���W��> [as <�Z���ޯ�>]
 
�o�ӫ��O���A�˳ƬY�󪫫~�@�Z���M�A���ݭn�֦��o�˪��~�C���ǪZ���i�H���\�h
�اL���ϥΡM�Ҧp�@����C�i�H��C�ϡM�]�i�H��M�A�M�A�i�H��

wield broadsword as sword ��
wield broadsword as blade �ӫ��w�C��L���k�p:

wield blade as twohanded blade
wield dagger as secondhand dagger
wield kris 2 as secondhand blade

�Y��Z�������k�i�঳�@�إH�W�A���k���P�ɤ޵o���Z���¤O�i��]���P�A�A�i�H�b
���_�� identify ����o��L��T�C

HELP
    );
    return 1;
}
