// refresh_pill.c

inherit COMBINED_ITEM;

void create()
{
	set_name("����T��Y", ({"refresh pill", "pill"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
"����T��Y���X����, �s��, �sŽ, ����ԤΨd���ƺ��ħ�����s\n"
"�Ӧ��O�@�ؤ�a���Ī��`�١A���ߺ뤧���ġC\n");
		set("base_unit", "��");
		set("base_value", 1000);
		set("base_weight", 5);
		set("mixture_value", 200);
		set("produce_param", ([
			"min_heat_power" : 110,
			"max_heat_power" : 170,
			"min_heat" : 400,
			"max_heat" : 428,
		]));
		set("requirement", ([
			"literate" : 15,
			"alchemy-medication" : 50,
		]));
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 20)
		return notify_fail("�A���{�l�w�g���o�s�o���ĤY�]�]���U�h�F�C\n");
	message_vision("$N�]�U�@�ɪ���T��Y�C\n", me);
	me->consume_stat("water", 10);
	me->supplement_stat("food", 5);
	me->heal_stat("gin", 25 + random(7));
	me->supplement_stat("gin", 20 + random(15));
	me->consume_stat("sen", 8);
	add_amount(-1);

	return 1;
}
