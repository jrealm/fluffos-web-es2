/*  chard.c - protected character operation daemon

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#pragma save_binary

#include <login.h>
#include <statistic.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

// setup_char()
//
// This function is called when characters need setup (after create() is
// called). The major task of this function is to keep consistency of
// user data and NPCs. Because the game system may change with development
// of mudlib, there might be minor or major changes in creating character
// objects. Also, this function serves as default creation function of 
// NPCs that saves wizards' work on initializing NPCs.

/*  setup()
 *
 *  �@��ʪ��H���]�w��ơC�o�Ө�ƥΨӹ�H�����󰵤@�Ǫ�l�ƪ��]�w�C
 */
void
setup_char(object ob)
{
    mapping apply;

    /* �p�G�H���S���]�w�رڡB¾�~�B���šA���@�ӹw�]�� */
    if( !ob->query_race() )	ob->set_race("human");
    if( !ob->query_class() )	ob->set_class("commoner");
    if( !ob->query_level() )	ob->set_level(1);

    ob->init_statistic();
    ob->init_attribute();

    /* ��l�ƤH�����Ȯɪ��A */
    if( mapp(apply = ob->query("perm_apply") ) )
	ob->set_temp("apply", copy(apply));
    else
	ob->set_temp("apply", ([]));

    /* �H��������j���סA�Ѯڰ��M�w */
    ob->set_stat_maximum("HP", ob->query_attr("con") * 5);
    ob->set_stat_regenerate("HP", TYPE_HEALTH);

    /* �H�����h�ҧԨ��� */
    ob->set_stat_maximum("fatigue", 100);
    ob->set_stat_effective("fatigue", 100);
    if( ! ob->query_stat_current("fatigue") )
	ob->set_stat_current("fatigue", 0);
    ob->set_stat_regenerate("fatigue", TYPE_WASTING);

    /* �w��H�����ͩR���A(life_form)�A����t�ιw�]���]�w */
    switch(ob->query("life_form"))
    {
    case "ghost":	/* ����A */
	ob->set_temp("apply/vision_of_ghost", 1);
	ob->delete_stat("kee");
	ob->delete_stat("food");
	ob->delete_stat("water");
	ob->set_stat_regenerate("gin", TYPE_WASTING);
	ob->set_stat_regenerate("sen", TYPE_WASTING);
	break;
    case "undead":	/* �����ͪ����A */
	ob->set_temp("apply/vision_of_ghost", 1);
	ob->delete_stat("sen");
	ob->set_stat_regenerate("gin", TYPE_HEALTH);
	ob->set_stat_regenerate("kee", TYPE_HEALTH);
	ob->set_stat_regenerate("food", TYPE_WASTING);
	ob->set_stat_regenerate("water", TYPE_WASTING);
	break;
    case "living":	/* �ͪ����A */
    default:
	ob->set_stat_regenerate("gin", TYPE_HEALTH);
	ob->set_stat_regenerate("kee", TYPE_HEALTH);
	ob->set_stat_regenerate("sen", TYPE_HEALTH);
	ob->set_stat_regenerate("food", TYPE_WASTING);
	ob->set_stat_regenerate("water", TYPE_WASTING);
	break;
    }

    /* �Ův���ݭn�����M���� */
    if( wizardp(ob) ) {
	ob->set_stat_regenerate("food", TYPE_STATIC);
	ob->set_stat_regenerate("water", TYPE_STATIC);
    }

    /* ����رڤ�¾�~����l�ơA�رکM¾�~����i�H�ק�e����l�ƹL���ݩʡC*/
    RACE_D(ob->query_race())->setup(ob);
    CLASS_D(ob->query_class())->setup(ob);
    ob->add_path("/daemon/race/" + ob->query_race() + "/");
    ob->add_path("/daemon/class/" + ob->query_class() + "/");
}

varargs object
make_corpse(object victim, object killer)
{
    int i, k, negative_fame, killer_rep, killer_fame;
    object corpse, inv, police1, police2;
    string corpse_ob;
    mapping bounty;
    string score;
    int amount;

    // Wizards never leave a corpse.
    if( wizardp(victim) ) return 0;

    // Notify inventory item to save data if nessessary.
    all_inventory(victim)->owner_is_killed(killer);

    // Check life form.
    switch( victim->query("life_form") )
    {
    case "ghost":
	message("vision", victim->name() + "�Ʀ��@�}�ϡA�����F ...\n",
	    environment(victim), victim);
	return 0;
    case "living":
    default:
        all_inventory()->add("sinister", 1);
    }

    // Check if using custom corpse object.
    corpse_ob = victim->query("corpse_ob");
    if( !corpse_ob ) corpse_ob = CORPSE_OB;

    seteuid(MUDLIB_UID);
    catch(corpse = new(corpse_ob));
    seteuid(getuid());

    corpse->set_name( victim->name(1) + "������",
	"corpse of " + capitalize(victim->query("id")), "corpse" );
    corpse->set("long", victim->long()
	+ "�M�ӡM" + gender_pronoun(victim->query("gender")) 
	+ "�w�g���F�M�u�ѤU�@������R�R�a���b�o�̡C\n");
    corpse->set("age", victim->query("age"));
    corpse->set("gender", victim->query("gender"));
    corpse->set("victim_name", victim->name(1));

    // Relate victim with hir corpse.
    victim->set_temp("corpse", corpse);

    corpse->set_weight( victim->query_weight() );
    corpse->set_max_encumbrance( victim->query_max_encumbrance() );
    corpse->move(environment(victim));
    // change decay time 300 -> 90 -Dragoon
    corpse->start_decay( userp(victim) ? 90 : 60 );

    // Transfer inventory into corpse.
    foreach(inv in all_inventory(victim))
	inv->move(corpse);
        
    if( !killer ) killer = victim->last_damage_giver();

    // Handle the killer.
    if( objectp(killer) ) {
	// PK gains mortal sin scores.
	if( userp(victim) && userp(killer) && victim != killer
	&& (victim->query_level() > 1) ) {
	    killer->gain_score("mortal sin",
		victim->query_level() * victim->query_level() * 10);
	    // �p�G�Q�`�H����}�n, ���H�̧�l�ۨ��n��ΪZ�L�n��, ���H��
	    // �Y�O�p��, �h���W�¹D�n�� -dragoon
	    negative_fame = victim->query_score("reputation") + 
		victim->query_level() * victim->query_level() -
		victim->query_score("mortal sin") / 15;

	    if( negative_fame > 0 ) {
		killer_rep = killer->query_score("reputation");
		killer_fame = killer->query_score("martial fame");
		k = random(negative_fame);
		// ���n��
	        if( killer_rep > k ) 
		    killer->gain_score("reputation", -k);
		else killer->gain_score("reputation", -killer_rep);
		// ���Z�L�n��
		if( killer_fame > 0 ) {
		    if( killer_fame > k/10 )
			killer->gain_score("martial fame", -k/10);
		    else killer->gain_score("martial fame", -killer_fame);
		}
		// �p�����W�¹D�n��
		if( killer->query("class") == "thief" )
		    killer->gain_score("negative fame", k/10);
	    }
	}

	// if pker die, delete mark about pker -dragoon
	if( victim->query("last_pk_time")
	|| victim->query("pker")
	|| victim->query("pk_record") ) {
	    victim->delete("last_pk_time");
	    victim->delete("pker");
	    victim->delete("pk_record");
	}
	// set marks on PKer -dragoon
	if( userp(killer) && userp(victim) ) {
            // �Y�O���H�����L�H, �B�ɶ��֩�Y�q�ɶ�, �h�O���W�[�@��, �_�h, 
	    // �K���]�ɶ��O��
	    // �[�W�]��: ����lv>1�~�|�W�[, �H�������S�𶤥H�t���覡 pk
            if( killer->query("last_pk_time")
            && time() - (int)killer->query("last_pk_time") < 60 * 60 ) {
		if( victim->query("level") > 1 )
		    killer->add("pk_record", 1); }
            else {  killer->set("pk_record", 1); }
	    // �]�W�̪�@�����H���ɶ�
            killer->set("last_pk_time", time());
	    // ���H�ư���3�}�l�����|�X�{���Y, �t�~�[�W�v�w����
	    // �ثe�]�w: �v�w���q, �R�׵o�ͦ��T�����v�X�{���Y
	    if( killer->query("pk_record") > 3 + random(12) 
	    && random(10) > 6 ) {
		if( killer->query("pk_record") > 15 + random(10) ) {
		    write("��Ӯ��Y������ť���G�s�A���t���b�F�L��!!\n");
		    police1 = new("/d/domain/npc/police_leader");
		    police1->move(environment(killer)); }
		else write("���Y������ť���G�s�A���t���b�F�L��!!\n");
		police2 = new("/d/domain/npc/police");
		police2->move(environment(killer));
	    }		
	}

	// Register vendetta marks if any.
	if( victim->query("vendetta_mark") )
	    killer->add("vendetta/" + victim->query("vendetta_mark"), 1);

	// Killing humanoid creatures adds kills statistic
	if( victim->query("humanoid") )
	    killer->gain_score("kills", 1);

	// Gain other bounty if any.
	if( mapp(bounty = victim->query("bounty")) )
	    foreach(score, amount in bounty)
		killer->gain_score(score, amount);

	// Finally, let class daemon check this kill.
	CLASS_D(killer->query_class())->kill_check(killer, victim, corpse);
    }        

    return corpse;
}

int
make_mist(object victim)
{
    LOGIN_D->reincarnate(victim);
    return 1;
}

/*  �ͩR���A�ഫ�G�ͪ� -> ����
 */
int
make_ghost(object victim)
{
    object corpse;

    if( victim->query("life_form") != "living" )
	error("����u��ѥͪ��ഫ�Ӧ��C\n");

    corpse = victim->query_temp("corpse");
    victim->set("life_form", "ghost");
    victim->set("living", ([
	"kee" : victim->query_stat_maximum("kee"),
    ]));

    victim->supplement_stat("HP", 9999);
    victim->supplement_stat("gin", 9999);
    victim->supplement_stat("sen", 9999);
    victim->clear_statistic_flags();

    victim->clear_temp_dbase();
    victim->setup();

    /* ���s�]�w���骺�s���A�]�� clear_temp_dbase() �|�M�� */
    if( objectp(corpse) ) victim->set_temp("corpse", corpse);
    return 1;
}

int
make_living(object ob)
{
    object corpse;
    mapping living_stat;
    string stat;
    int max;

    living_stat = ob->query("living");
    corpse = ob->query_temp("corpse");

    /* ��_�ͪ����򥻼ƭ� */
    if( mapp(living_stat) )
	foreach(stat, max in living_stat) {
	    if( !corpse ) max -= max/10;
	    ob->set_stat_maximum(stat, max);
	    ob->set_stat_effective(stat, max);
	    ob->set_stat_current(stat, max);
	}

    ob->set("life_form", "living");
    ob->delete("living");

    ob->clear_temp_dbase();
    ob->setup();
    return 1;
}
