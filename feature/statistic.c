/*  statistic.c

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
#include <dbase.h>
#include <login.h>
#include <move.h>
#include <statistic.h>

// variables

static int regenerating = 1;

mapping st_maximum = ([]);
mapping st_effective = ([]);
mapping st_current = ([]);
mapping st_notify = ([]);

static mapping st_regenerator;
static object last_from_ob;
static mapping f_exhausted = ([]);
static mapping f_destroyed = ([]);
static mapping f_notified = ([]);

// implementations

string* query_stat_name() { return mapp(st_maximum) ? keys(st_maximum) : ({}); }
object last_damage_giver() { return last_from_ob; }
mapping query_exhausted() { return f_exhausted; }
mapping query_destroyed() { return f_destroyed; }
mapping query_notified() { return f_notified; }

void clear_statistic_flags()
{
    f_exhausted = ([]);
    f_destroyed = ([]);
    f_notified = ([]);
}

/*  query_stat()
 *
 *  ���o�Y�@���򥻼ƭȡC
 *
 *  �C�@�Ӱ򥻼ƭȳ��ѤT�ӼƦr�өw�q�G
 *
 *	�ثe�� (current)
 *	���A�� (effective)
 *	�W���� (maximum)
 *
 *  �]���U�ؤH�����ͩR���A���P�A�o�T�ӼƦr�i�঳���w�q�����A�C
 */
int
query_stat(string what)
{
    int val;

    if( mapp(st_current)
    &&	!undefinedp(val=st_current[what]) ) return val;
    if( mapp(st_effective)
    &&	!undefinedp(val=st_effective[what]) ) return val;
    if( mapp(st_maximum)
    &&	!undefinedp(val=st_maximum[what]) ) return val;

    return 0;
}

void
delete_stat(string what)
{
    if( mapp(st_current) )	map_delete(st_current, what);
    if( mapp(st_effective) )	map_delete(st_effective, what);
    if( mapp(st_maximum) )	map_delete(st_maximum, what);
    if( mapp(st_notify) )	map_delete(st_notify, what);
    if( mapp(st_regenerator) )	map_delete(st_regenerator, what);
}

/*  ���o�򥻼ƭȪ���T
 */
int query_stat_current(string what)
    { return mapp(st_current) ? st_current[what] : 0; }

int query_stat_effective(string what)
    { return mapp(st_effective) ? st_effective[what] : 0; }

int query_stat_maximum(string what)
    { return mapp(st_maximum) ? st_maximum[what] : 0; }

int query_stat_notify(string what)
    { return mapp(st_notify) ? st_notify[what] : 0; }

mixed query_stat_regenerate(string what)
    { return mapp(st_regenerator) ? st_regenerator[what] : 0; }

/*  �]�w�򥻼ƭ�
 */
int set_stat_current(string what, int val)
    { return mapp(st_current) ? st_current[what] = val : 0; }

int set_stat_effective(string what, int val)
    { return mapp(st_effective) ? st_effective[what] = val : 0; }

int set_stat_maximum(string what, int val)
    { return mapp(st_maximum) ? st_maximum[what] = val : 0; }

int set_stat_notify(string what, int val)
    { return mapp(st_notify) ? st_notify[what] = val : 0; }

int
advance_stat(string what, int val)
{
    if( !mapp(st_maximum) || undefinedp(st_maximum[what]) ) return 0;

    return (st_maximum[what] += val);
}

/*  set_stat_regenerate()
 *
 *  �]�w�򥻼ƭȪ���s�覡�C
 */

mixed
set_stat_regenerate(string what, mixed val)
{
    int max;

    /* �p�G�o�Ӱ򥻼ƭȪ��̤j�ȥ��w�q�A�h����]�w��s�覡�C */
    if( !(max = query_stat_maximum(what)) ) return 0;

    if( functionp(val) )
	return (st_regenerator[what] = val);

    switch(val)
    {
    case TYPE_STATIC:
	/* �o���򥻼ƭȬO���|�۰ʧ�s�� */
	return (st_regenerator[what] = 0);
    case TYPE_HEALTH:
	/* �o���򥻼ƭȬO�|�H�ɶ��۰ʫ�_�� */
	if( undefinedp(query_stat_current(what)) )
	    set_stat_current(what, max);
	if( undefinedp(query_stat_effective(what)) )
	    set_stat_effective(what, max);
	return (st_regenerator[what] = (: health_regenerator :) );
    case TYPE_WASTING:
	/* �o���򥻼ƭȬO�|�H�ɶ��C�C��֪� */
	if( undefinedp(query_stat_current(what)) )
	    set_stat_current(what, max);
	if( undefinedp(query_stat_effective(what)) )
	    set_stat_effective(what, max);
	return (st_regenerator[what] = (: wasting_regenerator :) );
    default:
	error("undefined regenerate method.\n");
    }
    return 0;
}

/* ��l�ƤH�����򥻼ƭ� */

void
init_statistic(mapping base)
{
    mapping st;
    string s;
    int val;

    if( mapp(st = query("statistic/maximum")) ) {
	st_maximum = st;
	delete("statistic/maximum");
    }

    if( mapp(st = query("statistic/effective")) ) {
	st_effective = st;
	delete("statistic/effective");
    }

    if( mapp(st = query("statistic/current")) ) {
	st_current = st;
	delete("statistic/current");
    }

    if( mapp(st = query("statistic/notify")) ) {
	st_notify = st;
	delete("statistic/notify");
    }

    if( mapp(st = query("statistic")) ) delete("statistic");

    if( !mapp(st_maximum) ) st_maximum = allocate_mapping(NUM_STATISTICS);
    if( !mapp(st_effective) ) st_effective = allocate_mapping(NUM_STATISTICS);
    if( !mapp(st_current) ) st_current = allocate_mapping(NUM_STATISTICS);
    if( !mapp(st_notify) ) st_notify = allocate_mapping(NUM_STATISTICS);
    if( !mapp(st_regenerator) ) st_regenerator = allocate_mapping(NUM_STATISTICS);

    if( mapp(base) && sizeof(base) )
	foreach(s, val in base)
	    if( undefinedp(st_maximum[s]) ) st_maximum[s] = val;
}

// consume_stat()
//
// This is the formal method to let a character 'consume' its statistic
// current value. Once a statistic has been exhausted (i.e. current value
// drop below zero), a flag is set (to the object caused the last consumption)
// and it should be checked in heart_beat to make proper change.
//
// This function also starts regeneration automatically.

varargs int
consume_stat(string type, int damage, object who)
{
    if( damage < 0 ) error("damage less than zero.\n");
    if( damage == 0 ) return 0;

    /* �Y�����w�o�Ӷˮ`�Ӧۭ��@�ӥͪ��A�ϥΥH�U�W�h�q�� */
    if( !objectp(who) ) {
	if( this_player() ) who = this_player();
	else if( previous_object() && previous_object()->is_character() )
	    who = previous_object();
	else
	    who = this_object();
    }

    /* �p�G�o�ذ򥻼ƭȤ��s�b�A������^�H�`�ٮɶ� */
    if( !mapp(st_current)
    ||	undefinedp(st_current[type])
    ||	f_exhausted[type] )
	return 0;

    last_from_ob = who;
    st_current[type] -= damage;

    /* �Y�o�Ӱ򥻼ƭȪ��ثe�Ȥw�g�ӺɡA�]�w�O���� heart_beat �ɳB�z */
    if( st_current[type] < 0 ) {
        st_current[type] = 0;
        f_exhausted[type] = who;
    }

    /* �Y�C��]�wĵ�ܪ��ʤ���A�]�w�O���� heart_beat �ɳB�z */
    if( who && mapp(st_notify) && !undefinedp(st_notify[type])) {
	if( mapp(st_maximum) && !undefinedp(st_maximum[type])
	&&  st_maximum[type] > 0
	&&  st_current[type]*100/st_maximum[type] < st_notify[type] )
	    f_notified[type] = who;
    }

    start_regenerate();
    return damage;
}

// damage_stat()
//
// This is the formal method to let a character receive 'damage', which
// reduces the effective value of a statistic. Once the effective value
// of a statistic drops below zero, the statistic is 'destroyed', and a
// flag is set (to the object that causes the last damage). This flag
// should be checked in heart_beat and make proper changes.
//
// This function also starts regeneration automatically.

varargs int
damage_stat(string type, int damage, object who)
{
    if( damage < 0 ) error("damage less than zero.\n");
    if( damage == 0 ) return 0;

    /* �Y�����w�o�Ӷˮ`�Ӧۭ��@�ӥͪ��A�ϥΥH�U�W�h�q�� */
    if( !objectp(who) ) {
	if( this_player() ) who = this_player();
	else if( previous_object() && previous_object()->is_character() )
	    who = previous_object();
	else
	    who = this_object();
    }

    /* �p�G�o�ذ򥻼ƭȤ��s�b�A�Τw�g�p�� 0�A������^�H�`�ٮɶ� */
    if( !mapp(st_effective)
    ||	undefinedp(st_effective[type])
    ||	f_destroyed[type] )
	return 0;

    last_from_ob = who;
    st_effective[type] -= damage;

    /* �p�G�ثe�Ȥj�󪬺A�ȡA�N�ثe�ȭ��C�쪬�A�Ȫ����� */
    if( mapp(st_current) && st_current[type] > st_effective[type] )
	st_current[type] = st_effective[type];

    /* �Y�o�Ӱ򥻼ƭȪ����A�Ȥw�g�ӺɡA�]�w�O���� heart_beat �ɳB�z */
    if( st_effective[type] < 0 ) {
        st_effective[type] = 0;
        f_destroyed[type] = who;
    }
    /* �Y�C��]�wĵ�ܪ��ʤ���A�]�w�O���� heart_beat �ɳB�z */
    else if( who && mapp(st_notify) && !undefinedp(st_notify[type])) {
	if( mapp(st_maximum) && !undefinedp(st_maximum[type])
	&&  st_maximum[type] > 0
	&&  st_effective[type]*100/st_maximum[type] < st_notify[type] )
	    f_notified[type] = who;
    }

    start_regenerate();
    return damage;
}

// supplement_stat()
//
// This is the formal method to supplement statistics of a character.
// Note supplement can fill a statistic's current value up to its
// effective value.
//
// This function also starts regenerating automatically.

int
supplement_stat(string type, int heal)
{
    int old_stat;

    if( heal < 0 ) error("heal less than zero.\n");

    if( !mapp(st_current) || undefinedp(st_current[type]) ) return 0;

    old_stat = st_current[type];
    st_current[type] += heal;

    if( mapp(st_maximum) && st_current[type] > st_maximum[type] )
	st_current[type] = st_maximum[type];

    if( mapp(st_effective) && st_current[type] > st_effective[type] )
	st_current[type] = st_effective[type];

    start_regenerate();
    return st_current[type] - old_stat;
}

// heal_stat()
//
// This is the formal method to heal a character's statistic. Healing
// a statistic can fill its effective value up to its maximum.
//
// This function also starts regenerating automatically.

int
heal_stat(string type, int heal)
{
    int old_stat;

    if( heal < 0 ) error("heal less than zero.\n");

    if( !mapp(st_effective) || undefinedp(st_effective[type]) ) return 0;

    old_stat = st_effective[type];
    st_effective[type] += heal;

    if( mapp(st_maximum) && st_effective[type] > st_maximum[type] )
	st_effective[type] = st_maximum[type];

    start_regenerate();
    return st_effective[type] - old_stat;
}

// start_regenerate()
//
// This function starts regenerating manually. The regenerating is on by
// default when characters inherits F_STATISTIC was created. It can be
// turned off by regenerate() eventually. If you want force regenerating
// to start, call this function.

void start_regenerate() { regenerating = 1; }

/*  regenerate()
 *
 *  �򥻼ƭȪ���s�禡�C�b�H���� heart_beat ���C��@�� tick ���ɶ���
 *  �F�A�N�|�I�s�o�Ө禡�ӧ�s�H�����򥻼ƭȡC
 *
 *  ��H�����Ҧ��򥻼ƭȳQ�]�w����s�禡���Ǧ^ 0 ���ɭԡAregenerate
 *  �|�۰ʧ�ۤv�����A���� start_regenerate �Q�I�s����C
 */

int regenerate()
{
    string st;
    mixed regenerator;
    int n_updated = 0;

    if( !regenerating ) return 0;

    if( !mapp(st_regenerator)
    ||	!mapp(st_maximum) )
	return 0;

    foreach(st, regenerator in st_regenerator)
    {
	if( evaluate( regenerator,
	    this_object(),
	    st,
	    st_maximum[st],
	    mapp(st_effective) ? st_effective[st] : 0,
	    mapp(st_current) ? st_current[st] : 0) )
		n_updated++;
	if( mapp(st_effective) && st_effective[st] < 0 && !f_destroyed[st])
	    f_destroyed[st] = this_object();
	if( mapp(st_current) && st_current[st] < 0 && !f_exhausted[st])
	    f_exhausted[st] = this_object();
    }

    return regenerating = (n_updated > 0);
}

// The following functions are default regenerator of statistics. You
// can either use them, or just took them as examples and write your
// own.

int
health_regenerator(object me, string stat, int max, int eff, int cur)
{
    if( eff <= 0 ) return 0;	/* ���A�� <= 0 ���򥻼ƭȤ��|�۵M��_ */

    if( userp(me) ) {		/* �ϥΪ̥���������(��O)�Ȥ~���_�ثe�� */
	if( me->is_fighting()
	||  (int)me->query_stat("water") < 1
	||  me->over_encumbranced() )
	    return 0;
    }

    if( cur < eff ) {	/* ��_�ثe�� */
	switch(stat)
	{
	case "gin":
	    return me->supplement_stat(stat, (int)me->query_attr("dex") );
	case "kee":
	    return me->supplement_stat(stat, (int)me->query_attr("con") );
	case "sen":
	    return me->supplement_stat(stat, (int)me->query_attr("spi") );
	case "HP":
	    return me->supplement_stat(stat, 1 );
	default:
	    return me->supplement_stat(stat, (int)me->query_level() );
	}
    }

    if( userp(me) && ((int)me->query_stat("food") < 1) ) return 0;

    if( eff < max ) {	/* ��_���A�� */
        switch(stat)
        {
	case "gin":
	    return me->heal_stat(stat, (int)me->query_attr("dex") / 6 + 1 );
	case "kee":
	    return me->heal_stat(stat, (int)me->query_attr("con") / 6 + 1);
	case "sen":
	    return me->heal_stat(stat, (int)me->query_attr("spi") / 6 + 1);
	case "HP":
	    return me->heal_stat(stat, 1 );
	default:
	    return me->heal_stat(stat, (int)me->query_level() / 6 + 1);
	}
    }

    return 0;
}

int
wasting_regenerator(object me, string stat, int max, int eff, int cur)
{
    /* NPC ���|�f���ξj�{�l */
    if( !userp(me) ) return 0;

    return me->consume_stat(stat, 1 + (me->is_fighting() ? 2 : 0), me);
}

