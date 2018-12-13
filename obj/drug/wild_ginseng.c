// wild_ginseng.c

inherit COMBINED_ITEM;

void create()
{
	set_name("���s�x", ({"wild ginseng", "ginseng"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"���s�x�O�@�ؼs���H�����ɫ~�M��H����𯫳��ᦳ�U�q�M�ӥB\n"
			"�S��������㪺�Ƨ@�ΡM�q�`�@�������Ī��ħ��M���L�����]��\n"
			"�H�����A�ΡM���O�ĪG������ۡC\n");
		set("base_unit", "��");
		set("base_value", 1500);
		set("base_weight", 400);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 50 )
		return notify_fail("�A���{�l�w�g���o����F��]�]���U�h�F�C\n");
	message_vision("$N���X�@�賥�s�x��J�f���Z�F�Z�]�F�U�h�C\n", me);
	me->supplement_stat("food", 50);
	me->heal_stat("gin", 5);
	me->heal_stat("kee", 5);
	me->heal_stat("sen", 5);
	add_amount(-1);

	return 1;
}
