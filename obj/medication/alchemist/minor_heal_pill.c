// minor_heal_pill.c

inherit COMBINED_ITEM;

void create()
{
	set_name("�p�٤�", ({"minor heal pill", "minor", "pill" }));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"�p�٤��O�@�ج۷��_���P���A�i�H���A�Ϊ̪��~�˦b����¡�X�A���y\n"
			"�ܻ��A�۹��@��u���_��𯫪����q���ġA�p�٤��ٯ����_����\n"
			"�Ҩ����l�ˡA���L�һs�p�٤��һݪ��ħ��ᬰ���Q�A�ӥB�N�Үɥ�����\n"
			"�j�q���E�@���l�A�]���ҶO����A�ܤ֦����E�|�c��o�ؤ��ġC\n");
		set("base_unit", "��");
		set("base_value", 6000);
		set("base_weight", 5);
		set("mixture_value", 250);
		set("produce_param", ([
			"min_heat_power" : 130,
			"max_heat_power" : 150,
			// change from 8000 to 800 by dragoon
			"min_heat" : 800,
			// change from 8200 to 820 by dragoon
			"max_heat" : 820,
		]));
		// skill changed from 30 to 60 by dragoon
		set("requirement", ([
			"literate" : 15,
			"alchemy-medication" : 60,
		]));
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if (me->query_stat_maximum("food") - me->query_stat("food") < 8)
		return notify_fail("�A���{�l�w�g���o�s�o���ĤY�]�]���U�h�F�C\n");
	message_vision("$N�]�U�@�ɤp�٤��C\n", me);
	me->consume_stat("water", 15);
	// changed from 20 to 5 by dragoon
	me->supplement_stat("food", 5);
	me->damage_stat("gin", 5);
	me->consume_stat("gin", 5);
	me->heal_stat("kee", 35);
	me->supplement_stat("kee", 60);
	me->supplement_stat("HP", 20);
	add_amount(-1);

	return 1;
}
