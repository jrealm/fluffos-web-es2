// map.c

inherit ITEM;

void create()
{
	set_name("�a��", ({ "map" }));
	set_weight(10);
	if( !clonep() ) {
		set("unit", "�i");
		set("value", 300);
		set("long", "�@�i�i�H��ܧA����a�Ϊ��a�ϡA�� read map �ϥΡC\n");
	}
	setup();
}

void init()
{
	add_action("do_read", "read");
}

int do_read(string arg)
{
	mapping m;
	string mstr;

	if( !id(arg) ) return 0;
	if( !mapp(m = environment(this_player())->query("virtual_map")) )
		return notify_fail("�a�ϥu���b�j�ϰ줤�~���ġC\n");
	mstr = "�z�w�w�w�w�w�w�w�w�w�{\n";
	mstr += repeat_string("�x                  �x\n", 9);
	mstr += "�|�w�w�w�w�w�w�w�w�w�}\n";
	write(mstr);
	return 1;
}
