// ghostbaby.c

inherit ITEM;

void create()
{
        set_name("������", ({ "ghostbaby" }));
        set_weight(1);
        if( !clonep() ) {
                set("unit", "��");
                set("long",
                        "�o�O�@�Ӱ�����, �i�H�N���A�w���C\n");
        set("no_sell", 1);
//	set("no_drop",1);
        set("value", 1000000000);
        }
        set("keep_this", 1);
        setup();
}

int query_autoload() { return 1; }
