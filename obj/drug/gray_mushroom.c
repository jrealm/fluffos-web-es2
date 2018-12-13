// gray_mushroom.c

inherit COMBINED_ITEM;

void create()
{
	set_name("�ǯ�ۣ", ({ "gray mushroom", "mushroom"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"�ǯ�ۣ�O�@�إͪ��b���㪺����h�a�A�i�H�ΨӪv���M�˪�\n"
			"�Ӥp��ۣ�A�q�`���ҥH��Ψӻs�y�~�Ū��I�ġA���L�����A\n"
			"�Τ]���ֳ\\�v�����˪��\\�ġC\n");
		set("base_unit", "��");
		set("base_value", 90);
		set("base_weight", 30);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 20 )
		return notify_fail("�A���{�l�w�g���o����F��]�]���U�h�F�C\n");
	message_vision("$N���X�@��ǯ�ۣ��J�L�̡A�Z�F�Z�]�F�U�h�C\n", me);
	me->supplement_stat("food", 20);
	me->consume_stat("water", 20);
	me->heat_stat("gin", 3);
	me->heat_stat("kee", 3);
	add_amount(-1);

	return 1;
}
