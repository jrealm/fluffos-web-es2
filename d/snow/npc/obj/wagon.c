// wagon.c

inherit CONTAINER_ITEM;

void create()
{
	set_name("�B�f�j��", ({ "wagon" }));
	set_max_encumbrance(1000000);
	set("no_get", 1);
	set("unit", "��");
	set("long", "�@���B�f���|���j���M���b�o�̵��۸��f(load)�C\n");
	set("inside_long",
		"�A�{�b�����b�@���B�f�Ϊ��|���j���W�C\n");
	set("transparent", 1);
	setup();
}

void init()
{
	add_action("do_load", "load");
}

int do_load(string arg)
{
	object ob;

	if( 	!arg 
	||	!sscanf(arg, "wagon with %s", arg)
	&&	!sscanf(arg, "%s into wagon", arg) )
		return notify_fail("�A�i�ո�: load wagon with �F�� �� load �F�� into wagon.\n");

	ob = present(arg, this_player());
	if( !ob ) return notify_fail("�A���W�S���o��F��, ���B�W���S\n");
	if( environment(this_player())==this_player() )
		return notify_fail("�A�������U���C\n");

	message_vision("$N��$n�ˤW�B�f�j���C\n", this_player(), ob);
	ob->move(this_object());
	tell_object(this_player(), "�I  �I.. �n�ֳ�C\n");
	this_player()->consume_stat("kee",5);
	this_player()->add_temp("wage_deserved", ob->query("wage"));

	if( sizeof(all_inventory()) >= 20 ) {
		write("���j���������@�l�@���M�����j���e�f�h�F�C\n");
		destruct(this_object());
	}

	return 1;
}

// To prevent player from getting things in wagon.
int hold_object(object ob)
{
	notify_fail("����S\n");
	return 1;
}
