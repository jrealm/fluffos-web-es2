/*  char.c - standard character body

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
#include <action.h>
#include <ansi.h>
#include <char.h>
#include <command.h>
#include <condition.h>
#include <dbase.h>
#include <move.h>
#include <name.h>
#include <skill.h>
#include <user.h>

inherit F_ACTION;
inherit F_ATTACK;
inherit F_ATTRIBUTE;
inherit F_COMBAT;
inherit F_COMMAND;
inherit F_CONDITION;
inherit F_DBASE;
inherit F_FINANCE;
inherit F_MESSAGE;
inherit F_MASTER;
inherit F_MOVE;
inherit F_NAME;
inherit F_SCORE;
inherit F_SKILL;
inherit F_STATISTIC;
inherit F_TEAM;

// variables

static int tick;

// implementations

int is_character() { return 1; }

/* setup()
 *
 * �o�Ө禡�Ψӧ����@�ӤH������l�ơA�ñҰʩҦ��H������i�H�������ƥ�A�]�A
 * �߸�(heart beat)�A���O(command)���C
 * setup �ٷ|�I�s CHAR_D �ӧ��� game-specific ���H����l�ơC
 */

void
setup()
{
    seteuid(getuid());

    /* �u���ƻs������ݭn���} heart beat �ΥH�U���]�w�A�ΨӸ`�� CPU time */
    if( !clonep(this_object()) ) return;

    enable_player();
    init_command();
    CHAR_D->setup_char( this_object() );

    set_heart_beat(1);
    tick = 5 + random(10);
}

/* heart_beat()
 *
 * �H�����߸��禡�A�o�Ө禡�C������|�Q driver �I�s�@���A���H���o�H�i��
 * �԰����ʧ@�F�ϥΪ̥H�� NPC �S�����\����O�w�q�b NPC �� USER ������
 * �C
 *
 * �ѩ�o�Ө禡�Q���檺���ƬO��� mudlib ���̰����A�]���Y���@�۷��̨�
 * �ơA�ܮe���ɭP�į઺�j�T���C�A�p�G�A�� LPC �٨S���ܼ��A�Ф��n�H�N���
 * �o�Ө禡�����e�C
 */

static void
heart_beat()
{
    mapping f;
    int f_altered = 0;

    if( mapp(f=query_destroyed()) && sizeof(f) ) {
	f_altered++;
	RACE_D(query_race())->statistic_destroyed(this_object(), f);
        if( !this_object() ) return;
    }

    if( mapp(f=query_exhausted()) && sizeof(f) ) {
	f_altered++;
	RACE_D(query_race())->statistic_exhausted(this_object(), f);
        if( !this_object() ) return;
    }

    if( mapp(f=query_notified()) && sizeof(f) ) {
	f_altered++;
	this_object()->notify_stat(f);
        if( !this_object() ) return;
    }

    if( f_altered ) clear_statistic_flags();

    /* �԰��^�X������ */
    if( living(this_object()) )
    {
	if( is_fighting() ) clean_up_enemy();

	if( is_busy() ) continue_action();
	else if( is_fighting() ) attack();
    }

    /* �H�U�O tick �ɶ��쪺�ɭԤ~�|���檺�����C */
    if( tick-- ) return;

    /* �U�@�� tick ���ɶ����j���üơA�N�Ҧ��ͪ��� heart beat ���}�A�H�K�y
     * ���t�Ϊ��t��L�󶰤��b�S�w�� tick�C
     */
    tick = 5 + random(10);

    update_condition();
    regenerate();
}

void
lose_fight(object opponent)
{
    if( opponent ) opponent->win_fight(this_object());
}

// notify_stat()
//
// This is an apply support by F_STATISTIC which is called by heart_beat()
// when statistic_notification is detected.
int notify_stat(mapping flag)
{
    mapping exits;
    string *dirs, default_dir;

    if( !living(this_object())
    ||	!environment()
    ||	!mapp(exits = environment()->query("exits"))
    ||	!sizeof(dirs = keys(exits)) )
        return 0;

    /* �p�G���]�w�w�]�k�]��V�A�h�����թ��o�Ӥ�V�k�]�A�_�h�H����@��
     * ��V�]�C
     */
    default_dir=query("wimpy_dir");

    if( stringp(default_dir) && member_array(default_dir, dirs) 
    &&	command("go " + default_dir) )
	return 1;

    return command("go "+ dirs[random(sizeof(dirs))]);
}

varargs void
revive(int quiet)
{
    object ob;
    string arg, arg2;

    remove_call_out("revive");

    /* �p�G�o�ӤH���Q��L�H����a�ۡA���ʨ���a�̪��~�� */
    while( environment()->is_character() )
        this_object()->move(environment(environment()));

    enable_player();
    delete_temp("block_msg/all");

    if( !quiet ) {
        COMBAT_D->announce(this_object(), "revive");
        message("system", HIY "\n�C�C�a�A�ש�S���F��ı....\n\n" NOR,
            this_object());
    }
}

/*  �H�������`
 */
void
die()
{
    object corpse, ob;

    /* ����@�����԰��B�O�@�B������ܪ����Y */
    remove_all_killer();
    guard_ob(0);
    charge_ob(0);
    dismiss_team();

    /* ������󥿦b�i�檺�ʧ@ */
    if( is_busy() ) interrupt(this_object(), INTR_DEATH);

    /* �M���Ҧ��� condition */
    clear_condition();

    /* �ŧi�o�ӤH�������` */
    COMBAT_D->announce(this_object(), "dead");

    /* �p�G�o�W�H���b���g���A���L�u�w�R�a�v���L�ӡA�o�ˤ~�ݱo���
     * �v���`���T��
     */
    if( !living(this_object()) ) revive(1);

    if ( query("life_form") == "ghost") {
        tell_object(this_object(), HIR "\n�A�w�g��z���F�I�I�I\n\n" NOR);
        message("vision", this_object()->name() + "�Ʀ��@�}�ϡA�����F ...\n",
            environment(this_object()), this_object());
        return;
    }

    // �[�W���`���ܱԭz -dragoon
    tell_object(this_object(), HIR "\n�A���F�I�I\n\n" NOR);
    if( objectp(corpse = CHAR_D->make_corpse(this_object())) )
	corpse->move(environment());
}

varargs void
unconcious(string reason)
{
    object ob, me=this_object();

    /* �w�g���g ? */
    if( !living(me) ) return;

    /* �Ův������g */
    if ( wizardp(this_object()) ) {
        message("system", HIW "\n�A���Ův��O�v¡�F���W�������ˮ` ....\n\n" NOR,
		me);
        me->set_stat_current("gin", me->query_stat_maximum("gin"));
        me->set_stat_current("kee", me->query_stat_maximum("kee"));
        me->set_stat_current("sen", me->query_stat_maximum("sen"));
        me->set_stat_current("HP", me->query_stat_maximum("HP"));
        me->set_stat_current("water", me->query_stat_maximum("water"));
        me->set_stat_current("food", me->query_stat_maximum("food"));
        return;
    }

    /* ����Ҧ� fight �����ĤH */
    remove_all_enemy();

    /* ���_���b�i�檺�ʧ@ */
    if( is_busy() ) interrupt(me, INTR_UNCONCIOUS);

    message("system", HIR "\n�A�����e�@�¡A���ۤ���]�����D�F....\n\n" NOR,
        this_object());

    disable_player(stringp(reason) ? reason : " <���g����>");
    set_temp("block_msg/all", 1);

    COMBAT_D->announce(this_object(), "unconcious");

    /* �]�w�@������d�� */
    remove_call_out("revive");
    call_out("revive", 60);
}

// overrides

int
receive_object(object ob, int from_inventory)
{
    if( from_inventory ) return 1;

    if( query_encumbrance() + ob->weight() > query_strength("carriage") )
        return notify_fail(ob->name() + "�{�b��A�ӻ��ӭ��F�C\n");

    if( sizeof(all_inventory(this_object())) >= 20 )
        return notify_fail("�A���W�w�g�S���Ŧ�A��a��L�F��F�C\n");

    return 1;
}

varargs int
move(mixed dest, int silent)
{
    if( interactive(this_object()) && is_busy() )
	return notify_fail("�A�{�b�L�k���ʡT\n");

    if( ::move(dest, silent) ) {
	if( interactive(this_object()) && !silent )
	    environment()->do_look(this_object());
	return 1;
    }

    return 0;
}

string
query_id()
{
    mixed* applied;

    if( arrayp(applied = query_temp("apply/id"))
    &&	sizeof(applied)
    &&	arrayp(applied[<1])
    &&	stringp(applied[<1][0]) )
        return applied[<1][0];

    return query("id");
}

int
id(string str)
{
    mixed* applied;

    if( arrayp(applied = query_temp("apply/id"))
    &&	sizeof(applied)
    &&	arrayp(applied[<1]) )
	return member_array(str, applied[<1]) >= 0;
    return ::id(str);
}

varargs string
name(int raw)
{
    string *applied_name;

    if( !raw
    &&	arrayp(applied_name = query_temp("apply/name"))
    &&	sizeof(applied_name)
    &&	stringp(applied_name[<1]) )
	return applied_name[<1];
    return ::name(raw);
}

/*  short()
 *
 *  �o�Ө�ƶǦ^�H����²�u�ԭz�A�ϥΪ̦b look �@�өж����A�Y����L�H���A�h
 *  ��ܪ��N�O�o�Ӧr��C
 */
varargs string
short(int raw)
{
    string str, title, nick, *applied;

    str = ((title = query("title")) ? title : "")
        + ((nick = query("nickname")) ? ("�u"+nick+"�v") : (title?" ":""))
        + ::short(1);

    if( raw ) return str;

    /* ���[���u�ԭz */        
    if(	arrayp(applied = query_temp("apply/short"))
    &&	sizeof(applied)
    &&	stringp(applied[<1]) ) {
	str = applied[<1];
	if( ! this_player()->query("option/BRIEF_SHORT") )
	    str += "(" + capitalize(query_id()) + ")";
    }

    if( !living(this_object()) ) str += HIR + query("disable_type") + NOR;

    if( !userp(this_object()) ) return str;

    // These user only case are defined here because the case that wizards
    // exec into an NPC.

    if( query("life_form")=="ghost" ) str = HIK + str + "������" NOR;
    else if( query("life_form")=="undead" ) str = CYN + str + "������" NOR;

    if( query_temp("pending/hidden") )
	str += "�����������a���b�t�B ...";

    if( !interactive(this_object()) ) str += HIG " <�_�u��>" NOR;
    else if( query_idle( this_object() ) > 120 ) str += HIM " <�o�b��>" NOR;

    if( in_input() ) str += HIC " <��J��r��>" NOR;
    if( in_edit() ) str += HIY " <�s���ɮפ�>" NOR;

    return str;
}

varargs string
long(int raw)
{
    string str, *applied;

    if( !raw
    &&	arrayp(applied = query_temp("apply/long")) 
    &&	sizeof(applied)
    &&	stringp(applied[<1]) )
	str = applied[<1];
    else str = ::long(raw);

    if( !raw
    &&	arrayp(applied = query_temp("apply/description")) 
    &&	sizeof(applied)
    &&	stringp(applied[<1]) ) {
	str += implode(applied, "\n");
	str = replace_string(str, "$N", this_object()->name(raw));
    }

    return str;
}

varargs string
rank(string politeness, int raw)
{
    string c, r;

    if( c = this_object()->query_class() )
        r = CLASS_D(c)->query_rank(this_object(), politeness);
    else
        r = ::rank(politeness, raw);

    if( !politeness && !raw)
        switch(wizhood(this_object())) {
        case "(admin)": return "�j��";
        case "(arch)": return "�j�Ův";
        case "(wizard)": return "�Ův";
        case "(apprentice)": return "���ߧŮv";
        case "(immortal)": return "�Ȯy�Ův";
        }
    return r;
}

nomask int
visible(object ob)
{
    int a, b;

    /* ����H���û����i�H�ݨ�ۤv */
    if( ob==this_object() ) return 1;

    /* �Ův�û��i�H�ݨ�Ův���Ť�ۤv�C������ */
    a = wiz_level(ob);
    b = wiz_level(this_object());
    if( wizardp(ob) && a>b ) return 1;
    if( query("invis") && a<=b ) return 0;

    if( !::visible(ob) ) return 0;

    /* ���ê�����ݭn��������O�~��o�{ */
    if( query_temp("pending/hidden") > ob->query_ability("awarness") )
	return 0;

    /* ����ݭn�S���O�~��ݨ� */
    if( query("life_form")=="ghost"
    &&	!ob->query_temp("apply/vision_of_ghost") ) return 0;

    return 1;
}
