/*  exert.c

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
    int ratio;
    string f, dest;
    object target;

    if( !(f = me->skill_mapped("force")) )
        return notify_fail("�A�{�b�èS���ϥΥ��󤺥\\�C\n");
    if( f=="force" )
        return notify_fail("�A������ enable �@�ؤ��\\�C\n");

    if( !arg ) {
        ratio = me->query("force_ratio");
        if( !ratio ) ratio = 75;
        printf("�A�b�@�ԮɱN�ϥX%s��%s���\\�O�C\n",
            chinese_number(ratio/10), (ratio%10==0 ? "" : chinese_number(ratio%10)));
        return 1;
    }

    if( sscanf(arg, "%d", ratio)==1 ) {
        if( ratio < 10 || ratio > 100 )
            return notify_fail("�A�౱��d��O�b�@����Q���\\�O�����C\n");
        me->set("force_ratio", ratio);
        write("Ok.\n");
        return 1;
    }

    if( me->is_busy() )
        return notify_fail("�A�������� halt ����A���b�����ơT\n");

    if( sscanf(arg, "%s on %s", arg, dest)==2 ) {
        target = present(dest, environment(me));
//        if( !target || !target->is_target() )
//            return notify_fail("�o�̨S���o�ӤH�C\n");
// edit by ueiren .....cant find is_target()
	if( !target ) target = present( dest, me );
	if( !target ) return notify_fail("�o�̨S���o�ӤH�C\n");
    }
    notify_fail("�A�ҨϥΪ����\\�S���o�إ\\��C\n");
    return SKILL_D(me->skill_mapped("force"))->exert_function(me, arg, target);
}

int help(object me)
{
    write(@TEXT
���O�榡�Rexert [<�\��> [on <�ؼ�>]]
          exert <�\�O�ʤ���(10-100)>
          exert

�ϥΤ��\���Y�ǥ\��M�γ]�w�b�԰����n�ϥX�X���\�O�Mexert 100 ��ܧA�N�ϥX���O
�԰��M��A�ޯण�����ɭԧA��\�O������N������ব�o�ۦp�M�ϥX���O�԰��N�ϧA
�B�Τ��\���@�԰��ɪ������R���v�B�}�a�O�B�P���m�O�M���O�۹諸�O�𪺮��Ӥ]�۷�
�j�M������z���ĤH�ɧA�i�H��ܨϥΤ��B�����\�O�H�`����O�C

���[����ѼƮɷ|��ܧA�{�b���]�w�C

�ϥΤ��\�ޯ�ɩҥΪ��\���H�A�ǲߪ����\�Ӳ��M�q�`�A�i�H�� exert <���\�W��> ��
�׷Ҥ��\�M���L���ǯS���\���׷Ҥ�k�i��|�����P�C

TEXT
    );
    return 1;
}
