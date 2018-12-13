// wear.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);

int main(object me, string arg)
{
	object ob, *inv;
	int i, count;


	if( me->is_busy() )	return notify_fail("�A�{�b�S���šT\n");

	if( !arg ) return notify_fail("�A�n��������S\n");

	if(arg=="all") {
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) {
			if( inv[i]->query("equipped") ) continue;
			if(do_wear(me, inv[i]) ) count ++;
		}
		write("Ok.\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("�A���W�S���o�˪F��C\n");

	if( ob->query("equipped") )
		return notify_fail("�A�w�g�˳ƵۤF�C\n");

	return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
	string str;

	if( ob->query("female_only")
	&&	(string)me->query("gender") != "�k��" )
		return notify_fail("�o�O�k�H����m�M�A�@�Ӥj�k�H�]�Q��M�ۤ]���ۡS\n");

	if( ob->wear() ) {
		if( !stringp(str = ob->query("wear_msg")) ) {
			// Get equipped info "armor/xxxxx"
			switch( ob->query("equipped")[6..<1] ) {
				case "cloth":
				case "armor":
				case "leg_eq":
				case "feet_eq":
					str = YEL "$N��W�@" + ob->query("unit") + "$n�C\n" NOR;
					break;
				case "head_eq":
				case "neck_eq":
				case "finger_eq":
				case "hand_eq":
					str = YEL "$N���W�@" + ob->query("unit") + "$n�C\n" NOR;
					break;
				case "waist_eq":
					str = YEL "$N�N�@" + ob->query("unit") + "$nô�b�y���C\n" NOR;
					break;
				default:
					str = YEL "$N�˳�$n�C\n" NOR;
			}
		}
		message_vision(str, me, ob);
		return 1;
	} else
		return 0;
}

int help(object me)
{
	write(@HELP
���O�榡�Rwear <�˳ƦW��>
 
�o�ӫ��O���A�˳ƬY�󨾨�C
 
HELP
    );
    return 1;
}
