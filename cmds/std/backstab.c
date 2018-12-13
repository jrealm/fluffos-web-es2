/*  backstab.c - the backstab command

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

#define DELAY_COUNTDOWN         3

#define INITIAL_COUNTDOWN       DELAY_COUNTDOWN + 1
#define ENGAGE_COUNTDOWN        DELAY_COUNTDOWN + 2
#define DOIT_COUNTDOWN          DELAY_COUNTDOWN + 3

int do_backstab(object, object);
int halt_backstab(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{       
    object victim;

    if( me->query_stat("fatigue")>=me->query_stat_maximum("fatigue") )
        return notify_fail(me->name() + "���¤F�o�ذ����N�����欰�A���@�N����o�өR�O�C\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("�H���F�N�@�F�ʤF, �֥h�䫰���_���a!!\n");

    if( me->is_busy() )
        return notify_fail("�Х��� halt ����A���b�����ơC\n");

    if( me->is_fighting() )
        return notify_fail("�A�w�g�b�԰����F�C\n");

    if( !arg
    ||  arg == "corpse"
    ||  !(victim = present(arg, environment(me)))
    ||  victim==me
    ||  !victim->is_character() )
        return notify_fail("�A�n��ŧ�֡H\n");

    if( environment(me)->query("no_fight") ) {
        if( !victim->query("unprotect_mark") ) {
            tell_object(me, "�o�̤���԰��C\n");
            return 1;
        }
    }
    
    // add by dragoon
    if( userp(victim) && !interactive(victim) ) 
        return notify_fail("�o�H�{�b���b�u�W�C\n");

    if( victim->query("no_fight") ) return notify_fail("����C\n");

//    if( !arg ) return notify_fail("�A�n��ŧ�֡H\n");

    if( me->skill_mapped("backstab") )
    {
        mapping weapon = me->query_temp("weapon");
        string skill;

        if( !mapp(weapon) || !sizeof(weapon) ) skill = "unarmed";
        else {
            skill = "dagger";
            if( !objectp(weapon["dagger"]) )
                return notify_fail("�A�u��H�Ť�ΤP�����Z���i�氽ŧ�C\n");
        }
        if( ! me->skill_mapped(skill) )
            return notify_fail("�A���� enable �A�������ޯ�C\n");
    }
    else {
        write("�A���� enable �u" + to_chinese("backstab") + "�v�~��i�氽ŧ�C\n");
        return 1;
    }

    // �����a�i�H�Q��stake�ӽmbackstab -Dragoon
    if( !living(victim) && !victim->query("TARGET_STAKE") ) {
        write("�A���ݭn��ŧ�o�ӳå�A�����W�ڡI\n");
        return 1;
    }

    if( victim->query("TARGET_STAKE")
    && me->query_skill("backstab") > 40 ) {
        write("���H������H�u�����A�߱o�ʲL����ŧ�t��ޥ��I\n");
        return 1;
    }

    me->set_temp("pending/hidden", 0);
    write("�A�}�l�����n��a�q" + victim->name() + "�I��C�C�a�� ... �C\n\n");

    me->set_temp("backstab_countdown", INITIAL_COUNTDOWN);
    me->start_busy( (: do_backstab, victim :), (: halt_backstab :) );

    return 1;
}

int do_backstab(object victim, object me)
{
    int countdown, ability, defend, bonus;

    if( !me ) return 0;

    /* �ˬd�n��ŧ����H�O�_�٦b */
    if( !victim || environment(me) != environment(victim) ) {
        tell_object(me, "\n...  �u�i���A���ӳå�w�g���b�o�̤F�C\n");
        return 0;
    }

    /* ���o��ŧ�̪���ŧ�{�ǭ˼ƭp�ɭ� */
    countdown = me->query_temp("backstab_countdown");
    if( ! countdown ) countdown = 4;

    /* �b�԰����A�H */
    if( me->is_fighting() ) {
        tell_object(me, "\n�i�c�A�٬O�����I���e���ĤH�a�C\n");
        return 0;
    }

    switch(countdown)
    {
    case INITIAL_COUNTDOWN:
        /* �Ĥ@���q������ */
        ability = 3 * (me->query_attr("dex") + me->query_skill("backstab"));
        defend = victim->query_ability("awarness")
                 + random(victim->query_stat("gin"));

        if( living(victim) && defend > ability ) {
            write("�A�Q�o�{�F�I\n");
            victim->catch_backstab(me);
            return 0;
        }

        /* ����٨S���o�{�A�i�J�U�@���q */
        tell_object(me, CYN "\n�ݰ_��" + victim->name()
                + "�٨S����ı�A���|�� ... �C\n\n" NOR);
        me->set_temp("backstab_countdown", ENGAGE_COUNTDOWN);
        me->improve_skill("backstab", 1 + random(me->query_attr("int")));
        return 1;

    case ENGAGE_COUNTDOWN:
        /* �ĤG���q������ */
        ability = 2 * (me->query_attr("dex") + me->query_skill("backstab"));
        defend = victim->query_ability("awarness")
                 + random(victim->query_stat("gin"));

        if( living(victim) && defend > ability ) {
            message_vision(HIY "\n$N�o�{$n�b$P�I��Q���I�t��I\n" NOR,
                        victim, me);
            me->kill_ob(victim);
            me->start_busy(3);
            write(HIR "\n�V�|�I�Q�o�{�F�I\n\n" NOR "�A�Q"
                        + victim->name() + "��F�ӱ��⤣�ΡI\n\n");

            /* �Q��ŧ�̪����� */
	    // ���C���Ѫ��ˮ`�M�R���v, for thief's low hp -dragoon
            victim->kill_ob(me);
            victim->add_temp("apply/attack", 2 * victim->query_level() );
            victim->add_temp("apply/damage", victim->query_level() );
            victim->attack(me);
            victim->add_temp("apply/attack", -2 * victim->query_level() );
            victim->add_temp("apply/damage", -victim->query_level() );

            /* ��ŧ�̪��N�� */
            me->gain_score("mortal sin", 1);
            me->set_temp("backstab_countdown", DELAY_COUNTDOWN);
            return 1;
        }
        write(CYN "\n�A���\\�a�Ө�" + victim->name() + "���I��A�ǳưʤ�F ...\n\n" NOR);
        me->improve_skill("backstab", 1 + random(me->query_attr("int")));
        me->gain_score("mortal sin", random(10)+1);
        me->set_temp("backstab_countdown", DOIT_COUNTDOWN);
        return 50;

    case DOIT_COUNTDOWN:
        message_vision(HIY "\n$N�q$n���I��@�D�ӥX�A�ܹD�G�u�h���a�I"
                + victim->rank("rude") + "�I�v\n\n" NOR, me, victim);
        tell_object(victim, "�����I�A�Q" + me->name() + "�q�᭱��ŧ�F�I\n");
        me->kill_ob(victim);

        /* ��ŧ���\���¤O */
        bonus = 10 + me->query_skill("backstab")
                + 2 * me->query_skill("killerhood");

        me->add_temp("apply/damage", bonus/2);
        me->add_temp("apply/attack", bonus);
        me->attack(victim);
        if( random(victim->query_ability("defense"))
                < me->query_skill("killerhood") ) {
            message_vision(HIY "$N��ŧ$n�o��A��$p�@�ɤ������L�ӡA�y�S��"
                        "�A�ѹꤣ�Ȯ�a���e�i�G�@�B�C\n" NOR,
                        me, victim);
            /* ���⥻��A�l�[��U */
            me->attack(victim);
            me->attack(victim);
        }
        me->add_temp("apply/damage", - bonus/2);
        me->add_temp("apply/attack", - bonus);

        victim->kill_ob(me);

        /* �����g��� */
        me->improve_skill("backstab", 1 + random(me->query_attr("int")*2) );
        if( me->query_learn("killerhood") )
            me->improve_skill("killerhood", 1 + random(me->query_attr("dex")) );
        me->gain_score("mortal sin", bonus);

        return 0;

    default:
        /* �Y�b���𤤡A����˼ƭp�� */
        if( countdown > 0 && countdown <= DELAY_COUNTDOWN ) {
            me->set_temp("backstab_countdown", --countdown);
            return countdown;
        }
        return 0;
    }
}

int halt_backstab(object me)
{
    int countdown = me->query_temp("backstab_countdown");

    if( countdown > DELAY_COUNTDOWN ) {
        write("�A�����F��ŧ�����Y�C\n");
        me->supplement_stat("fatigue", 5);
        return 1;
    }
    write("�ӿ�F�A�A�⦣�}�æa�Q�樭�A���O�S�šI\n");
    return 0;
}

int help()
{
    write(@TEXT
���O�榡�Gbackstab <�ؼ�>

�o�ӫ��O���A��ĤH�i�氽ŧ�t��A��ŧ���\�i�H��ĤH�y���ܤj���ˮ`�A���O
���Ѥ]�|���A�I�X���֥N���C

��ŧ�����\�v�D�n��A���u��ŧ�t��ޭǡv�o�ӧޯ঳���A�Ӷˮ`�O�h�����@��
��P�u���⥻��v���v�T�A��ŧ�ɥu��Ť�A�ΨϥΤP�����u�L�b�C
TEXT
    );
        return 1;
}
