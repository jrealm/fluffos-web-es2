inherit ITEM;
void create()
{
        set_name("���K�b", ({ "iron arrow", "arrow" }));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 4000);
                set("long", "�@�ڬ��K�s�����b, ��u���.\n");
        }
        setup();
}
