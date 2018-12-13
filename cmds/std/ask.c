/*  ask.c

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

int help();

int main(object me, string arg)
{
    string targ, key;
    object target;

    if( !arg || arg=="" ) return notify_fail("�ݤ���H\n");

    if( sscanf(arg, "%s about %s", targ, key)==2 ) {
        target = present(targ, environment(me));
        if( !target || !target->is_character() )
            return notify_fail("�o�̨S���o�ӤH�C\n");
                // add by dragoon
                if( objectp(target) && target->query("no_fight") )
                        return notify_fail("����??\n");
        message_vision("$N�V$n��ť�����u" + key + "�v�������C\n", me, target);
        target->accept_inquiry(me, key);
        return 1;
    }
    else if( sscanf(arg, "%s for %s", targ, key)==2 )
    {
	target = present(targ, environment(me));
	if( !target || !target->is_character() )
	    return notify_fail("�o�̨S���o�ӤH�C\n");

	// add by dragoon
	if( objectp(target) && target->query("no_fight") )
	    return notify_fail("����??\n");

	switch(key) {
	case "help":
	    message_vision("$N���$n�j�s�G" + target->rank("respectful")
		+ "�ϩR�I\n", me, target);
            break;
	case "peace":
            if( !target->is_fighting(me) ) {
		write(target->name() + "�M�A�èS�������C\n");
		return 1;
            }
            message_vision("$N�V$n����@���A���D�G�o��"
		+ target->rank("respectful")
		+ "�Z�����j�A�b�U�تA�o��A���p�ƼĬ��ͦp��H\n", me, target);
            break;
	case "mercy":
            if( target->is_killing(me) )
                message_vision("$N�V$n�������ˡA�s�D�D�G" + target->rank("respectful")
                    + "�ǩR�I�p���U���A�]�����F�I\n", me, target);
            break;
	default:
	}
	target->accept_negotiation(me, key);
	return 1;
    }
    else
	return notify_fail("�Х� help ask �Ѧһ����C\n");
}

int help()
{
    write(@TEXT
���O�榡�Gask <�Y�H> about <����r>
          ask <�Y�H> for <��A�ؼ�>

�o�ӫ��O���A�M npc �i��@��²�檺���ʡA�βĤ@�خ榡���ɭԪ�ܦV npc ��ť
�����Y����r�������A�ĤG�خ榡�h�O�M npc �i���A�A�ثe�j�h�� npc ����F
�Ѫ���A�ؼЦ��G

help     �V���D�U�C
peace    �V��A�����몺�H�n�D�M�ѡC
mercy    �V���b�����A���ĤH�D�ǡC

TEXT
    );
    return 1;
}
