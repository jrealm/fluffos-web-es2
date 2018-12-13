// whisper.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string dest, msg;
	object ob;

	if( me->is_fighting() )
		return notify_fail("�A���b�԰����T\n");

	if( !arg || sscanf(arg, "%s %s", dest, msg)!=2 )
		return notify_fail("�A�n��֦ջy�Ǥ���S\n");

	ob = present(dest, environment(me));
	if( !ob || !ob->is_character() )
		return notify_fail("�A�n��֦ջy�S\n");

	if( ob->is_fighting() )
		return notify_fail( ob->name() + "���b�԰����T\n");

	write( GRN "�A�b" + ob->name() + "�����䮨�n���D�R" + msg + "\n" NOR);
	tell_room( environment(me), me->name() + "�b" + ob->name()
		+ "����p�n�a���F�ǸܡC\n", ({ me, ob }) );
	if( !userp(ob) ) ob->relay_whisper(me, msg);
	else
		tell_object( ob, GRN + me->name() + "�b�A�����䮨�n���D�R" + msg + "\n" NOR);
	return 1;
}

int help(object me)
{
	write( @TEXT
���O�榡�Rwhisper <�Y�H> <�T��>

�o�ӫ��O�i�H�ΨөM�P�@�ж������H�ջy�M�]�A NPC �b���C
TEXT
	);
	return 1;
}
