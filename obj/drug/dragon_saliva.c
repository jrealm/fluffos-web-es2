// dragon_saliva.c

inherit COMBINED_ITEM;

void create()
{
	set_name("�s�C��", ({"dragon-saliva herb", "dragon-saliva", "herb"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"�s�C��O�@�ج۷�W�Q�������ġM�@��H�O���ӶR�o�_�o���ħ����M\n"
			"�s�C��g�`�Q��h�̥Ω�һs�@�ǬöQ�����ġM���O�����A���o�د�\n"
			"�Ĥ]���ǳ\\�����ˮĪG�M�u���L���Ǯ��O�}�F�C\n");
		set("base_unit", "��");
		set("base_value", 5000);
		set("base_weight", 7);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 10 )
		return notify_fail("�A���{�l�w�g���o����F��]�]���U�h�F�C\n");
	message_vision("$N���X�@���s�C���J�f���Z�F�Z�]�F�U�h�C\n", me);
	me->consume_stat("water", 10);
	me->supplement_stat("food", 10);
	me->consume_stat("sen", 3);
	me->heal_stat("kee", 30);
	add_amount(-1);

	return 1;
}
