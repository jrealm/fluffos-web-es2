/*  estimate.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object ob = me;
    int my_ability, my_defense, my_strength;
    int hir_ability, hir_defense, hir_strength;
    int cmp_ability, cmp_defense, cmp_strength;
    mapping weapon;
    string msg;

    if( arg ) {
	ob = present(arg, environment(me));
	if( !ob || !ob->is_character() || !ob->visible(me) )
	    return notify_fail("�o�̨S�� " + arg + " �o�ӤH�C\n");
    }

    // Calculate my attack ability

    my_ability = me->query_ability("attack");
    if( mapp(weapon = me->query_temp("weapon")) && sizeof(weapon) ) {
	int v, best = 0;
	string sk;
	object foo;

	foreach(sk, foo in weapon)
	    if( (v=me->query_skill(sk)) > best ) best = v;
	my_ability += best;
    }
    else my_ability += me->query_skill("unarmed");
    if( ! my_ability ) my_ability = 1;

    // Calculate my defense ability

    my_defense = me->query_ability("defense");
    if( me->skill_mapped("dodge") ) my_defense += me->query_skill("dodge");
    if( ! my_defense ) my_defense = 1;

    // Calculate my attack strength

    my_strength = me->query_strength("attack");
    if( me->skill_mapped("force") != "force" )
	my_strength += me->query_skill("force") * me->query_stat("kee") * 4;
    if( ! my_strength ) my_strength = 1;

    if( ob==me ) {
	printf("�A�����ۤv�b�Z�\\�ۼƤW���� %d ���{�סC\n", my_ability);
	printf("�u�m�譱���Ӧ� %d �����ǡC\n", my_defense);
	printf("���O�@�����ܯ঳ %.2f ���祪�k���O�D�C\n", my_strength / 1000.0);
	return 1;
    }

    // Calculate target attack ability

    hir_ability = ob->query_ability("attack");
    if( mapp(weapon = ob->query_temp("weapon")) && sizeof(weapon) ) {
	int v, best = 0;
	string sk;
	object foo;

	foreach(sk, foo in weapon)
	    if( (v=ob->query_skill(sk)) > best ) best = v;
	hir_ability += best;
    }
    else hir_ability += ob->query_skill("unarmed");

    // Calculate my defense ability

    hir_defense = ob->query_ability("defense");
    if( ob->skill_mapped("dodge") ) hir_defense += ob->query_skill("dodge");

    // Calculate target attack strength

    hir_strength = ob->query_strength("attack");
    if( ob->skill_mapped("force") != "force" )
        hir_strength += ob->query_skill("force") * ob->query_stat("kee") * 4;

    // Give remarks.

    if( my_ability < 1 ) my_ability = 1;
    if( my_strength < 1 ) my_strength = 1;
    if( my_defense < 1 ) my_defense = 1;

    cmp_ability  = (my_ability - hir_ability) * 100 / my_ability;
    cmp_strength = (my_strength - hir_strength) * 100 / my_strength;
    cmp_defense  = (my_defense - hir_defense) * 100 / my_defense;

    msg = "�A����" + ob->name() + "���Z�\\�b�ۼƤW";

    if( cmp_ability < -150 )
        msg += "���ө�A�A";
    else if( cmp_ability < -80 )
        msg += "���X�A�Ʀh�A";
    else if( cmp_ability < -40 )
        msg += "���X�A�@�I�A";
    else if( cmp_ability < -10 )
        msg += "��A���Ӥ@�w�A";
    else if( cmp_ability < 10 )
        msg += "�P�A�u�b�B�򤧶��A";
    else if( cmp_ability < 40 )
        msg += "�����A�@�w�A";
    else if( cmp_ability < 80 )
        msg += "�M�A�ۤ�ᦳ���p�A";
    else if( cmp_ability < 150 )
        msg += "�M�A�ۤ�t�ۦѤj�@�I�A";
    else
        msg += "��A�Ө��@���c���¯١A";

    msg += "�b�u�m�譱";

    if( cmp_defense < -150 )
        msg += "���ө�A�A";
    else if( cmp_defense < -80 )
        msg += "���X�A�Ʀh�A";
    else if( cmp_defense < -40 )
        msg += "���X�A�@�I�A";
    else if( cmp_defense < -10 )
        msg += "��A���Ӥ@�w�A";
    else if( cmp_defense < 10 )
        msg += "�P�A�u�b�B�򤧶��A";
    else if( cmp_defense < 40 )
        msg += "�����A�@�w�A";
    else if( cmp_defense < 80 )
        msg += "�M�A�ۤ�ᦳ���p�A";
    else if( cmp_defense < 150 )
        msg += "�M�A�ۤ�t�ۦѤj�@�I�A";
    else
        msg += "��A�Ө��@���c���¯١A";

    if( cmp_defense * cmp_strength > 0 )
        msg += "�ӥB�b�O�D�W�]";
    else
        msg += "���O�b�O�D�W�o";

    if( cmp_strength < -150 )
        msg += "���ө�A�C\n";
    else if( cmp_strength < -80 )
        msg += "�j�L�A�Ʀh�C\n";
    else if( cmp_strength < -40 )
        msg += "�j�L�A�@�j�I�C\n";
    else if( cmp_strength < -10 )
        msg += "��A���Ӥ@�w�C\n";
    else if( cmp_strength < 10 )
        msg += "�P�A�b�B�򤧶��C\n";
    else if( cmp_strength < 40 )
        msg += "�����A�@�w�C\n";
    else if( cmp_strength < 80 )
        msg += "�ᤣ�p�A�C\n";
    else if( cmp_strength < 150 )
        msg += "�t�ۧA�Ѥj�@�I�C\n";
    else
        msg += "��A�Ө����Ȥ@�S�C\n";

    write(msg);
    return 1;
}

int help()
{
    write(@TEXT
���O�榡�Gestimate [<��H>]

�o�ӫ��O���A�j�������@�ӹ�⪺��O�A�p�G���[��H�A�h�O�����ۤv���Z���C
TEXT
    );
    return 1;
}
