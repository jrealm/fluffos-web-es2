// pot.c

inherit ITEM;

void create()
{
	object water;

	set_name("�j����", ({ "pot" }));
	set_max_encumbrance(180000);
	set("long", "�@�Ӹ˺��M�����j�����M�p�G�A�f���M�i�H����ӳ�(drink)�C\n");
	set("no_get", 1);
	set("liquid_container", 1);
	setup();
	if( clonep() ) {
		water = new("/obj/water");
		water->set_volume(100000);
		water->move(this_object());
	}
}

varargs int accept_object(object me, object ob)
{
	if( ob )
		if( !userp(ob) )
			return 1;
	else return notify_fail("�A����N���a���e���̭��C\n");
}

void reset()
{
	object water;
	if( water = present("water", this_object()) )
		water->set_volume(100000);
}

