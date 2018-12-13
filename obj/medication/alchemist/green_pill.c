// green_pill.c

inherit COMBINED_ITEM;

void do_cure_poison(object me);

void create()
{
	set_name("���F�M�r��", ({"green pill", "pill"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
"���F�M�r���O�@�زM���Ѭr������,�Ѷ���, �t����, ��q, ���ƥ�\n"
"���h���ħ���s�Ӧ�, ���۷��M�������Ī����@�C\n");
		set("base_unit", "��");
		set("base_value", 650);
		set("base_weight", 5);
		set("mixture_value", 100);
		set("produce_param", ([
			"min_heat_power" : 85,
			"max_heat_power" : 230,
			"min_heat" : 150,
			"max_heat" : 200,
		]));
		set("cure_poison", ([
		"��" : -1, "��" : -1, "��" : -1, "�g" : -1, "��" : -1,
		"damage" :   -1,
		]));
		set("requirement", ([
			"literate" : 5,
			"alchemy-medication" : 15,
		]));
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 20)
		return notify_fail("�A���{�l�w�g���o�s�o���ĤY�]�]���U�h�F�C\n");
	message_vision("$N�]�U�@�ɥ��F�M�r���C\n", me);
	me->consume_stat("water", 10);
	me->supplement_stat("food", 5);
	me->supplement_stat("sen", 2);
	do_cure_poison( me );	
	add_amount(-1);
	return 1;
}

void do_cure_poison(object me)
{
        mixed cnd_data;
        object ob;
        ob=this_object();
        cnd_data = me->query_condition("poison");

	if ( me->query_condition("poison") == 0 ) {
		tell_object(me, "�A�]�U�o���ĤY, ���O�o�S����Pı�C\n");
	} else {
		if ( ob->query("cure_poison/damage") )
		cnd_data["damage"] = cnd_data["damage"] + 
			ob->query("cure_poison/damage");
                if (cnd_data["damage"] <= 0 ){
                        me->delete_condition("poison");
	                tell_object(me, 
			"�A�]�U�o���ĤY��, ���骺���A�w�g���������F�C\n");
                        return;
                }
                else {
	                tell_object(me, 
			"�A�]�U�o���ĤY��, ���骺���A�P���G�y�L��F�C\n");
                }
                return;
        }
}
