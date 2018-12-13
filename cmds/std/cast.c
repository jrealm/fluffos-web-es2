/*  cast - the spell-casting command

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string spells, spl, trg;
    object target;
        
    if( me->query("life_form") == "ghost" )
        return notify_fail("�H���F�N�@�F�ʤF, �֥h�䫰���_���a!!\n");

    if( me->is_busy() ) return notify_fail("�A�{�b�S���šI\n");

    if( !arg ) return notify_fail("���O�榡�Rcast <�G��W��> [on <�I�G��H>]\n");

    if( sscanf(arg, "%s on %s", spl, trg)==2 ) {
	target = present(trg, environment(me));
	if( !target ) target = present(trg, me);
	if( !target ) return notify_fail("�o�̨S�� " + trg + "�C\n");

	// add by dragoon, modified by annihilator
	if( userp(target) && !interactive(target) ) {
	     write("�A������_�u�����H�I�k�C\n");
	     return 1;
	}
    } else {
	spl = arg;
	target = 0;
    }

    if( environment(me)->query("no_magic")
    && !me->is_fighting(target)
    && !target->query("unprotect_mark") ) {
	    tell_object(me, "�o�̤���԰��C\n");
	    return 1;
    }

    spl = replace_string( spl, " ", "_");

    notify_fail("�A�Х��� enable ���O��ܧA�n�ϥΪ��G��t�C\n");
    if( stringp(spells = me->skill_mapped("spells")) )
	return (int)SKILL_D(spells)->cast_spell(me, spl, target);

    return 0;
}

int help (object me)
{
    write(@HELP
���O�榡�Rcast <�G��W��> [on <�I�G��H>]

�I�i�k�N�A�A���ݭn���w<�G��W��>�A<�I�G��H>�Y�w�B��Ԫ����A�h�i�ٲ��C

�b�A�ϥάY�@�өG�大�e�A�A�������� enable ���O�ӫ��w�A�n�ϥΪ��G��t�A��
�ϥΪ��өG��t�����G��A�G��W�٥i�Ѧ� help taoism�C

�j�h�ƪ��k�N�q�A�}�l�u�w�G��A�짹���k�N�|�ݭn�@�q�ɶ��C�o�q�ɶ��I�k�̷|
�L�k���ʩΧ����C
HELP
    );
    return 1;
}
