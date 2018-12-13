/*  combat.c - the combat ability feature

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <attack.h>
#include <dbase.h>
#include <score.h>
#include <skill.h>
#include <statistic.h>
#include <combat.h>

static string combat_message = "";

void set_combat_message(string s) { combat_message = s; }
void add_combat_message(string s) { combat_message += s; }
string get_combat_message() { return combat_message; }

varargs int query_attr(string,int);

// query_strength()
//
// This function returns the strength an character can bestow on specific
// application in the UNIT OF GRAM. Currently the default definition 
// implements a convert based on human attributes. Human strength ranged
// from 13 to 18, yielding the strength range from 16.9 kg to 32.4 kg.

int query_strength(string application)
{
    if( !living(this_object()) ) return 0;
    switch(application) {
    case "attack":	// Strength to perform an attack.
	return query_attr("str") * query_attr("cor") * 150
		+ query_stat("kee") * 30;
    case "defense":	// Strength to defense against attack.
	return query_attr("str") * query_attr("cps") * 150
		+ query_stat("kee") * 30;
    case "magic":	// Strength of magic power
	return query_attr("spi") * query_attr("spi") * 150
		+ query_stat("sen") * 30;
    case "spell":	// Strength of spell power
	return query_attr("wis") * query_attr("wis") * 150
		+ query_stat("sen") * 30;
    case "carriage":	// Strength to carry items.
	return query_attr("str") * query_attr("str") * 200;
    default:
	return 0;
    }
}

// query_ability()
//
// This function returns the ability measurement of the character's specific
// ability. Currently the value of ability had been adjusted to fit the skill
// system that with 100 as regular-maximum. Under this asumption, a human's
// natural attack ability ranges from 21 to 70 (an ultimate wimpy in dying
// status versus an top ace in perfect condition) in the UNIT OF SKILL LEVEL.

int query_ability(string application)
{
    if( !living(this_object()) ) return 0;

    switch(application) {

    /* attack :
     *
     * ����������򥻧ޥ��ȡC
     */
    case "attack":
	return query_attr("dex") * query_attr("cor") / 10
		+ (query_stat("gin") >> 5)
		+ query_temp("apply/attack");

    /* defense :
     *
     * �����������򥻨��m�ȡC
     */
    case "defense":
	return query_attr("dex") * query_attr("cps") / 10
		+ (query_stat("gin") >> 5)
		+ query_temp("apply/defense");

    /* intimidate:
     *
     * ��յ��šC
     */
    case "intimidate":
	return query_attr("cor") * query_attr("str") / 10
		+ (query_stat("kee") >> 5)
		+ query_temp("apply/intimidate");

    /* wittiness:
     *
     * �u�յ��šC
     */
    case "wittiness":
	return query_attr("cps") * query_attr("wis") / 10
		+ (query_stat("kee") >> 4)
		+ query_temp("apply/wittiness");

    /* magic:
     *
     * �]�O�C
     */
    case "magic":
	return query_attr("spi") * query_attr("int") / 10
		+ (query_stat("sen") >> 5)
		+ query_temp("apply/magic");

    /* spell:
     *
     * �k�O�C
     */
    case "spell":
	return query_attr("spi") * query_attr("wis") / 10
		+ (query_stat("sen") >> 5)
		+ query_temp("apply/spell");

    case "move":
	return query_attr("str") * query_attr("dex") / 10
		+ (query_stat("gin") >> 5)
		+ query_temp("apply/move");

    /* awarness:
     *
     * �����èƪ����P���O�C
     */
    case "awarness":
	return query_attr("cps") * query_attr("spi") / 10
		+ (query_stat("gin") >> 4)
		+ query_temp("apply/awarness");

    case "cauterization":
	return query_attr("cor") * query_attr("wis") / 10
		+ query_stat("gin") / 40;
    default:
	return query_skill(application);
    }
}

/*
 * int defend(int ability, int strength, object from)
 *
 * �o�Ө�Ʃw�q�@�ӤH�����u���m�v��O�C
 *
 * ��H������Y�ا������ɭԡA���өI�s�o�Ө�����H�������m�����|�C
 * ability �� strength ���O�y�z�o�ӧ������ޥ��ʤαj�סAfrom ��ܳo�ӧ���
 * �ҨϥΪ�����A�i��O�t�@�ӤH���B�Z���B�]�k�ޯ൥�C
 *
 * defend �Y�Ǧ^�@�ӫD 0 ���ƭȡA��ܳo�ӧ����Q���\�a���m��A�o��������
 * ���ӵL�ġC�Y�Ǧ^ 0 ��ܳo�ӤH���L�k���m�A�Ψ��m���ѡC
 */

int defend(int ability, int strength, object from)
{
    string sk;
    int counter_ability, chance;

    if( !living(this_object()) ) return 0;

    switch(from->query("phase")) {
    case PHASE_MENTAL:
    case PHASE_ILLUSION:
    case PHASE_ELEMENTAL:
	counter_ability = query_ability("defense");
	break;
    case PHASE_PHYSICAL:
	counter_ability = query_ability("defense");
	if( (sk=skill_mapped("dodge")) )
	    counter_ability += SKILL_D(sk)->dodge_using(this_object(),
			ability, strength, from);
	break;
    default:	/* unknown phase */
	return 0;
    }

    chance = 50 + (ability - counter_ability) * 2;
    if( chance < 5 ) chance = 5;
    else if( chance > 95 ) chance = 95;
    return (random(100) > chance);
}

/*
 * int absorb(int ability, int strength, object from)
 *
 * �o�Ө�Ʃw�q�@�ӤH���u�Ө��v��������O�C
 * ability �� strength ��ܳo�ӧ������ޥ��ʤαj�סAfrom ��ܳo�ӧ����ҨϥΪ�
 * ����C
 *
 * absorb ���ӶǦ^�@�Ӿ�ƭȡA��ܦ��h�֧������j�׳Q�u�l���v�F�C
 */

int absorb(int ability, int strength, object from)
{
    string sk;

    /* ����û��l��������������Ҧ����O�D */
    if( query("life_form")=="ghost" ) {
	if( from->is_character() )
	    from->add_combat_message("���O�q$n���W��z�L�h�A");
	else if( environment(from) && environment(from)->is_character() )
	    environment(from)->add_combat_message("���O$w�q$n���W��z�L�h�A");
	return strength;
    }

    /* ����O�D�]�û��Q�����l�� */
    if( from->is_character() && from->query("life_form")=="ghost" ) {
	from->add_combat_message("���O���i$n������A");
	return strength;
    }

    if( !living(this_object()) ) return 0;

    if( (sk=skill_mapped("parry")) )
	return SKILL_D(sk)->parry_using(
	    this_object(), ability, strength, from);

    return 0;
}

// inflict_damage()
//
// This is the default function to inflict damage when unarmed. (If armed
// with weapon(s), the inflict_damage() in weapon object is called instead)
// For more information about the task of this function, see F_EQUIP for
// the comments of inflict_damage().

int inflict_damage(int strength, object victim)
{
    int damage;
    string force_sk;

    // If we are not living, make no damage.
    if( !living(this_object()) ) return 0;

    // Convert strength to damage. If we are using force, use force formula.
    // Otherwise use default.
    force_sk = skill_mapped("force");

    // If using force, call force skill to inflict damage
    if( force_sk ) {
	damage = SKILL_D(force_sk)->inflict_damage(strength, victim);

	// Call default force skill in case the special force doesn't define
	// inflict_damage()
	if( ! damage && force_sk != "force" )
	    damage = SKILL_D("force")->inflict_damage(strength, victim);

	return damage;
    }

    damage = 1 + strength/10000 + random(strength/10000);
    damage += query_temp("apply/damage");

    // Call victim to resist this.
    damage -= victim->resist_damage(damage, this_object());

    return damage > 0 ? victim->receive_damage(damage, this_object(), this_object()) : 0;
}

// resist_damage()
//
// This function returns the non-initiative defense against all physical
// damage to this object. 

int resist_damage(int damage, object from_ob)
{
    return query_temp("apply/armor");
}

// receive_damage()
//
// This function does actual damage on this object and return the actual
// number of damage received. Note that this function is for 'game system
// abstraction' reason and ANY DEFENSE should be defined in resist_damage
// instead. One example application  of this function is to convert hp/mp
// statistics system into gin/kee/sen statistic system.

varargs int
receive_damage(int damage, object from, object attacker)
{
    int max, kill_mode = 0;
    mapping flag;
    string from_type;

    if( damage < 1 ) return 0;
    if( !living(this_object()) ) damage *= 10;

    kill_mode = objectp(attacker) ? attacker->is_killing(this_object()) : 0;
    from_type = objectp(from) ? from->query("material") : "unknown";

    // Damage this character according the life form it is in.
    // Currently the default form is living, which is, damage kee.
    switch( query("life_form") ) {
    case "ghost":
	consume_stat("gin", damage, attacker);

	if( kill_mode )
	{
	    if( living(this_object()) ) {
		/* ����H��O�@�ۤv */
		max = query_stat_effective("gin");
		if( random(max/3) < damage ) {
		    damage_stat("gin", damage, attacker);
		}

		/* �p�G�ˮ`�O�M��V����A�h�ˮ`���骺���|�V�� */
		if( random(query_stat("gin")) < damage )
		    consume_stat("HP", random(damage)+1, attacker);
	    } else {
		/* �H���e���g���A�ɡA�����ѧ���Ө��Ҧ��ˮ` */
		consume_stat("HP", damage, attacker);
	    }
	}
	break;
    case "living":
    default:
	/* ���Ӯ�O */
	consume_stat("kee", damage, attacker);

	/* �u�� kill �Ҧ��~�|���� */
	if( kill_mode )
	{
	    if( living(this_object()) ) {
		/* �𪺧@�ΡG�O�@�H�������ˮ`�A�ҥH��𪺪��A�ȶV����
		 * ���˪����|�V�C�A�Ϥ��V���C
		 */
		max = query_stat_effective("kee");
		if( random(max/3) < damage ) {
		    damage_stat("kee", damage, attacker);
		    gain_score("survive", damage);
		}

		/* �p�G�ˮ`�O�M��V����A�h�ˮ`���骺���|�V�� */
		if( random(query_stat("kee")) < damage )
		    consume_stat("HP", random(damage)+1, attacker);
	    } else {
		/* �H���e���g���A�ɡA�����ѧ���Ө��Ҧ��ˮ` */
		consume_stat("HP", damage, attacker);
	    }
	}
	break;
    }

    // Quick recover of character, occurs on the following condition:
    //
    // 1. Attacker is not killing this character.
    // 2. This character is not killing ANYONE.
    //    (And nobody is killing this character, however, this costs too much
    //    code to check, so let give it a chance in next turn.)
    // 3. This character is exhausting in next turn.
    //
    if(	!kill_mode 
    &&	!is_killing()
    &&	mapp(flag = query_exhausted())
    &&	(flag["gin"] || flag["kee"] || flag["sen"] || flag["HP"]) )
    {
        string stat;
        object ob;

	// fix all exhausted stats to zero.
        foreach(stat, ob in flag)
            set_stat_current(stat, 1);

	clear_statistic_flags();

        // ask all enemy to stop, they've done enough.
        remove_all_enemy();

        call_out("lose_fight", 0, attacker);
        return damage;
    }

    return damage;
}

