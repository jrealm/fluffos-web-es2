// black_pill.c

inherit COMBINED_ITEM;

void create()
{
	set_name("�Q�ߤ�", ({"black pill", "pill"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"�Q�ߤ��O�@�إ����ܴ��M���Ĥ�M�Ψӫ�_�]�޽m�B�u�@�үӪ���O\n"
			"���������ĪG�M���I�O�Y�F�H��|�����H�H�Q��ı�M�B�e���f���C\n");
		set("base_unit", "��");
		set("base_value", 80);
		set("base_weight", 5);
		// �Ĥ誺����
		set("mixture_value", 30);
		// �һs�Ѽ�
		set("produce_param", ([
			"min_heat_power" : 80,
			"max_heat_power" : 250,
			//change from 1000/1500 to  100/150
			"min_heat" : 100,
			"max_heat" : 150,
		]));
		// �ۿ��Ĥ�һݳ̧ޯ�U��
		set("requirement", ([
			"literate" : 1,
		]));
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 5 )
		return notify_fail("�A���{�l�w�g���o�s�o���ĤY�]�]���U�h�F�C\n");
	message_vision("$N�]�U�@�ɶ¶ª��ĤY�C\n", me);
	me->consume_stat("water", 30);
	me->supplement_stat("food", 5);
	me->damage_stat("sen", 1);
	me->consume_stat("sen", 4);
	me->supplement_stat("gin", 15);
	me->supplement_stat("kee", 15);
	add_amount(-1);

	return 1;
}
