/*  fight.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>
#include <char.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object obj, old_target;
    int rg, rk, rgm, rkm;

    if( me->query("life_form")=="ghost" )
        return notify_fail("�H���F�N�@�F�ʤF, �֥h�䫰���_���a!!\n");

    if( environment(me)->query("no_fight") )
	return notify_fail("�o�̸T��԰��C\n");
 
    if( !arg
    ||	!objectp(obj = present(arg, environment(me)))
    ||	!obj->is_character()
    ||	obj->is_corpse() )
	return notify_fail("�A�Q�����֡S\n");

    if( obj->query("no_fight") ) return notify_fail("����C\n");

    // ���i�����w�_�u���a -Dragoon
    if( userp(obj) && !interactive(obj) ) 
        return notify_fail("�o�H�{�b���b�u�W�C\n");

    if( !me->visible(obj) )
	return notify_fail( obj->name() + "�ݤ����A�A�����D�A�b�V�L�D�ԡC\n");

    if( me->is_apprentice_of(obj) )
	return notify_fail( obj->name() + "�O�A���v���T\n");

    if( obj->is_fighting(me) )
	return notify_fail("�[�o�T�[�o�T�[�o�T\n");

    if( !living(obj) && inherits(F_ATTACK, obj) )
	return notify_fail( "�M" + obj->name() + "�԰��H\n"); 

    if( obj==me ) return notify_fail("�A��������ۤv�C\n");

    if( userp(obj) && (object)obj->query_temp("pending/fight")!=me ) {
	message_vision("\n$N���$n���D�R" 
	    + me->rank("self") + me->name() + "�A��гo��"
	    + obj->rank("respectful") + "�����ۡT\n\n", me, obj);

	if( objectp(old_target = me->query_temp("pending/fight"))
	&&  obj != old_target
	&&  environment(old_target)==environment(me) )
	    message_vision("\n$N�V$n�ꮱ�����A���D�G"
		+ me->rank("self") + "���A��бСC\n", me, old_target);
	me->set_temp("pending/fight", obj);

	tell_object(obj, YEL "�p�G�A�@�N�M���i���աA�ЧA�]��" + me->name() + "("+(string)me->query("id")+")"+ "�U�@�� fight ���O�C\n" NOR);
	write(YEL "�ѩ���O�Ѫ��a����H���A�A���������P�N�~��i���աC\n" NOR);
	return 1;
    }

    if( obj->query("civilized") ) {
	if( me->is_fighting() )
	    message_vision( "\n$N���$n���D�G�@�ֻ�гo��"
		+ obj->rank("respectful") + "�����ۡT\n\n", me, obj);
	else
	    message_vision( "\n$N���$n���D�R" 
		+ me->rank("self") + me->name() + "�A��гo��"
		+ obj->rank("respectful") + "�����ۡT\n\n", me, obj);

	if( obj->query_temp("pending/fight")==me ) {
	    obj->start_busy(1);
//	delete else, �����賣busy�ӫD���Ufight���O���Hbusy only -dragoon
//	else 
	    me->start_busy(1);
	}

	if( !userp(obj) && !obj->accept_fight(me) ) {
	    write("�ݰ_��" + obj->name() + "�ä��Q��A���q�C\n");
	    return 1;
	}

	me->fight_ob(obj);
	obj->fight_ob(me);
    } else {
	message_vision("\n$N�j�ܤ@�n�A�}�l��$n�o�ʧ����T\n\n", me, obj);
	me->fight_ob(obj);
	obj->kill_ob(me);
    }

    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : fight <�H��>
 
�o�ӫ��O���A�V�@�ӤH���u�Q�Сv�Ϊ̬O�u���R�Z���v�M�o�اΦ����԰��º�O
�I�쬰��M�]���u�|������O�M���|�u�����ˡM���O�ä��O�Ҧ���  NPC �����w
���[�M�]�����\\�h���p�A����Z�n�D�|�Q�ڵ��C
 
��L�������O: kill

PS. �p�G��褣�@�N�����A���D�ԡM�A���M�i�H�w��� kill ���O�}�l�԰��M��
    �� fight �� kill ���Ϥ��Ь� 'help combat'.
HELP
    );
    return 1;
}
 
