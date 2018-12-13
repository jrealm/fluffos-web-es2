// wagon.c

inherit CONTAINER_ITEM;

void create()
{
	set_name("笲砯苆ó", ({ "wagon" }));
	set_max_encumbrance(1000000);
	set("no_get", 1);
	set("unit", "进");
	set("long", "进笲砯近苆ó氨硂柑单帝更砯(load)\n");
	set("inside_long",
		"瞷タГ进笲砯ノ近苆ó\n");
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
		return notify_fail("刚刚: load wagon with 狥﹁ ┪ load 狥﹁ into wagon.\n");

	ob = present(arg, this_player());
	if( !ob ) return notify_fail("ō⊿Τ硂ン狥﹁, 或笲ó\n");
	if( environment(this_player())==this_player() )
		return notify_fail("ゲ斗ó\n");

	message_vision("$Nр$n杆笲砯苆ó\n", this_player(), ob);
	ob->move(this_object());
	tell_object(this_player(), "㊣  ㊣.. 仓翅\n");
	this_player()->consume_stat("kee",5);
	this_player()->add_temp("wage_deserved", ob->query("wage"));

	if( sizeof(all_inventory()) >= 20 ) {
		write("话苆óóひ聾喘话帝苆ó癳砯\n");
		destruct(this_object());
	}

	return 1;
}

// To prevent player from getting things in wagon.
int hold_object(object ob)
{
	notify_fail("ぐ或\n");
	return 1;
}
