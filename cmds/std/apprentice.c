// apprentice.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if( !arg ) return notify_fail("�A�n���֬��v�S\n");

	ob = present(arg, environment(me));
	if( !ob || !ob->is_character() ) return notify_fail("�o�̨S���o�ӤH�C\n");
	// add by dragoon
        if( objectp(ob) && ob->query("no_fight") ) 
		return notify_fail("����??\n");

	if( ob==me ) return notify_fail("���A�ۤv���v�S\n");

	if( me->is_apprentice_of(ob) )
		return notify_fail("�A�w�g�O" + ob->name() + "���̤l�F�C\n");

	if( !living(ob)	)
		return notify_fail(ob->name() + "�{�b�S����k�^���A�C\n");

	notify_fail(ob->name() + "���G�S�����A���{������C\n");
	if( !ob->accept_apprentice(me) )
		return 0;

	message_vision(CYN "\n$N���U�Ӯ����q�q�a�V$n�W�F�|���T�Y�M�s�D�R�v���T\n\n" NOR,
		me, ob);
	ob->init_apprentice(me);

	return 1;
}

int help(object me)
{
	write(@Help
���O�榡: apprentice <�Y�H>

���Y�H��v��, �p�G�Y�H�w�O�A(�p)�v��, �h�O�V�v���Цw�C
Help
	);
	return 1;
}
