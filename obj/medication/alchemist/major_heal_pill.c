// basic setup of major_heal_pill 
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name("�j�٤�", ({"major heal pill", "major", "pill" }));
	if( !clonep() ) {
		set("unit", "��");
		set("long", 
"�j�٤��O�@�ط����_���P��, ��j�j�����ĥi�H���A�Ϊ̪�\n"
"���~�˦b����¡�X, ���L�һs�j�٤��һݪ��ħ����F�p�٤�\n"
"�һݪ��X���ħ��~, �٥��ݧ�M����, �d�~�H�x���ƺبu��\n"
"���öQ�ħ��C�]��, �j�٤����F�N�ҧx���~, �ħ��������\n"
"�����Q�C\n");
		set("base_unit", "��");
		set("base_value", 10000);
		set("base_weight", 5);
		set("mixture_value", 6000);
		set("produce_param", ([
			"min_heat_power" : 460,
			"max_heat_power" : 500,
			"min_heat" : 9500,
			"max_heat" : 10500,
		]));
		set("requirement", ([
			"literate" : 45,
			"alchemy-medication" : 150,
		]));
	}
	set_amount(1);
	setup();
}
