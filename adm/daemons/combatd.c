/*  combatd.c - combat arbitrator daemon

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

// MudOS v21.6 #pragma optimize's jump threading has bug! (line 200)
//#pragma optimize

#pragma save_binary

#include <ansi.h>
#include <combat.h>

//#define SHOW_DAMAGE
//#define SHOW_COMBAT_STAT

inherit F_CLEAN_UP;
inherit F_DBASE;

string *catch_hunt_msg = ({
    HIW "$N�M$n���H�ۨ����~�����A�ߨ襴�F�_�ӡT\n" NOR,
    HIW "$N���$n�j�ܡR�u�i�c�A�S�O�A�T�v\n" NOR,
    HIW "$N�M$n�@�I���A�G�ܤ����N���F�_�ӡT\n" NOR,
    HIW "$N�@���h��$n�A�u��v���@�n�ĤF�L�ӡT\n" NOR,
    HIW "$N�ܹD�R�u����T�O�]�v\n" NOR,
    HIW "$N�ܹD�R�u�ǩR�ӡT�v\n" NOR
});

string *dead_msg = ({
    "\n$N���F�C\n\n",
    "\n$N�R�X�X�f�A��A���z�F�X�U ... ���F�C\n\n",
    "\n$N�˪צb��y���A�L���y�X�A��A���ݬO�����F�C\n\n",
    "\n$N�D�u�F�X�n�A�y�X�@�f�A��A�K�_�F��C\n\n",
    "\n$N�w�b�a�W�A�L�O�a�ä�F�@�|��A�H�Y���h�C\n\n",
});

void create()
{
    seteuid(getuid());
    set("name", "�԰����F");
    set("id", "combatd");
}

string damage_msg(int damage, string type)
{
    string str;

    if( !type ) type = "�ˮ`";
#ifdef SHOW_DAMAGE
    return "���G�y�� " + damage + " �I" + type + "�C\n";
#else
    if( damage == -1 ) switch(type) {
    case "���":
        return "���G�u�y�v�a�@�n���ӥ��ۡC\n";
    case "�ζ�":
        return "���G�u��v�a�@�n��X�@�D�ʤf�C\n";
    case "���":
        return "���G�u�P�v�a�@�n��F�i�h�C\n";
    default:
        return "���G�����R��$n�C\n";
    }

    if( damage == 0 ) return "���G���G�S���y�����㪺�ˮ`�C\n";
    if( damage > 100 ) damage = 100;

    switch( type ) {
    case "����":
    case "�ζ�":
        if( damage < 5 ) return "���G�u�O�����a���}$p���֦סC\n";
        else if( damage < 10 ) return "���G�b$p$l���X�@�D�Ӫ����岪�C\n";
        else if( damage < 20 ) return "���G�u��v�a�@�n���X�@�D�ˤf�T\n";
        else if( damage < 40 ) return "���G�u��v�a�@�n���X�@�D��O�O���ˤf�T\n";
        else if( damage < 60 ) return "���G�u��v�a�@�n���X�@�D�S���S�`���ˤf�A�q�o$N���y�A��T\n";
        else return "���G�uť��$n�@�n�G�z�A$w�w�b$p$l���X�@�D�`�Ψ������i�ȶˤf�T�T\n";
        break;
    case "���":
        if( damage < 5 ) return "���G�u�O�����a��}$p���֦סC\n";
        else if( damage < 10 ) return "���G�b$p$l��X�@�ӳФf�C\n";
        else if( damage < 20 ) return "���G�u�P�v�a�@�n��J�F$n$l�o�\\�T\n";
        else if( damage < 40 ) return "���G�u�P�v�a�@�n��i$n��$l�A��$p���ѦۥD�a�h�F�X�B�T\n";
        else if( damage < 60 ) return "���G�u�P��v�a�@�n�A$w�w�b$p$l��X�@�Ӧ���U�k����]�K�T\n";
        else return "���G�uť��$n�@�n�G�z�A$w�w�b$p��$l���ӥX�A�A���q�o���a�T�T\n";
        break;
    case "���":
        if( damage < 2 ) return "���G�u�ԡv�a�@�n�����A�i�O���G�ˮ`���j�C\n";
        else if( damage < 5 ) return "���G�b$p��$l�y���@�B��C�C\n";
        else if( damage < 10 ) return "���G�@���R���A$n��$l�n�ɸ~�F�@���Ѱ��T\n";
        else if( damage < 20 ) return "���G�@���R���A$n�e��F�@�n��M�Y�F���p�����T\n";
        else if( damage < 40 ) return "���G�u�y�v�a�@�n�A$n�h�F��B�T\n";
        else if( damage < 60 ) return "���G�o�@�U�u�y�v�a�@�n���o$n�s�h�F�n�X�B�A�t�@�I�L�ˡT\n";
        return "���G�����a�����A$n�u�z�v�a�@�n�R�X�@�f�A��T\n";
        break;
    default:
        if( damage < 2 ) str =  "���G�u�O�j�j�y���@�B���L";
        else if( damage < 5 ) str = "���G�y�����L��";
        else if( damage < 10 ) str = "���G�y���@�B";
        else if( damage < 20 ) str = "���G�y���@�B�Y��";
        else if( damage < 30 ) str = "���G�y���ᬰ�Y����";
        else if( damage < 40 ) str = "���G�y���۷��Y����";
        else if( damage < 60 ) str = "���G�y���Q���Y����";
        else if( damage < 80 ) str = "���G�y�������Y����";
        else str =  "���G�y���D�`�i�Ȫ��Y��";
        return str + type + "�T\n";
    }
#endif
}

string eff_status_msg(int ratio)
{
    if( ratio==100 ) return HIG "( $N�ݰ_�ӨèS�����ˡC )\n" NOR;
    if( ratio > 95 ) return HIG "( $N���G���F�I���ˡA���L���q�~��ݤ��j�X�ӡC )\n" NOR;
    if( ratio > 90 ) return HIG "( $N�ݰ_�ӥi����F�I���ˡC )\n" NOR;
    if( ratio > 80 ) return HIY "( $N���F�X�B�ˡA���L���G�ä�ê�ơC )\n" NOR;
    if( ratio > 60 ) return HIY "( $N���ˤ����A�ݰ_�Ӫ��p�ä��Ӧn�C )\n" NOR;
    if( ratio > 40 ) return HIY "( $N�𮧲ʭ��A�ʧ@�}�l���áA�ݨөҨ����˵۹ꤣ���C )\n" NOR;
    if( ratio > 30 ) return HIY "( $N�w�g�˲��ֲ֡A���b�j�O�伵�ۤ��ˤU�h�C )\n" NOR;
    if( ratio > 20 ) return HIR "( $N���F�۷����ˡA�u�ȷ|���ͩR�M�I�C )\n" NOR;
    if( ratio > 10 ) return HIR "( $N�˭����U�w�g���H�伵�A���ݴN�n�˦b�a�W�C )\n" NOR;
    if( ratio > 5  ) return HIR "( $N���˹L���A�w�g�a�a�@���A�R�b���i�F�C )\n" NOR;
    return HIR "( $N���˹L���A�w�g���p��������A�H�ɳ��i���_��C )\n" NOR;
}

string status_msg(int ratio)
{
    if( ratio==100 ) return HIG "( $N�ݰ_�ӹ�o�ص{�ת������@�I�]���b�G�C )\n" NOR;
    if( ratio > 95 ) return HIG "( $N���G���ǯh�ΡA���]�\\�O���Ĥ��p�A�A�L�k�T�w�C )\n" NOR;
    if( ratio > 90 ) return HIG "( $N�ݰ_�ӥi�঳�ǲ֤F�A�X�۶}�l�C�F�U�ӡC )\n" NOR;
    if( ratio > 80 ) return HIY "( $N�ʧ@���G�}�l���I�����F���A���O���M���������C )\n" NOR;
    if( ratio > 60 ) return HIY "( $N��ݼN�N�A�ݰ_�Ӫ��p�ä��Ӧn�C )\n" NOR;
    if( ratio > 40 ) return HIY "( $N���G�Q���h�ΡA�ݨ���O�����Ӭ۷��Y���C )\n" NOR;
    if( ratio > 30 ) return HIY "( $N�w�g�@���Y���}�����ҼˡA���b�j�O�伵�ۤ��ˤU�h�C )\n" NOR;
    if( ratio > 20 ) return HIR "( $N�ݰ_�Ӥw�g�O���q�ߤF�C )\n" NOR;
    if( ratio > 10 ) return HIR "( $N�n�Y�̸��B�n�n�ױצa��������í�A���ݴN�n�˦b�a�W�C )\n" NOR;
    return HIR "( $N�w�g���J�b���g���A�A�H�ɳ��i��L�˷w�h�C )\n" NOR;
}

varargs void report_status(object ob, int effective)
{
    if( !ob->query_stat_maximum("kee") ) return;
    if( effective ) 
        message_vision( eff_status_msg(
            (int)ob->query_stat_effective("kee") * 100 / (int)ob->query_stat_maximum("kee") ), ob);
    else
        message_vision( status_msg(
            (int)ob->query_stat("kee") * 100 / (int)ob->query_stat_maximum("kee") ) , ob);
}

// fight()
//
// This function serves as a lowest level routine for combat system and
// is usually called from a daemon of combat skill such as unarmed, sword
// etc.

varargs int
fight(object me, object victim, string skill, mapping action, object weapon)
{
    int ability, strength, damage, gin_cost, force_bonus;
    string msg, force_skill;

    // �Y�b�D�԰�, �B�԰����賣�S�Qarrest, ����԰� -Dragoon
    // ����userp(me) check, mob�]���Ǧb�D�԰ϥX����� -dragoon
    if( environment(me)->query("no_fight") ) {
	if( !victim->query("unprotect_mark") 
	&& !me->query("unprotect_mark") ) return 0;
    }

    // �Y�԰���@�b�_�u, ��������԰� -Dragoon
    if( ( userp(me) && !interactive(me) ) 
    || ( userp(victim) && !interactive(victim) ) ) return 0;

    me->set_combat_message(action["action"]);
    me->set_temp("last_action", action);

    /* �O�D
     */
    strength = me->query_strength("attack");

    /* ���O��԰����v�T:
     *
     * �O�D�W�[: �ޯ� * �� * (�\�O�ʤ��� + �ۦ��Y��)% * 4
     *           => �ޯ� 100, �� 1000, �Q���\�O, �L�ۦ�, �|�W�[ 400Kg �O�D
     * �ݭn��: �ҼW�[�O�D / 500;
     * ���Ӻ�: �H��(1 �� 1 + �ҼW�[�O�D / 30000)
     */
    gin_cost = 1;
    if( force_skill = me->skill_mapped("force") )
    {
        int ratio, kee_required, kee;

        if( !(ratio = me->query("force_ratio")) ) ratio = 75;

        force_bonus = me->query_skill("force") * me->query_stat("kee") 
                * (ratio + action["force"]) / 25;
        kee_required = force_bonus / 500;

        if( userp(me) && kee_required > 0 ) {
            kee = me->query_stat("kee");
            if( kee < kee_required )
                force_bonus = force_bonus * kee / kee_required;
        }

        /* ��ϥΤ��\�A�H���C���\�O�ʤ���԰��ɡA�����| gin_cost = 0 */
        gin_cost = random(2 + force_bonus/30000);
    }

    /* �R���v: ������O + �����ޯ� + �ۦ��Y�� */
    ability = me->query_ability("attack")
        + me->query_skill(skill)
        + action["attack"]
        ;

    /* �Y������H������̩ҨϥΪ��ޯ�]���x�A�h�����R���v���t�������C */
    ability -= random( victim->query_skill(skill) );

    /* �Y������H�W�@�өۦ������m�ĪG�A�h�����R���v�v�T�C */
    ability -= victim->query_temp("last_action/defense");

    /* �����̮��Ӥֳ\��O�C */
    if( userp(me) ) {
        if( me->query_stat("gin") > gin_cost ) {
            me->consume_stat("gin", gin_cost);
            strength += force_bonus;
        } else {
            // ������̺�֩�n�D����O��, ���F���C������O, �t
            // �~���ݦ��� -Dragoon
            me->consume_stat("gin", gin_cost/2 + 1);
            ability /= 2;
            strength /= 2;
        }
    }
    else strength += force_bonus;

    if( ability < 1 ) ability = 1;

    /* �n�D������H�i�樾�m�C */
    me->set_temp("defend_message", 0);
    if( !victim->is_busy()
    &&  victim->defend(ability, strength, weapon ? weapon : me) )
    {
        string defend_msg;

        /* ���m���\�A�N���m���T���[�J�԰��T���C */
        defend_msg = me->query_temp("defend_message");
        me->add_combat_message( "�A" );
        me->add_combat_message( stringp(defend_msg) ? defend_msg
                : "���O�S��" );
        damage = -1;
    }
    else
    {
        string absorb_msg;

        /* ���m���ѡA����������H�l���O�D�����|�C */
        me->set_temp("absorb_message", 0);
        strength -= (int)victim->absorb(ability, strength,
                weapon ? weapon : me);
        absorb_msg = me->query_temp("absorb_message");
        me->add_combat_message( "�A" );
        me->add_combat_message( stringp(absorb_msg) ? absorb_msg
                : "���O�Q$n��}");

        /* �Y�O�D�������Q�l���A�h���Ͷˮ`�C */
        /* ���Ͷˮ`�A�h�������覡�����ּƺ���� -Dragoon */
        if( strength > 0 ) {
            if( weapon ) {
                damage = weapon->inflict_damage(strength, victim);
                me->gain_score("weapon mastery", random(me->query_attr("int")/3));
            } else {
                damage = me->inflict_damage(strength, victim);
                me->gain_score("unarmed mastery", random(me->query_attr("int")/3));
            }
        }
        else damage = 0;
    }

    /* �N�ˮ`�{�ת��T���[�J�԰��T���C */
    if( damage >= 0 ) {
#ifdef SHOW_DAMAGE
        me->add_combat_message("�A" + damage_msg( damage, action["damage_type"] ));
#else
        int max, percent;

        max = victim->query_stat_effective("kee");
        if( max ) percent = damage * 100 / max;
        else percent = -1;      /* �D�ͪ����ˮ`�T�� */
        me->add_combat_message("�A" + damage_msg( percent, action["damage_type"]));
#endif
    }
    else me->add_combat_message("�C\n");

#ifdef SHOW_COMBAT_STAT
    message_vision(sprintf(HIY "%s�������G[�ޥ� %d, �O�D %.2fkg]\n" NOR,
        me->name(), ability, strength / 1000.0), me);
#endif

    /* �e�X�԰��T���C */
    msg = me->get_combat_message();
    if( stringp(msg) )
    {
        string *limbs = victim->query("limbs");

        if( !arrayp(limbs) || !sizeof(limbs) ) {
            msg = replace_string(msg, "$l", "���W");
        } else {
            msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
        }
        if( weapon ) msg = replace_string(msg, "$w", weapon->name());

        message_vision( msg, me, victim);
        if( damage > 0 ) report_status(victim);
    }

    /* �Ǧ^�D�s��(�ˮ`�O)��ܧ����̥i��o�g�� */
    if( living(victim) ) {
        /* ���O�ͪ� */
        return damage;
    } else {
        /* ���O�D�ͪ��A�����̯�O�ݤp�� 80 �~�����|�o��g�� */
        // ability > 80 ������I�L�Y, �P���p�Uforce exp�o�L������
        // ������e�o�ت��]��, �ϥ�stake�w�g����F���h��m�쨺�@��
        // -Dragoon 
        return random(500) > ability ? damage : 0;
    }
}

// auto_fight()
//
// This function is to start an automatically fight. Currently this is
// used in "aggressive", "vendetta", "hatred", "berserk" fight.

void auto_fight(object me, object obj, string type)
{
    // Don't let NPC autofight NPC.
    if( !userp(me) && !userp(obj) ) return;

    // This call_out gives victim a chance to slip trough the fierce guys.
    call_out( "start_" + type, 0, me, obj);
}

// add check net connection of player, testing work or not -Dragoon
void
start_hatred(object me, object obj)
{
    if( !me || !obj ) return;   // Are we still alive(not becoming a corpse)?

    if( !living(me)                             // Are we capable for a fight?
    ||  (userp(obj) && !interactive(obj))       // Is player net dead?
    ||  environment(me)!=environment(obj)       // Are we still in the same room?
    ||  environment(me)->query("no_fight")      // Are we in a peace room?
    )   return;

    // We found our hatred! Charge!
    message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
    me->kill_ob(obj);
    if( userp(obj) ) obj->fight_ob(me);
    else obj->kill_ob(me);
    me->attack(obj);
}

void
start_vendetta(object me, object obj)
{
    if( !me || !obj ) return;   // Are we still exist( not becoming a corpse )?

    if( me->is_fighting(obj)    // Are we busy fighting?
    ||  !living(me)             // Are we capable for a fight?
    ||  (userp(obj) && !interactive(obj))       // Is player net dead?
    ||  environment(me)!=environment(obj)       // Are we still in the same room?
    ||  environment(me)->query("no_fight")      // Are we in a peace room?
    )   return;

    // We found our vendetta opponent! Charge!
    message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
    me->kill_ob(obj);
    if( userp(obj) ) obj->fight_ob(me);
    else obj->kill_ob(me);
    me->attack(obj);
}

void start_aggressive(object me, object obj)
{
    int def;

    if( !me || !obj ) return;   // Are we still exist( not becoming a corpse )?

    if( me->is_fighting()       // Are we busy fighting?
    ||  !living(me)             // Are we capable for a fight?
    ||  (userp(obj) && !interactive(obj))       // Is player net dead?
    ||  environment(me)!=environment(obj)       // Are we still in the same room?
    ||  environment(me)->query("no_fight")      // Are we in a peace room?
    ||  obj->query("life_form") == "ghost"	// Only kill living -Dragoon
    ||  me->query_stat("kee") < obj->query_stat("kee")
    )   return;

    // let cor, cps, and command: agg work -dragoon
    def = (int)me->query_attr("cps");
    if( me->query_temp("ashura/aggressive") < 1 )
	def += (int)me->query_attr("cps");
    if( random(me->query_attr("cor")) < def ) return;

    /* ������ù�ڹJ���L���a�ɡA�u����դ�ۤv�j�� */
//  �n���]�ϤF?? ������ -dragoon
//    if( userp(me) && userp(obj) 
//    && obj->query_ability("intimidate") > me->query_ability("intimidate") )
//        return;

    // We got a nice victim! Kill him/her/it!!!
    message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
    me->kill_ob(obj);
    if( userp(obj) ) obj->fight_ob(me);
    else obj->kill_ob(me);
    me->attack(obj);
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
    switch(event)
    {
    case "dead":
        message_vision( dead_msg[random(sizeof(dead_msg))], ob );
        break;
    case "unconcious":
        message_vision("\n$N�}�U�@�Ӥ�í�M�^�b�a�W�@�ʤ]���ʤF�C\n\n", ob);
        break;
    case "revive":
        message_vision("\n$N�C�C�C�}�����M�M���F�L�ӡC\n\n", ob);
        break;
    }
}

