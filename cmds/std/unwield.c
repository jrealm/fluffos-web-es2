// unwield.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string equipped, str;

	if( !arg ) {
		mapping weapons;
		string skill;

		if( mapp(weapons = me->query_temp("weapon")) && sizeof(weapons) ) {
			foreach(skill, ob in weapons) ob->unequip();
			write("Ok.\n");
			return 1;
		} else
			return notify_fail("�A�{�b�èS���˳ƥ���Z���C\n");
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("�A���W�S���o�˪F��C\n");

	if( !stringp(equipped = ob->query("equipped"))
	||	!sscanf(equipped, "weapon/%*s") )
		return notify_fail("�A�èS���˳Ƴo�˪F��@���Z���C\n");

	if( ob->unequip() ) {
		if( !stringp(str = ob->query("unwield_msg")) )
			str = "$N��U�⤤��$n�C\n";
		message_vision(str, me, ob);
		return 1;
	} else
		return 0;
}

int help(object me)
{
  write(@HELP
���O�榡 : unwield <���~�W>
 
�o�ӫ��O���A��U�⤤���Z���C
 
HELP
    );
    return 1;
}
 
