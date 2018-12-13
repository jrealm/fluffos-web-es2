// basic setup of major_heal_pill 
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIY"�j�٤�"NOR, ({"major heal pill", "major", "pill" }));
	if( !clonep() ) {
		set("unit", "��");
		set("long", 
"�j�٤��O�@�ط����_���P��, ��j�j�����ĥi�H���A�Ϊ̪�\n"
"���~�˦b����¡�X, ���L�һs�j�٤��һݪ��ħ����F�p�٤�\n"
"�һݪ��X���ħ��~, �٥��ݧ�M����, �d�~�H�x���ƺبu��\n"
"���öQ�ħ��C�]��, �j�٤����F�N�ҧx���~, �ħ��������\n"
"�����Q�C�o�����~��e�H�H��������, �D��s�L�{�����ԤQ\n"
"������x, ���ʤ���@�����~�p�٤��C\n");
		set("base_unit", "��");
		set("base_value", 10000);
		set("base_weight", 5);
		set("mixture_value", 6000);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if (me->query_stat_maximum("food") - me->query_stat("food") < 10)
		return notify_fail("�A���{�l�w�g���o�s�o���ĤY�]�]���U�h�F�C\n");
	message_vision("$N�]�U�@�ɤj�٤��C\n", me);
	me->consume_stat("water", 18);
	me->supplement_stat("food", 7);
	me->heal_stat("gin", 60);
	me->supplement_stat("gin", 80);
	me->heal_stat("kee", 150);
	me->supplement_stat("kee", 180);
	me->heal_stat("HP", 25);
	me->supplement_stat("HP", 40);
	add_amount(-1);

	return 1;
}
