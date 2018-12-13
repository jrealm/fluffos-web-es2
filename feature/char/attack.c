/*  attack.c - the attack routines

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
#include <name.h>
#include <origin.h>
#include <skill.h>

#define MAX_OPPONENT    4

static object charge_target = 0;
static object guarding = 0, *guarded = ({});
static object *enemy = ({});
static mapping killer = ([]);
static int attack_patience;

static object current_target;

void fight_ob(object ob);
void kill_ob(object ob);

void add_guard(object who);
void remove_guard(object who);
object* wake_guard(object enemy);
void activate_guard(object enemy);
void guard_ob(object target);

object *query_enemy() { return enemy; }
mapping query_killer() { return killer; }
object query_charging() { return charge_target; }
object query_guarding() { return guarding; }
object query_opponent() { return current_target; }

varargs int is_fighting(object ob)
{
    return ob ? (member_array(ob, enemy) >= 0) : sizeof(enemy);
}

varargs int is_killing(mixed id)
{
    if( !killer ) return 0;
    if( !id ) return sizeof(killer);

    if( objectp(id) && userp(id) ) id = id->query("id");

    if( stringp(id) || objectp(id) )
	return !undefinedp(killer[id]);

    return 0;
}

// add_guard()
//
// Let someone guard us when another one try to kill us.

void add_guard(object ob)
{
    if( member_array(ob, guarded) >= 0 ) return;

    tell_object(this_object(), HIY + ob->name() + "�}�l�O�@�A�C\n" NOR);
    guarded += ({ ob });
}

// remove_guard()
//
// Remove someone who is not guarding us any more.

void remove_guard(object ob)
{
    if( member_array(ob, guarded) < 0 ) return;

    guarded -= ({ ob, 0 });
    tell_object(this_object(), HIY + ob->name() + "���A�O�@�A�F�C\n"+ 
	NOR);
}

// wake_guard()
//
// This function returns awaken guards that is not yet fighting specific
// enemy. Visibility of enemy and presence of guard is also checked.

object *wake_guard(object target)
{
    return filter(guarded, (:
	objectp($1)
	&& living($1)
	&& environment($1)==environment()
	&& (!$1->is_fighting($(target)))
	&& $(target)->visible($1) :),
    );
}

// activate_guard()
//
// Activate guarding action upon specific target. Default action is to fight
// target.

void activate_guard(object target)
{
    fight_ob(target);
}

// guard_ob()
//
// Set this character to guard someone. guard_ob(0) to clear guarding status.

void
guard_ob(object ob)
{
    if( objectp(guarding) && (guarding != ob) ) {
	tell_object(guarding, HIY + name() + "���A�O�@�A�F�C\n" NOR);
	guarding->remove_guard(this_object());
    }

    guarding = ob;
    if( objectp(ob) ) ob->add_guard(this_object());
}

// fight_ob()
//
// Start fighting someone.

void fight_ob(object ob)
{
    object *guard;

    // Check the target if it is valid and at the same room with us.
    if( !objectp(ob)
    ||	ob==this_object()
    ||	environment(ob) != environment())
	return;

    // If we are to fight the one we are guarding, then stop guarding before
    // we fight.
    if( ob==guarding ) guard_ob(0);

    // Start heart beating.
    set_heart_beat(1);

    // Insert the target to the first attack target.
    if( member_array(ob, enemy)==-1 )
	enemy += ({ ob });

    // Check if any characters is guarding the target, and let them join
    // the fight.
    guard = ob->wake_guard(this_object());
    if( sizeof(guard) ) {
	message("system", HIY + ob->name() + "���D�������I�A�W�e�U�ԡI\n" NOR, guard);
	guard->activate_guard(this_object());
	enemy += guard;
    }
}

// kill_ob()
//
// This function starts killing between this_object() and ob

void kill_ob(object ob)
{
    if( userp(ob) ) {
	if( living(ob) && undefinedp(killer[ob->query("id")]) )
	    tell_object(ob, HIR "�ݰ_��" + this_object()->name() + "�Q�����A�T\n" NOR);
	killer[ob->query("id")] = time();
    }
    else
	killer[ob] = time();

    // Remove dead npc killers, but player killer remains.
    killer = filter(killer, (: stringp($1) || objectp($1) :));

    // Start the fight.
    fight_ob(ob);
}

// charge_ob()
//
// This function promotes ob to the first target to attack.
void
charge_ob(object ob)
{
    if( ! ob ) { charge_target = 0; return; }

    if( member_array(ob, enemy) < 0 ) enemy += ({ ob });
    tell_object(this_object(),
	HIY "�A�}�l�N" + ob->name() + "�����n�����ؼСI\n" NOR);
    charge_target = ob;
}

// remove_enemy()
//
// Stop fighting specific object. (Might fight again on next encounter)
int remove_enemy(object ob)
{
    if( is_killing(ob) ) return 0;
    enemy -= ({ ob });
    return 1;
}

// remove_killer()
//
// Stop fighting specific object no matter if he is a killer or not.

void remove_killer(object ob)
{
    map_delete(killer, userp(ob) ? ob->query("id") : ob);
    remove_enemy(ob);
}

// remove_charge()
//
// Stop charging specific object;

int remove_charge()
{
    charge_target = 0;
}

// remove_all_enemy()
//
// Stop all fighting, but killer remains.

void remove_all_enemy()
{
    enemy = filter(enemy,
	(: objectp($1) && $1->remove_enemy($(this_object()))==0 :));
}

// remove_all_killer()
//
// Remove all enemies at once, killer or not.

void remove_all_killer()
{
    object ob;

    // We MUST stop killing anyone before asking them to forget us.
    killer = ([]);
        
    // Call all enemies seeing we die stop killing us. They have done enough.
    enemy->remove_killer(this_object());
    enemy = ({});
}

/* clean_up_enemy()
 *
 * �o�Ө�ƥΨӱN�w�g�S���԰���O���ĤH�۾԰���H���簣�A�Ǧ^�Ȧp�G�j�� 0
 * ��ܩ|���ĤH�C
 */
int
clean_up_enemy()
{
    enemy = filter(enemy, (:
	objectp($1)
	&& (environment($1)==environment())
	&& (living($1) || is_killing($1))
    :) );

    return sizeof(enemy);
}

/* select_opponent()
 *
 * �o�Ө�ƥΨӬ��H����ܤ@�ӧ�����H�C
 */

private object
select_opponent()
{
    object opp;
    int which, intimidate, wittiness, chance;

    if( !arrayp(enemy) || !sizeof(enemy) ) return 0;

    /* �����ɦV = ��յ��� + ���ݫY�� */
    intimidate = this_object()->query_ability("intimidate") + attack_patience;

    /* �p�G�����n�����ؼСA�u���Ҽ{�o�ӥؼ� */
    if( charge_target && member_array(charge_target, enemy) >= 0 ) {
	intimidate += intimidate / 5;	// charge �������ĪG
	opp = charge_target;
    } else
	opp = enemy[random(sizeof(enemy))];

    /* �u�յ��� */
    if( living(opp) ) {
	wittiness = opp->query_ability("wittiness");
	if( opp->query_charging() )
	    wittiness -= wittiness / 3;	// charge ���t���ĪG
    }
    else wittiness = 0;

    if( ! wittiness ) return opp;
    chance = 50 + (intimidate - wittiness) * 2;

    /* �N�o�ʧ��������|���w�b 20% �� 80% ���� */
    if( chance < 20 ) chance = 20;
    else if( chance > 80 ) chance = 80;

    /* �o�ʧ����I�M�����ݫY�� */
    if( random(100) < chance ) {
	attack_patience = 0;
	return opp;
    }

    /* ��դ����A�֥[���ݫY�� */
    attack_patience += intimidate / 10;
    return 0;
}

/* attack()
 *
 * �o�Ө�O�Ψӱ���H���C�^�X���԰��G�ϥΪZ���ޯ�ή{��i���ޯ�����C
 */

varargs int
attack(object opponent)
{
    string skill;
    mapping wielded_weapon;

    if( !living(this_object()) ) return 0;

    /* �Y�S�����w�ؼСA�h��w�@�ӥؼСC�@��Ө����w�ؼЪ��I�s�覡�O��
     * �S��ޯ�Ϊ��A�S�����w�ؼЪ��覡�O�� heart_beat �Ϊ��C
     */
    if( !objectp(opponent) )
        opponent = select_opponent();

    if( opponent ) current_target = opponent;

    wielded_weapon = query_temp("weapon");
    if( mapp(wielded_weapon) && sizeof(wielded_weapon) )
    {
	object weapon;
	string art;

	// Attack with each of our weapons.
	foreach(skill, weapon in wielded_weapon) {
	    art = skill_mapped(skill);
	    if( ! art ) continue;
	    weapon->attack_with( this_object(), opponent, art );
	}
    } else {
	// Or, attack with unarmed.
	skill = skill_mapped("unarmed");
	if( skill )
	    SKILL_D(skill)->attack_using(this_object(), opponent, skill);
    }

    return 1;
}

// init()

void init()
{
// �o��check���G�P/adm/daemon/combatd.c�ح���, �y���@�ǲ��`
//   �������� -Dragoon
//    /* �Y�o�Ӫ���Q���ʨ�D�԰ϡA�h���޵o�԰��C */
//  if(	environment() && environment()->query("no_fight") ) return;
//
    /* �Y this_player() �ݤ����o�ӤH���A�h���޵o�԰��C */
    if( ! this_object()->visible(this_player()) ) return;

    /* �Y���西���ۤ������A�}�l�԰��C */
    if( this_player()->is_killing(query("id")) ) {
	COMBAT_D->auto_fight(this_player(), this_object(), "hatred");
	return;
    }

    /* �Y���観�a�ڤ���A�h�}�l�԰��C */
    if( this_player()->query("vendetta/" + query("vendetta_mark")) ) {
	COMBAT_D->auto_fight(this_player(), this_object(), "vendetta");
	return;
    }

    switch( query("attitude") )
    {
    case "aggressive":
	/* �D�ʧ������ͪ� */
	COMBAT_D->auto_fight(this_object(), this_player(), "aggressive");
	break;
    case "peaceful":
    default:
	break;
    }
}
