// shout.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( !wizardp(me) )
		return notify_fail("�ثe�Ȥ��}�񪱮a shout�C\n");
	if (!arg) return notify_fail("�A�Q�n�j�s����?\n");
	shout( me->name() + "�a�n���S�R" + HIY + arg + NOR + "\n");
	write("�A�a�n���S�R" + HIY + arg + NOR + "\n");
	return 1;
}
int help(object me)
{
  write(@HELP
���O�榡 : shout <�T��>
 
�o�ӫ��O���A�N <�T��> �ǰe�X�h, �Ҧ����b�u�W�������H���|ť���A���ܡC�ثe�u
���Ův�i�ΡC
 
see also : tune
HELP
    );
    return 1;
}
 
