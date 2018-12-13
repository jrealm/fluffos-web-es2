// cast.c

#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object weapon;
    string martial_skill, act, trg;
    object target;

    if( me->is_busy() )
        return notify_fail("�A�{�b�S���šT\n");
    
    if( environment(me)->query("no_fight") )
	return notify_fail("�o�̤���԰��C\n");

    if( !me->is_fighting())
	return notify_fail("�A�����b�԰����~��ϥε��ۡI\n");

    if( !arg ) return notify_fail("���O�榡�Rperform <�ޯ�:����> on <�ؼ�>\n");
    
    if( sscanf( arg, "%s:%s on %s", martial_skill, act, trg) != 3
    &&	sscanf( arg, "%s:%s", martial_skill, act) != 2 )
        return notify_fail("���O�榡�Rperform <�ޯ�.����> [on <�ؼ�>]\n");
    
    if( trg ) {
        target = present(trg, environment(me));
        if( !target ) return notify_fail("�A�n��֨ϥΩۦ��H\n");
        if( !living(target) ) return notify_fail("�A�i�H�����_�F�o�ө��g�������å�A���ݭn�ε��ۡC\n");
    }

    if( !me->query_temp("weapon/" + martial_skill ) 
        && (martial_skill != "unarmed") )
        return notify_fail("�A�����˳ƾA���Z���ӨϥX���ۡC\n");

        notify_fail("�A�Х��� enable ���O��ܧA�n�ϥΪ��ޯ�C\n");

    if( (martial_skill != me->skill_mapped( martial_skill ))
    &&	(me->skill_mapped(martial_skill) != 0))
        return SKILL_D(me->skill_mapped(martial_skill))->perform_action(me, act, target);

    return 0;

}

int help (object me)
{
    write(@HELP
���O�榡�Rperform <�ޯ�:����> [on <�I�۹�H>]

�b�԰����ϥΩҾǧޯ઺���ۨөM�I�۹�H��ԡA���ۥi�H�Ѧ�
�ӧO���ޯ�Ҵ��Ѫ�HELP�C

�Ҧp�G perform sword:snowblade on guard

�N�O���w�� enable ���C�k�� snowblade �o�ۨӹ� guard �I�i�C

�b�A�ϥάY�@�ӧޯ઺���ۤ��e�M�A�������� enable ���O�ӫ��w�A�n�ϥΪ��ޯ�C
 
HELP
    );
    return 1;
}
