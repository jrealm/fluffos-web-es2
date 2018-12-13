/*  study.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <dbase.h>
#include <name.h>

int study_content(object me);
int halt_study(object me, object from, string how);

int study_ob(object me)
{
    mapping req, content;
    string t, msg;
    int min, max, to_learn = 0;

    if( this_player()->is_busy() )
	return notify_fail("�A�����ۨ�L�ƩO�I\n");
    if( this_player()->is_fighting() )
	return notify_fail("�A�٬O�����I���e���ĤH�a�I\n");
    req = query("required/attribute");
    if( mapp(req) ) {
	foreach(t, min in req)
	    if( this_player()->query_attr(t, 1) < min ) {
		write("�A��" + to_chinese(t) + "�����A�ҥH��o�W���O����"
			"���e�����L�k��|�C\n");
		return 1;
	    }
    }
    req = query("required/skill");
    if( mapp(req) ) {
	foreach(t, min in req)
	    if( this_player()->query_skill(t, 1) < min ) {
		write("�A�b" + to_chinese(t) + "�W���y���٤����z�ѳo�W���ҰO�������e�C\n");
		return 1;
	    }
    }

    /* �u���ŦX���󪺤H�~���D�O�������e���S���� .... */
    content = query("content");
    if( !content )
	return notify_fail("�o�W���S���O�����򦳥Ϊ����e�C\n");

    foreach(t, max in content)
	if( this_player()->query_skill(t, 1) < max ) to_learn++;
    if( ! to_learn ) {
	write("�o�W���O�������e��A�Ө����F�L�s�N ...�C\n");
	return 1;
    }

    this_player()->start_busy((: study_content :), (: halt_study :));
    if( stringp(msg = query("study_msg")) )
	message_vision(msg, this_player());
    else
	message_vision("$N�}�l�E��|���a��Ū" + name() + "�W�������e�C\n",
		this_player());

    return 1;    
}

int study_content(object me)
{
    mapping content;
    int skill, archaism, cost, max, point, gain = 0;
    string t;

    if( ! mapp(content = query("content"))
    ||	! sizeof(content) ) return 0;

    /* �ϥ�Ū���Ѧr���ޯ� */
    skill = me->query_skill("literate");

    /* �Ӻ믫 1 - 10 �I */
    cost = 1 + (9 - me->query_attr("wis")/3);
    if( cost < 1 ) cost = 1;

    /* �Y�ݭn�j�媾�ѡA���s�p��ޯ�ηl�� */
    if( (archaism = query("required/skill/archaic attainment")) ) {
	skill = skill/10 + me->query_skill("archaic attainment");
	cost *= 2;
    }

    if( me->query_stat("sen") < cost
    ||	me->query_stat("gin") < cost
    ||	me->query_stat("fatigue") >= me->query_stat_maximum("fatigue") ) {
	tell_object(me, "�Aı�o�믫���~�A�L�k�A�~���Ū�F�C\n");
	return 0;
    }

    me->consume_stat("gin", cost);
    me->consume_stat("sen", cost);

    point = me->query_attr("int") / sizeof(content);
    foreach(t, max in content) {
	if( max > skill ) max = skill;	
	if( me->query_skill(t, 1) < content[t]
	&&  random( point + skill ) >= max/2 ) {
	    me->improve_skill(t, 1 + random(point));
	    gain++;
	}
    }

    if( gain ) {
	me->improve_skill("literate", 1 + random(me->query_attr("int")));
	if( archaism )
	    me->improve_skill("archaic attainment",
		1 + random(me->query_attr("int")));
	me->supplement_stat("fatigue", gain);
	me->damage_stat("sen", gain);
    }

    return 1;
}

int halt_study(object me, object from, string how)
{
	string msg;
	if( stringp( msg = query("halt_msg") ) ) 
		write( msg );
	else
		write("�A�����Ū" + name() + "�W���O�������e�C\n");
		return 1;
}
