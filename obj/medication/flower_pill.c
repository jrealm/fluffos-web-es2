// flower_pill.c

inherit COMBINED_ITEM;

void create()
{
	set_name("����Y", ({"flower pill", "pill"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"����Y�O�@�تv�����m���`������A���L�s�y�۷�O�ɳ·СA�h\n"
			"�b�n��j�@�I������~�R�o��C\n");
		set("base_unit", "��");
		set("base_value", 150);
		set("base_weight", 5);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 5 )
		return notify_fail("�A���{�l�w�g���o�s�o���ĤY�]�]���U�h�F�C\n");
	message_vision("$N�]�U�@�ɷt���⪺�ĤY�C\n", me);
	me->consume_stat("water", 30);
	me->supplement_stat("food", 5);

	// TODO: implement medical function.

	add_amount(-1);

	return 1;
}
