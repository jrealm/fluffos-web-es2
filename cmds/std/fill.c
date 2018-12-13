// fill.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob, from_ob, ob_liq ,from_liq, new_liq;
	string source;
	int new_volume, empty_flag = 0;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("�Х�����A���b�����ơC\n");

	if( !me->query_stat_maximum("kee") )
		return notify_fail("�A�S������M�L�k���o�Ӱʧ@�C\n");

	notify_fail("���O�榡�Gfill <�e��> with <�G��>|<�e��>\n");
	if( !arg || arg=="" ) return 0;

	if( sscanf(arg, "%s with %s", arg, source)!=2 )	return 0;

	if( arg == source )
		return notify_fail("�A�o�˧@�O�椣�q���T\n");

	// find ob
	ob = present(arg, me);
	if( !ob ) ob = present(arg, environment(me));
	if( !ob ) return notify_fail("�o�̨S�� " + arg + " �o�˪F��C\n");
	if( !ob->query("liquid_container") )
		return notify_fail( ob->name() + "�ä��O�ˤ����e���C\n");
	// return fail if ob_liq exist 
	foreach(ob_liq in all_inventory(ob))
		return notify_fail(
		"�Ч�" + ob->name() + "�ت�" + ob_liq->name() + "�ܰ��b�A�ӸˡC\n");

	// find from_ob
	from_ob = present(source, me);
	if( !from_ob ) from_ob = present(source, environment(me));
	if( !from_ob ) {
		// resource of environment, set("resource/<source>") in room
		if( environment(me)->query("resource/" + source) ) {
			if( !(new_liq = new("/obj/" + source)) )
				return notify_fail("�o���� " + source + " ���I���D, �ЦV�Ův�����C\n");
//  marked by dragoon since still found bug and change to return fail if
//  found ob_liq
/*
			foreach(ob_liq in all_inventory(ob))	// dest liq of ob, keep solid
				if( function_exists("query_volume", ob_liq) ) {
					destruct(ob_liq);
					empty_flag++;
				}
			new_volume = to_int( ob->query_max_encumbrance() - ob->query_encumbrance()/new_liq->query("density") );
			new_liq->set_volume(new_volume);

			if( !ob->accept_object(me, new_liq) )
				return notify_fail(ob->name() + " ����ˤJ" + new_liq->name() + "�C\n");

			new_liq->move(ob);

			message_vision("$N�N" + ob->name(), me);
			if(empty_flag)
				tell_room(environment(me), "�����G��˪�, �åB");
			tell_room(environment(me), "�˺��F����" + new_liq->name() + "�C\n");

			return 1;
*/
		}
		return notify_fail("�A���W, �a�W, �γo���񳣨S��칳 " + source + " ���˪��G��ήe���C\n");
	}

	// check from_ob and from_liq
	if( !from_ob->query("liquid_container") )
		return notify_fail( from_ob->name() + "�ä��O�ˤ����e���C\n");
	if( from_ob->hold_object() )
		return notify_fail( from_ob->name() + "�{�b��򳬵ۡC\n");
	foreach(from_liq in all_inventory(from_ob))
		if( function_exists("query_volume", from_liq) ) break;
	if( !from_liq )
		return notify_fail(from_ob->name() + "�̨S���@�w���C\n");

	// check ob and ob_liq
	if( !ob->accept_object(me, from_liq) ) return 0;

	// set new_liq, move to ob
	new_liq = clone_object(base_name(from_liq));
	new_volume = to_int( (ob->query_max_encumbrance() -
	    ob->query_encumbrance()) / new_liq->query("density") );
	if( new_volume > from_liq->query_volume() )
		new_volume = from_liq->query_volume();
	if( new_volume > 0 ) {
		new_liq->set_volume(new_volume);
		new_liq->move(ob);
		from_liq->add_volume(-new_volume);
	}
	message_vision("$N�N" + from_ob->name() + "����" + new_liq->name() +
		"�ˤJ" + ob->name() + "���C\n", me );
	return 1;
}

int help(object me)
{
write(@TEXT
���O�榡�Gfill <�e���@> with <�e���G>|<�G��>

�N�e���G�����G��ˤJ�e���@���C���ثe����⤣�P���G��V�b�@�_�C

���Ǧa��p����B�����������B�A�Ϊ̩ж��ԭz������G�鷽���a��A�A�]�i�H��
��fill <�e��> with <�G�鷽> (�p�Gwater�Btea�Boil�B ... �аѦҧA�o�{������)
�Ҧp:
fill skin with pot
fill bottle with water
TEXT
	);
	return 1;
}
