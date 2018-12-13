// hockshop_storage.c

inherit ROOM;

void create()
{
	set("short", "�Y����Q���x�ë�");
	set("long", "�o�̬O�Y����Q���x�ëǡM�A���ӥX�{�b�o�̡C\n");
	setup();
}

int clean_up()
{
	// Do not clean up ourself unless the shop is cleaned up.
	if( objectp(query("shop_ob")) ) return 1;
	destruct(this_object());
	return 0;
}

void reset()
{
	object *inv;

	inv = all_inventory(this_object());

	// Make the goods in storage older that maybe we can sell some of them
	if( sizeof(inv) ) inv->add("pwaned_time", 1);

	// Destruct items that are not touched for a long time, say, 30 resets.
	// This should be longer than the time that pawned goods can be sold.
	for(int i=0; i<sizeof(inv); i++)
	if( (int)inv[i]->query("pawned_time") > 4 )
//	destruct(inv[i]);
	inv[i]->delete("pawned_time");
}
