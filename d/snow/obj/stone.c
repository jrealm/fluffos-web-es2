#include <armor.h>
#include <ansi.h>
void do_clean(object me);


void create()
{
	set_name(GRN"�C�m��"NOR, ({ "stone" }));
	set_weight(100000000);
	set("no_get", 1);
        if( !clonep() ) {
                set("unit", "��");
		set("value", 1);
                set("long",
"�@���C�m���ꪺ�j��, �i�H���h�A���W���ê��O��
�Y�O�A�bŪ���d���O�����D, �i�H�յۺN�N�o���j
��(touch stone)�C\n");
        }
	setup();
}

void init()
{
	add_action("do_touch", "touch");
}

int do_touch(string arg)
{
	if( arg != "stone" ) return notify_fail("�A�Q�N����?\n");

	if( this_player()->query_temp("stone/clean") ) {
		tell_object(this_player(),
		"�t�βM���O����, �еy�ݡC\n\n");
		call_out( (: do_clean, this_player() :), 1);
		this_player()->delete_temp("stone/clean");
		return 1; 
	}

	tell_object(this_player(),
	"�@�ѩ_�����n���b�A�����T�_:
Ū�d���o�ͧx����??�A�T�w�n�M���A�Ҧ����O����, �ЦA�N�@���C\n");
	this_player()->set_temp("stone/clean", 1);
	return 1;
}

void do_clean(object me)
{
	object link_ob;
        seteuid(getuid());
	link_ob = me->link();
	if( link_ob->query("board_last_read/announce") ) {
		link_ob->set("board_last_read/announce", 000000001);}
	if( link_ob->query("board_last_read/board_tree") ) {
		link_ob->set("board_last_read/board_tree", 000000001);}
	if( link_ob->query("board_last_read/bridge_b") ) {
		link_ob->set("board_last_read/bridge_b", 000000001);}
	if( link_ob->query("board_last_read/bug") ) {
		link_ob->set("board_last_read/bug", 000000001);}
	if( link_ob->query("board_last_read/chin_palace_b") ) {
		link_ob->set("board_last_read/chin_palace_b", 000000001);}
	if( link_ob->query("board_last_read/choyin_b") ) {
		link_ob->set("board_last_read/choyin_b", 000000001);}
	if( link_ob->query("board_last_read/common") ) {
		link_ob->set("board_last_read/common", 000000001);}
	if( link_ob->query("board_last_read/fighter") ) {
		link_ob->set("board_last_read/fighter", 000000001);}
	if( link_ob->query("board_last_read/kangpin_b") ) {
		link_ob->set("board_last_read/kangpin_b", 000000001);}
	if( link_ob->query("board_last_read/lee_b") ) {
		link_ob->set("board_last_read/lee_b", 000000001);}
	if( link_ob->query("board_last_read/market_b") ) {
		link_ob->set("board_last_read/market_b", 000000001);}
	if( link_ob->query("board_last_read/purple_b") ) {
		link_ob->set("board_last_read/purple_b", 000000001);}
	if( link_ob->query("board_last_read/swaylan_b") ) {
		link_ob->set("board_last_read/swaylan_b", 000000001);}
	if( link_ob->query("board_last_read/wutan_b") ) {
		link_ob->set("board_last_read/wutan_b", 000000001); }

	tell_object(me, "�O���w�����C\n");
	me->save();
	return;
}
