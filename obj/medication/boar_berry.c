// boar_berry.c

inherit COMBINED_ITEM;

void create()
{
	set_name("�s�ުG", ({"boar berry", "berry"}));
	if( !clonep() ) {
		set("unit", "��");
		set("long",
			"�s�ުG�O�@�إͪ��b�`�s���M�ר�O���ު��_�ު��񪺤@�طt����\n"
			"�����M���Ǥs�ުG�O���r���M���ǫh�O�L�r���M�L�r���s�ުG�i�H\n"
			"�Ψӷ�Ѭr�����ħ��M�����A�Ϋh�i�H�����M���L��ĵ�i�A�M���D\n"
			"��....�Ӧn�C\n");
		set("base_unit", "��");
        set("base_value", 2000);
		set("base_weight", 70);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 20 )
		return notify_fail("�A���{�l�w�g���o����F��]�]���U�h�F�C\n");
	message_vision("$N�Y�U�@���o�۴c�䪺�s�ުG ... �ѰڡM$P���M�]�o�U�h .... �C\n", me);
    me->supplement_stat("food", 10);
	me->consume_stat("water", 20);
    me->heal_stat("sen", 15);
    me->supplement_stat("sen", 10);
	add_amount(-1);

	return 1;
}
