/*  to.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

// inherit F_CLEAN_UP;
// Don't want this command be cleaned up while typing long string.

int main(object me, string arg)
{
    me->edit( (: call_other, __FILE__, "do_to", me, arg :) );
    return 1;
}

void do_to(object me, string arg, string str)
{
    seteuid(getuid());
    if(arg) me->force_me(arg + " " + str);
    else me->force_me(str);
}

int help(object me)
{
write(@HELP
���O�榡 : to <���O>

�i�H�@����X�h��H�W����r, <���O>�q�`�O��X�T�������O�p
say , tell , describe , chat , reple ........���C
�d�� : 
 to say
 �������}�� '.'�M������J�� '~q'�M�ϥΤ��ئC�s�边�� '~e'�C
 �w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
 �F�诫�бХD : �w���u���S��
 �ХD�j�ҤH�[�o�b������ : Elon
 �ХD�p�ѱC�[�N�������� : �ھЬX
 �j�̤l�[���V������ : ������R
 .

��X��ù��W�����G�h�O :

�A���D�R�F�诫�бХD : �w���u���S��
�ХD�j�ҤH�[�o�b������ : Elon
�ХD�p�ѱC�[�N�������� : �ھЬX
�j�̤l�[���V������ : ������R
HELP
    );
    return 1;
}

