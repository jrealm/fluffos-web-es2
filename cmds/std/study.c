/*  study.c

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

int main(object me, string arg)
{
    object ob;

    if( me->is_busy() ) return notify_fail("�A������ halt ����b�����ơI\n");

    if( !arg || arg=="" ) return notify_fail("�A�n��Ū����H\n");

    ob = present(arg, me);
    if( !ob ) ob = present(arg, environment(me));
    if( !ob ) return notify_fail("�o�̨S���o�˪F�� ...�C\n");

    return ob->study_ob(me);
}

int help()
{
    write(@TEXT
���O�榡�Gstudy <���~>

�o�ӫ��O���A���H����Ū�@�Ǯ��y�Τ���������~�C

��Ū���L�{�O�۷�Ӯɶ��κ믫���A�ӥB�H�۫��򪺬�Ū�A�|�W�[�H����o��
���ʪ��u�h�ҡv(fatigue)�A�ӥB�o�ǯh�ҬO�߲z�W���A�u���H�ۮɶ��ӭ��C�C
TEXT
    );
    return 1;
}
