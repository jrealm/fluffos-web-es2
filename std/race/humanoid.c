/*  humanoid.c - standard race daemon of humanoid type

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#define BASE_WEIGHT 40000

#include <ansi.h>
#include <statistic.h>
#include <combat.h>

inherit F_DBASE;

mapping *combat_action = ({
    ([	"action":	"$N��������$n��$l",
	"damage_type":	"���",
    ]),
    ([	"action":	"$N��$n��$l�@��",
	"damage_type":	"���",
    ]),
    ([	"action":	"$N��$n��$l�����a��F�@�}",
	"damage_type":	"���",
    ]),
    ([	"action":	"$N���_���Y��$n��$l���h",
	"damage_type":	"���",
    ]),
    ([	"action":	"$N���$n��$l�ΤO���X�@��",
	"damage_type":	"���",
    ]),
});

string* wear_type = ({
    "armor", "cloth", "feet_eq", "finger_eq", "hand_eq", "head_eq",
    "leg_eq", "neck_eq", "waist_eq"
});

// create()
//
// To save memory, we usually set the dafault object of a character
// to his race daemon. The properties we set here can be used as
// common default properties for characters of this race.

void create()
{
    seteuid(getuid());
    set("karma", 5);                // karma cost to select human when reincarnate
    set("life_form", "living");     // default life form.
    set("unit", "��");
    set("gender", "male");  // default gender

    set("default_body", USER_OB);   // default body object
    set("civilized", 1);
    set("humanoid", 1);
    set("commoner_score_base", 100);        // score base for gaining level
    set("attitude", "peaceful");            // default attitude
    set("limbs", ({
	"�Y��", "�V��", "�ݤf", "���", "����", "�k��", "���u",
	"�k�u", "����", "�k��", "�y��", "�p��", "���L", "�k�L",
	"���}", "�k�}"
    }) );
    set("phase", PHASE_PHYSICAL);
    set("default_actions", (: call_other, __FILE__, "query_action" :) );
}

// setup()
//
// setup() is called when a character is ready to enter the world. Note
// that for a player, setup() is called EVERYTIME he/she logins while
// initialize() is only called on character creation. For NPC, setup()
// is called everytime loaded.

void
setup(object ob)
{
    int food_max, water_max;

    seteuid(getuid());
    ob->set_default_object(__FILE__);
    ob->init_attribute();
    ob->init_statistic();

    food_max = ob->query_attr("con") *10 + ob->query_attr("str") * 5;
    water_max = ob->query_attr("cps") * 10 + ob->query_attr("dex") * 5;
    ob->set_stat_maximum("food", food_max);
    ob->set_stat_effective("food", food_max);
    ob->set_stat_maximum("water", water_max);
    ob->set_stat_effective("water", water_max);
}

// initialize()
//
// To initialize race-specific stuff of a character. 

void initialize(object ob)
{
    ob->set_default_object(__FILE__);
}

// This is the dafault_action implementation. You don't need call it
// "query_action" always. We usually set the property "default_action"
// to this function, and let characters access this via default object
// query. See create() for more information. If you are to define your
// own default_action for a character, just set the default_action
// property of the character to something else to override default object
// querying.

mapping query_action()
{
    return combat_action[random(sizeof(combat_action))];
}

string query_appearance(object ob)
{
    mapping attr;
    string a, best_a;
    int num;

    if( !mapp(attr = ob->query_attribute()) ) return "";

    best_a = "str";
    foreach(a, num in attr)
	if( num > attr[best_a] ) best_a = a;

    switch(best_a)
    {
	case "str": return "���o��I���y�A�ݰ_�Ӭ۷�ժZ���O";
	case "dex": return "�ͱo���u�T�y�A����w�M�Q���B��";
	case "cor": return "�ݰ_���x�ѹL�H�A�@�ƤѤ��Ȧa���Ȫ��Ҽ�";
	case "cps": return "�|��먬������q�e�A�ᦳ���s�Y��e������⪺��";
	case "int": return "�ݰ_�ӤQ�����D�A�Q���o�o�L�H";
	case "wis": return "�~���t�a���A���G��I���z";
	case "spi": return "�������`��A���H�@�إ@�~���H���Pı";
	case "con": return "�����Τú١A�ݰ_�����۷���";
    }
}

// advance_level()
//
// This function is called by F_SCORE when a character's score reaches
// target_score. You can give bonus to the character here with race
// concern, i.e.  mature the character.

void advance_level(object ob)
{
    int roll;


    roll = random(100);
    if( roll < 30 ) {
	string attr, c_attr;
	if( roll==0 )		{ attr = "dex"; c_attr = "����"; }
	else if( roll < 2 )	{ attr = "spi"; c_attr = "�F��"; }
	else if( roll < 4 )	{ attr = "con"; c_attr = "�ڰ�"; }
	else if( roll < 8 )	{ attr = "str"; c_attr = "�M�O"; }
	else if( roll < 12 )	{ attr = "int"; c_attr = "����"; }
	else if( roll < 16 )	{ attr = "cps"; c_attr = "�w�O"; }
	else if( roll < 25 )	{ attr = "wis"; c_attr = "�z��"; }
	else			{ attr = "cor"; c_attr = "�x��"; }

	ob->set_attr( attr, (int)ob->query_attr(attr, 1) + 1 );
	tell_object(ob, HIW "�A��" + c_attr + "�ȴ����F�T\n" NOR);
    }
}

// valid_wield()
//
// This function determines if a character of this race can wield a
// weapon in certain skill. When a character attempts to wield a weapon,
// the valid_wield() is called in his race daemon and class daemon to
// determine if he can wield it. In this example, we check that a human
// can only wield a primary weapon and a secondhand weapon.

int valid_wield(object me, object ob, string skill)
{
    mapping weapon;
    string *sk;
    int str, best_str;


    // Check strength
    str = me->query_attr("str");
    if( skill[0..8]=="twohanded" ) best_str = ob->weight() / 1000;
    else if( skill[0..9]=="secondhand" ) best_str = ob->weight() / 250;
    else best_str = ob->weight() / 500;

    if( str - best_str > 10 )
	write("�o" + ob->query("unit") + ob->name()
		+ "���b��̻����ƪ��A���O�Q���X��C\n");
    else if( str - best_str > 5 )
	write("�o" + ob->query("unit") + ob->name()
		+ "��A�ӻ����ǻ��F�A�ϰʰ_��ı�o������b�C\n");
    else if( str - best_str > -1 )
	write("�o" + ob->query("unit") + ob->name()
		+ "�����q��A�ӻ����n�A�۷�X��C\n");
    else if( str - best_str > -2 )
	write("�o" + ob->query("unit") + ob->name()
		+ "�����q���F�I�A���L�A�j�j�ϱo�ʡC\n");
    else if( userp(me) )
	return notify_fail("�o" + ob->query("unit") + ob->name()
		+ "��A�ӻ��ӭ��F�A�A�ڥ������ʳo��I�����L�b�C\n");

    weapon = me->query_temp("weapon");
    if( !mapp(weapon) || !sizeof(sk = keys(weapon)) ) return 1;

    if( sizeof(sk) >= 2 )
	return notify_fail("�A�����ⳣ�S���ťi�H�˳Ƴo�ӪZ���C\n");
    if( skill[0..8]=="twohanded" )
	return notify_fail(ob->name() + "�ݭn����C\n");
    if( sizeof(sk)==1 ) {
	if( sk[0][0..8]=="twohanded" )
	    return notify_fail("�A���b�ϥλݭn���⪺�Z���C\n");
	if( sk[0][0..9] !="secondhand" && skill[0..9]!="secondhand" )
	    return notify_fail("�ϥΨ��H�W���Z���������@�D�@�ơC\n");
	if( me->query_temp("armor/shield") )    
	    return notify_fail("�A�����ⳣ�S���ťi�H�˳Ƴo�ӪZ���C\n");
    }
        
    return 1;
}

// valid_wear()
//
// This function determines if a character can wear an armor on certain
// body part. You shuold check if the character of this race DO HAVE that
// body part and didn't wear another armor on the same body part.

int valid_wear(object me, object ob, string part)
{
    if( me->query_temp("armor/" + part) )
	return notify_fail("�A�w�g�����P�����@��F�C\n");

    if( member_array(part, wear_type) == -1 )
	return notify_fail("�A��������o�@���@��C\n");

    return 1;
}

// statistic_destroyed()
//
// This function is called when the character of this race is physically
// damaged in any of his statistics. The most representive example is to
// check if the character is about to die.

int
statistic_destroyed(object ob, mapping flag)
{

    if( flag["gin"] ) {
	if( ob->query_stat_maximum("gin") > ob->query_attr("dex") )
	    ob->advance_stat("gin", -1);
	ob->heal_stat("gin", ob->query_attr("dex"));
    }

    if( flag["kee"] ) {
	if( ob->query_stat_maximum("kee") > ob->query_attr("con") )
	    ob->advance_stat("kee", -1);
	ob->heal_stat("kee", ob->query_attr("con"));
    }

    if( flag["sen"] ) {
	if( ob->query_stat_maximum("sen") > ob->query_attr("spi") )
	    ob->advance_stat("sen", -1);
	ob->heal_stat("sen", ob->query_attr("spi"));
    }

    if( flag["gin"] || flag["kee"] || flag["sen"] )
	ob->unconcious();

    return 1;
}

// statistic_exhausted()
//
// This function is called when the character of this race has exhausted
// any of his statistics. The most representive example is to check if the
// character is about to fall unconcious.

int
statistic_exhausted(object ob, mapping flag)
{
    object killer,ob1;

    killer = ob->last_damage_giver();
    if( ! killer ) killer = ob;

    // Dying
    // Note: this should be checked first bcz character often fall unconcious
    // and die at the same heart beat.
    if( flag["HP"] )
    {
	ob->die();
	if( !userp(ob) ) {
	    destruct(ob);
	    return 1;
	}
	switch( ob->query("life_form") )
	{
	case "ghost":
	    log_file("GHOST_DIE",
		sprintf("[%s] %s destroyed by %s\n",
			ctime(time()), ob->short(1), killer->short(1)));
	    CHAR_D->make_mist(ob);
	    break;
	case "living":
	    log_file("PLAYER_DIE",
		sprintf("[%s] %s killed by %s\n",
			ctime(time()), ob->short(1), killer->short(1)));
	    CHAR_D->make_ghost(ob);
	    break;
	}
	return 1;
    }

    // Unconcious
    if( flag["gin"] || flag["kee"] || flag["sen"] ) {
	ob->unconcious();
	ob->supplement_stat("gin", ob->query_attr("dex"));
	ob->supplement_stat("kee", ob->query_attr("con"));
	ob->supplement_stat("sen", ob->query_attr("spi"));
	return 1;
    }

    // Starving and thirsting
    if( flag["food"] ) {
	map_delete( flag, "food" );
	ob->consume_stat("kee", 1);
	tell_object(ob,
	    HIR "�A�w�g�j�o�Ⲵ����A�|�ϵL�O�F�A�̦n���I�F��ӦY�C\n" NOR);
    }
    if( flag["water"] ) {
	map_delete( flag, "water" );
	ob->consume_stat("kee", 1);
	tell_object(ob,
	    HIR "�Aı�o�f������A�}�l�X�{������{�H�F�A�̦n���I���ܡC\n" NOR);
    }
    if( flag["fatigue"] ) map_delete(flag, "fatigue");

    return sizeof(flag)==0;
}
