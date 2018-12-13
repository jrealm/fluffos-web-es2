/*  berserk.c - berserk command

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

void do_berserk(object);

private void create() { seteuid(getuid()); }

int
main(object me, string arg)
{
    object ob;
    mapping weapon;
    string skill;

    weapon = me->query_temp("weapon");

    if( me->is_busy() )
	return notify_fail("�Х��� halt ����A���b�����ơC\n");

    /* NPC ���ˬd�o�ǭ��� */
    if( userp(me) )
    {
	if( me->query_stat("fatigue") >= me->query_stat_maximum("fatigue") )
	    return notify_fail("�A�Ӳ֤F�A�𮧤@�|��a�C\n");

	if( !me->query_learn("berserk", 1) )
	    return notify_fail("�A���|�o���ޯ�C\n");

	if( !me->is_fighting() )
	    return notify_fail("�A�n�b�԰����~��I�i�g���ð����k�I\n");

	if( mapp(weapon) && sizeof(weapon) ) {
	    foreach(skill, ob in weapon)
		if( skill[0..8] != "twohanded" )
		    return notify_fail("�A������������Z���~��ϥγo�ؾԳN�C\n");
	}

	if( me->query_stat("gin") < me->query_stat_maximum("kee")/10 )
	    return notify_fail("�A����O�����F�C\n");

	me->supplement_stat("fatigue", 3);
    }

//    message_vision(HIR "\n$N�@�n��q�A�j�ۡG�u��������I�v\n\n" NOR,
//	me);
    do_berserk(me);

    return 1;
}

void
do_berserk(object me)
{
    object ob, *enemy;
    int skill, power, cost, max_attack, max_hit, penalty, exp, kee_cost;

    /* berserk ����O�ݮ𪺱j�צөw�A�����Ӫ��O��O */
    // �[�W�M�O�M�x�Ѫ��ĥ�, �þ���W�խ�berserk���}�a�O, ���F�]��
    // berserk + powerblow �ثe�L��ɤO�~, ����w�d���}��ޯ঳�A
    // �W�j�x�H�����O���Ŷ�, �p: leadership  -dragoon
    cost = (me->query_attr("str")+me->query_attr("cor")) / 3 +
	me->query_stat("kee") / 30;
    if( me->query_stat("gin") < cost ) {
	tell_object(me, "�A���뤣���F�C\n");
	return;
    }
    // �[�W����]�w, ����berserk�b�C����ԤW�ү�ϥΪ��W������
    // �קKsr�i�H�bfr�@�ۥ��o���p�U�K�������
    kee_cost = me->query_stat_maximum("kee") / 8;
    if( me->query_stat("kee") < kee_cost ) {
	tell_object(me, "�A���𤣰��F�C\n");
	return;
    }

    message_vision(HIR "\n$N�@�n��q�A�j�ۡG�u��������I�v\n\n" NOR,
        me);

    /* �j�׸�Ү��Ӫ������A�������ƩM�ޯ঳�� */
    skill = me->query_skill("berserk");
    power = cost * 3500;		/* �̤j(�ʦ�) 700Kg */
    max_attack = skill / 20;		/* �������� 4 - 9 */
    if( max_attack < 4 ) max_attack = 4;
    max_hit = skill / 45;		/* �̤j = 4 */
    if( max_hit < 1 ) max_hit = 1;

    me->add_temp("apply/attack", skill/4);
    me->add_temp("apply/strength", power);

    /* ����I�Ҧ��ĤH�A�p�G�٦��l�O�A�A�h���X�� */
    enemy = me->query_enemy();
    while( max_hit-- && max_attack ) {
	foreach(ob in enemy) {
	    if( ! ob ) continue;	/* �p�G�ĤH�w�g���F�A���L�L :P */
	    // �Y�O�ĤH���b�P�@�өж�, ���L
	    if( environment(ob) != environment(me) ) continue;
	    me->attack(ob);
	    // �C�X������@���������g���, �H���y���a�b��Ԥ��ǲ� berserk, 
	    // �g��ȻP�������ޥ�����
	    exp = 1 + me->query_skill("berserk")/3
		+ random(me->query_skill("berserk"))/3;
 	    // �b�ޥ�������, �x�Ѱ���ޯ�ǲߦ��������U
 	    if( skill < 80 ) exp += random(me->query_attr("cor"));
	    me->improve_skill("berserk", exp);
	    if( --max_attack < 1 ) break;
	}
    }

    me->add_temp("apply/attack", - skill/4);
    me->add_temp("apply/strength", - power);

    /* ������O */
    if( userp(me) )
    {
	me->damage_stat("gin", cost/6);
//	me->consume_stat("gin", cost);
	me->consume_stat("kee", kee_cost);
	
	// �����򥻪��ϥθg���, �P���ʬ���
	if( me->query_skill("berserk", 1) < 180 )
	    me->improve_skill("berserk", 1 + random(me->query_attr("int"))*2);
	me->gain_score("combat", 1 + random(max_hit));

	me->start_busy(2);
    }
    else me->start_busy(1);
}

int help()
{
    write(@TEXT
���O�榡�Gberserk

�@�ؾA�X�b�L��ê��Գ��θs�ޤ����ϥΪ��ԳN�A�ǥѼȮɩʪ����u�m�A�H�g
���ɫB�몺��ձ��h�ĤH�C

�o�إ��k����ʼɳ��Z�A�ӥB������O�ƹd�A���O�b����Z�����j���ĤH�ɩ����e
�����ġA�]���o�ؾԳN�@�L���k�i���A���H���m�C
TEXT
    );
    return 1;
}
