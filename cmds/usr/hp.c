/*  hp.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>

inherit F_CLEAN_UP;

private string status_color(object me, string stat);

int main(object me, string arg)
{
    object ob;
    
    if( !wizardp(me) || !arg )    ob=me;
    else {
	ob = LOGIN_D->find_body(arg);
	if( !ob )    ob = present(arg, environment(me));
	if( !ob )    ob = find_living(arg);
	if( !ob )    return notify_fail("�S�� " + arg + " �o�ӤH���C\n");
	write("[" + ob->name() + "]");
    }    
    printf( // SAVEC HOME
    	"���� %s%d/%d" NOR "\t�� %s%d/%d" NOR "\t�� %s%d/%d" NOR "\t�� %s%d/%d\n" NOR
    	"���� %s%d/%d" NOR "\t���� %s%d/%d" NOR "\t�h�� %s%d/%d\n" NOR,
	status_color(ob, "HP"),
	ob->query_stat("HP"),
	ob->query_stat_effective("HP"),
	status_color(ob, "gin"),
	ob->query_stat("gin"),
	ob->query_stat_effective("gin"),
	status_color(ob, "kee"),
	ob->query_stat("kee"),
	ob->query_stat_effective("kee"),
	status_color(ob, "sen"),
	ob->query_stat("sen"),
	ob->query_stat_effective("sen"),
	HIG,
	ob->query_stat("food"),
	ob->query_stat_maximum("food"),
	HIG,
	ob->query_stat("water"),
	ob->query_stat_maximum("water"),
	HIG,
	ob->query_stat("fatigue"),
	ob->query_stat_maximum("fatigue"),
    );
    return 1;
}

private string
status_color(object me, string stat)
{
    int current = me->query_stat(stat);
    int max = me->query_stat_maximum(stat);
    int ratio = max ? (current * 100) / max : 100;

    if( ratio >= 90 ) return HIG;
    else if( ratio > 50 ) return HIY;
    else if( ratio > 20 ) return HIR;
    else return RED;
}

int help(object me)
{
write(@HELP
���O�榡 : hp [<�H�� ID>]

�γ~ : ���U�A�ݨ�ثe��²�n���A�C�Ův�i�H�d�L�H��²�n���A�C
HELP
     );
     return 1;
}
