// es2_bottle.c

inherit ITEM;

void create()
{
	object water;

	set_name("��o�����~", ({ "bottle" }));
	set_max_encumbrance(180000);
	set("long", "�@�ӳz���S�ܵ��R����o�����~�A�o�O workshop �������~�C\n");
	set("liquid_container", 1);
	set("value", 0);
	set("no_drop",1);
	setup();
	if( clonep() ) {
		water = new("/obj/water");
	    water->set_volume(1000);
		water->move(this_object());
	}
}

int accept_object(object me, object ob) { return 1; }
int query_autoload() { return 1; }
