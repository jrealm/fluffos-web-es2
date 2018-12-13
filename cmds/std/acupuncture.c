/*  acupuncture.c

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

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string cauterization, spl, trg;
    object target, weapon;
       
    weapon = me->query_temp("weapon/needle");

    if( me->query("life_form") == "ghost" )
        return notify_fail("�H���F�N�@�F�ʤF, �֥h�䫰���_���a!!\n");

    if(!weapon) return notify_fail("�A�����˳ưw�����~�i�ϥΰw�b���N�C\n");
        
    if( me->is_busy() )
        return notify_fail("�A�{�b�S���šT\n");

    if( !arg ) return notify_fail("���O�榡�Racupuncture <�b�N> [to <�ؼ�>]\n");
    if( sscanf(arg, "%s to %s", spl, trg)==2 ) {
        target = present(trg, environment(me));
        if( !target ) target = present(trg, me);
        if( !target ) return notify_fail("�o�̨S�� " + trg + "�C\n");
        // add by dragoon
        if( userp(target) && !interactive(target) )
            return notify_fail("�o�H�{�b���b�u�W�C\n");
    } else {
        spl = arg;
        target = 0;
    }

    spl = replace_string( spl, " ", "_");

    notify_fail("�A�Х��� enable ���O��ܧA�n�ϥΪ��b�N�t�C\n");
    if( stringp(cauterization = me->skill_mapped("cauterization")) ) {
        me->set_temp("pending/hidden", 0);
        return (int)SKILL_D(cauterization)->acupuncture_cauterization(me, 
                spl, target);
    } 
    return 0;
}

int help (object me)
{
    write(@HELP
���O�榡�Racupuncture <�b�N�W��> [to <��H>]
 
�ϥΨb�N�M�A���ݫ��w<�b�N�W��>�M<�I�b��H>�h�i���i�L�C
�b�A�ϥάY�@�Өb�N���e�M�A�������� enable ���O�ӫ��w�A
�n�ϥΪ��b�N�t, �ԲӪ��]�w�аѦ� help cauterization �C
 
HELP
    );
    return 1;
}
