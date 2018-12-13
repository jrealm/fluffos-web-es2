// aquapill.c

inherit COMBINED_ITEM;

void create()
{
	set_name("���G��", ({"aquapill", "pill"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"���G���O�@�ؤ�a���Ī��`�١A�D�n���\\��O���ˡA���G��������\n"
			"�\\�Ĭ۷����A�ӥB�һݪ��ħ��ܮe���R��A���O�]���һs�L�{��\n"
			"���ݭn�޳N�A�ҥH�u���j���������E�~�R�o��C\n");
		set("base_unit", "��");
		set("base_value", 160);
		set("base_weight", 5);
		set("mixture_value", 50);
		set("produce_param", ([
			"min_heat_power" : 90,
			"max_heat_power" : 180,
			// change from 4200/4500 to 2700/3000 by dragoon
			"min_heat" : 420,
			"max_heat" : 450,
		]));
		// skill changed from 5 to 30 by dragoon
		set("requirement", ([
			"literate" : 10,
			"alchemy-medication" : 30,
		]));
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 20)
		return notify_fail("�A���{�l�w�g���o�s�o���ĤY�]�]���U�h�F�C\n");
	message_vision("$N�]�U�@�ɪ��G���C\n", me);
	me->consume_stat("water", 10);
	// changed from 15 to 5 by dragoon
	me->supplement_stat("food", 5);
	me->damage_stat("gin", 3);
	me->consume_stat("gin", 5);
	me->heal_stat("kee", 25);
	me->supplement_stat("kee", 25);
	add_amount(-1);

	return 1;
}
