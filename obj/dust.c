// dust.c

inherit COMBINED_ITEM;

void create()
{
	set_name("�ƫͯ�", ({"dust"}));
	set("long",
		"�o�O�@�]�Ψӷ��ͷ��񪺤ƫͯ��M�u�n�x�@�B�I�N�i�H\n"
		"�ƥh(dissolve)�@�����T\n");
	set("unit", "�]");
	set("base_unit", "��");
	set("base_weight", 1);
	set_amount(1);
}

void init()
{
	if( this_player()==environment() )
		add_action("do_dissolve", "dissolve");
}

int do_dissolve(string arg)
{
	object ob;

	if( !arg ) return notify_fail("�A�n�Τƫͯ����Ѥ���F��S\n");
	if( !objectp(ob = present(arg, environment(this_player()))) )
		return notify_fail("�o�̨S���o�˪F��C\n");
	if( living(ob) || !ob->id("corpse") )
		return notify_fail("�ƫͯ��u��Ψӷ��ѫ���C\n");
	message_vision(
		"$N�Ϋ��ҬD�F�@�I�ƫͯ��b$n�W�M�uť���@�}�u���v�n�T�a��\n"
		"�@�ѥi�Ȫ��c��M$n�u�ѤU�@�y�����C\n", this_player(), ob);
	destruct(ob);
	add_amount(-1);
	return 1;
}

