// army.c

inherit F_NAME;
inherit F_MOVE;
inherit F_DBASE;
inherit F_ATTRIBUTE;
inherit F_STATISTIC;

void setup()
{
	seteuid(getuid());
	if( clonep() ) {
//		set_heart_beat();
		enable_commands();
		if( !query_stat("surviver") )
			set_stat_maximum("surviver", 1);
	}
}

string short()
{
	int nmem;

	nmem = query_stat("surviver");

	return sprintf("%s [ �L�O%s�H ]",
		::short(),
		( nmem > 10 ) ? ("��" + chinese_number(nmem - nmem%10) + "�h") : ("�@" + chinese_number(nmem)) );
}
