// conjure.c

#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string magic, spl, trg;
	object target;
	

	if( me->is_busy() )
		return notify_fail("�A�{�b�S���šT\n");

	if( environment(me)->query("no_magic") )
		return notify_fail("�o�̤���I�i�k�N�C\n");

	if( !arg ) return notify_fail("���O�榡�Rconjure <�k�N> [on <�ؼ�>]\n");
	if( sscanf(arg, "%s on %s", spl, trg)==2 ) {
		target = present(trg, environment(me));
		if( !target ) target = present(trg, me);
		if( !target ) return notify_fail("�o�̨S�� " + trg + "�C\n");
	} else {
		spl = arg;
		target = 0;
	}

	spl = replace_string( spl, " ", "_");

	notify_fail("�A�Х��� enable ���O��ܧA�n�ϥΪ��k�N�t�C\n");
	if( stringp(magic = me->skill_mapped("magic")) )
		return (int)SKILL_D(magic)->conjure_magic(me, spl, target);
		
	return 0;
}

int help (object me)
{
        write(@HELP
���O�榡�Rconjure <�k�N�W��> [on <��H>]
 
�I�k�M�A���ݭn���w<�k�N�W��>�M<�I�G��H>�h�i���i�L�C
�b�A�ϥάY�@�Ӫk�N���e�M�A�������� enable ���O�ӫ��w
�A�n�ϥΪ��k�N�t�C�i�ϥΪ��k�N�t�Ѧ� help alchemy�C
 
HELP
        );
        return 1;
}
