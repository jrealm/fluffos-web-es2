/*  analyze.c

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

int main(object me, string arg)
{
    object ob;
    string str;
    mapping apply, weapon;

    if( !arg ) ob = me;
    else {
        if( !(ob = find_player(arg))
        &&    !(ob = present(arg, environment(me)))
        &&    !(ob = find_living(arg)) )
            return notify_fail("�o�̨S�� " + arg + " �o�إͪ��C\n");
    }

    str = sprintf("%s���U����O���R�R\n", ob->name());
    str += HIY "\n<�򥻭� - �Ӧ��ݩ�>\n" NOR;
    str += sprintf("�����O\t\t��� %d�A�ޥ� %d�A�O�D %.2f ����\n",
	ob->query_ability("intimidate"),
	ob->query_ability("attack"),
	ob->query_strength("attack") / 1000.0);
    str += sprintf("���m�O\t\t�u�� %d�A�ޥ� %d�A�j�� %.2f ����\n",
	ob->query_ability("wittiness"),
	ob->query_ability("defense"),
        ob->query_strength("defense") / 1000.0);
    str += sprintf("�]�O\t\t��O�� %d�M�j�� %.2f Kw\n", ob->query_ability("magic"),
        ob->query_strength("magic") / 1000.0);
    str += sprintf("�k�O\t\t��O�� %d�M�j�� %.2f Kw\n", ob->query_ability("spell"),
        ob->query_strength("spell") / 1000.0);

    str += HIY "\n<�ץ��� - �Ӧۧޯ�>\n" NOR;
    if( ob->query_skill("force") && ob->skill_mapped("force")!="force" ) {
        int skill, modify;
        skill = ob->query_skill("force");
        modify = skill * ob->query_stat("kee") * 4;
        str += sprintf("�ϥΤ��O \t%s(�����j�� +%.2f Kg)\n",
            to_chinese(ob->skill_mapped("force")), (float)modify/1000.0);
    }
    if( mapp(weapon  = ob->query_temp("weapon")) && sizeof(weapon) ) {
        string term;
        str += "�ϥΪZ��\t";
        foreach(term in keys(weapon)) {
        str += sprintf("%s�M(������O %+d)\n\t\t", weapon[term]->name() + "(" + term + ")",
                    ob->query_skill(term));
        }
    }
    else str += sprintf("�{����� \t(������O %+d)\n", ob->query_skill("unarmed"));

    if( mapp(apply = ob->query_temp("apply")) ) {
        string term;
        int prop, k;

        str += HIY "\n<���[�� - �Ӧ۸˳ơA�k�N���v�T>\n" NOR;
        k = 0;
        foreach(term, prop in apply) {
            if( !intp(prop) ) continue;
            if( prop ) {
                str += sprintf("  %-16s %+d%s", to_chinese(term), prop,
                    k%2==0 ? "\t" : "\n");
                k++;
            }
        }
    }
    str += "\n";

    write(str);
    return 1;
}

int help()
{
    write(@TEXT
���O�榡�Ranalyze [<��H>]

�o�ӫ��O�|�C�X�@�Ǧ������w��H����O�ȡM�����w��H�ɫh�C�X�A�ۤv��
��O�ȡC
TEXT
    );
    return 1;
}
