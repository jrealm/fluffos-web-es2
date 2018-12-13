// say.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object *ob;
	if (!arg) return notify_fail("�A�n������S\n");

	write("�A���D�R" + HIG + arg + "\n" NOR);
	message("sound", me->name() + "���D�R" + HIG + arg + "\n" NOR,
		environment(me), me);

	// The mudlib interface of say
	ob = all_inventory(environment(me)) - ({ me });
	ob->relay_say(me, arg);

	return 1;
}

int help (object me)
{
	write(@HELP
���O�榡: say <�T��>
 
���ܡM�Ҧ���A�b�P�@�өж����H���|ť��A�����ܡC
 
��: �����O�i�� ' ���N.
 
HELP
	);
	return 1;
}
