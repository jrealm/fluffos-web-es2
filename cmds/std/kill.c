/*  kill.c

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

inherit F_CLEAN_UP;

void do_kill(object, object);

int main(object me, string arg)
{
    object obj;
    string *killer, callname;

    if( me->query("life_form") == "ghost" )
	return notify_fail("�H���F�N�@�F�ʤF, �֥h�䫰���_���a!!\n");

    if( !arg ) return notify_fail("�A�Q���֡S\n");

    if( !(obj = present(arg, environment(me)))
    ||	!obj->is_character()
    ||	obj->is_corpse() )
	return notify_fail("�o�̨S���o�ӤH�C\n");

    // add by dragoon
    if( wizardp(obj) ) return notify_fail("����!!\n");

    if( environment(me)->query("no_fight") ) {
	if( !obj->query("unprotect_mark") ) {
	    tell_object(me, "�o�̤���԰��C\n");
	    return 1;
	}
    }

    // add by dragoon
    if( userp(obj) && !interactive(obj) ) 
        return notify_fail("�o�H�{�b���b�u�W�C\n");

    if( obj->query("no_fight") ) return notify_fail("����C\n");

    if( me->is_busy() ) return notify_fail("�A�Q�ĤH��o�⦣�}�� ...\n");

    if(obj==me) return notify_fail("�A����Q���ܡS\n");

    me->set_temp("pending/hidden", 0);      // be visible
        
    if( ! me->is_fighting(obj)
    ||	! me->is_killing(obj) ) {
	switch( random(3) )
	{
	case 0:
	    message_vision("\n$N���$n�ܹD�R�u" + obj->rank("rude")
		+ "�T���餣�O�A���N�O�ڬ��T�v\n\n", me, obj);
	    break;
	case 1:
	    message_vision("\n$N���$n�ܹD�R�u" + obj->rank("rude")
		+ "�A�ǩR�ӡI�v\n\n", me, obj);
	    break;
	case 2:
	    message_vision("\n$N���$n�ܹD�R�u" + obj->rank("rude")
		+ "�A���~�����ѴN�O�A���Ҥ�I�v\n\n", me, obj);
	    break;
	}
    }

    do_kill(me, obj);

    return 1;
}

void do_kill(object me, object obj)
{
    me->kill_ob(obj);

    if( obj->is_fighting(me) && obj->is_killing(me) ) return;

    if( userp(obj) )
    {
	/* �缾�a�� kill ���O */
	obj->fight_ob(me);
	tell_object(obj, HIR "�p�G�A�n�M" + me->name() 
	    + "�ʩR�۷i�A�ЧA�]��o�ӤH�U�@�� kill ���O�C\n" NOR);
    }
    else {
	/* �� NPC �� kill ���O */
	if( function_exists("accept_kill", obj)
	&&  ! obj->is_killing(me)
	&&  obj->accept_kill(me) ) {
	    return; }

	if( ! obj->is_killing(me) ) obj->kill_ob(me);
	else if( ! obj->is_fighting(me) ) obj->fight_ob(me);
    }
}

int help(object me)
{
  write(@HELP
���O�榡 : kill <�H��>
 
�o�ӫ��O���A�D�ʶ}�l�����@�ӤH���M�åB�|�ձ������Mkill �M fight �̤j��
���P�b������N�|�u�M��j�a�����M�]�N�O���M�|�u�����ˡC�ѩ� kill �u�ݳ��
���@�[���@�N�i�H���ߡM�]���A�����H�ϥ� kill ���O���|�}�l�԰��M�q�`�p�G
���O NPC ���ܡM�L�̤]�|�P�˹�A�ϥ� kill�C

���H��A�ϥ� kill ���O�ɷ|�X�{���⪺�r��ĵ�i�A�M���@�Ӫ��a�Ө��M�p�G
�A�S����@�W�ĤH�ϥιL kill ���O�M�N���|�N���u�����˩α���( �ϥΪk�N��
��ŧ���~)�C

��L�������O: fight

���� fight �� kill ���Ϥ��Ь� 'help combat'.
HELP
    );
    return 1;
}
 
