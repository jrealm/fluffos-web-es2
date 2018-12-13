/*  team.c

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

int
main(object me, string arg)
{
    object *t;

    if( !arg ) {
	if( !pointerp(t = me->query_team()) )
	    return notify_fail("�A�{�b�èS���ѥ[���󶤥�C\n");
	write("�A�{�b������������R\n  " + implode(t->short(1), "\n  ") + "\n");
	return 1;
    }

    if( arg=="dismiss" ) {
        if( !pointerp(t = me->query_team()) )
            return notify_fail("�A�{�b�èS���ѥ[���󶤥�C\n");
        if( me->is_team_leader() ) {
            message("team", me->name(1) + "�N����Ѵ��F�C\n", t, me);
            write("�A�N����Ѵ��F�C\n");
        } else {
            message("team", me->name(1) + "�M�w��������C\n", t, me);
            write("�A�����F�A������C\n");
        }
        me->dismiss_team();
        return 1;
    }

    if( sscanf(arg, "with %s", arg)==1 ) {
        object ob;

        if( !(ob = present(arg, environment(me)))
        ||    !living(ob)
        ||    !ob->is_character()
        ||    ob==me )
            return notify_fail("�A�Q�M�֦����٦�S\n");

        if( !pointerp(me->query_team()) || me->is_team_leader() ) {
            if( me==(object)ob->query_temp("pending/team") ) {
                if( !pointerp(me->query_team()) ) {
                    ob->add_team_member(me);
                    message_vision("$N�M�w�[�J$n������C\n", me, ob);
                } else {
                    me->add_team_member(ob);
                    message_vision("$N�M�w��$n�[�J����C\n", me, ob);
                }
                ob->dellete_temp("pending/team");
                return 1;
            } else {
                message_vision("$N�ܽ�$n�[�J$P������C\n", me, ob);
                tell_object(ob, YEL "�p�G�A�@�N�[�J�M�Х� team with " + me->query("id") + "�C\n" NOR);
                me->set_temp("pending/team", ob);
                return 1;
            }
        } else
            return notify_fail("�u�������S�i�H�ܽЧO�H�[�J�C\n");
    }

    if( sscanf(arg, "talk %s", arg)==1 ) {
        if( !pointerp(t=me->query_team()) )
            return notify_fail("�A�{�b�èS���M�O�H�զ�����C\n");
        message("team", HIW "�i����j" + me->name(1) + "�R" + arg + "\n" NOR, t);
        return 1;
    }

    if( sscanf(arg, "form %s", arg)==1 ) {
        if( !pointerp(t=me->query_team()) || !me->is_team_leader() )
            return notify_fail("�A�����O�@�Ӷ����S�~���´�}�ΡC\n");
        if( !me->query_skill(arg, 1) )
            return notify_fail("�o�ذ}�ΧA�S�ǹL�C\n");
        return SKILL_D(arg)->form_array(me);
    }
}

int help(object me)
{
    write(@HELP
������O�ϥΤ�k:

team with <�Y�H> - ��Y�H�զ�����. �����n���賣�P�N�[�J�~�|�ͮġC
team dismiss     - ���}����. �Y�U�����O���O�ⶤ, �h��Ӷ���|�Ѵ��C
team talk <�T��> - �򶤥�̨�L���H�͸�, �i�H�� tt <�T��> ���N�C
team form <�}�k> - �p�G����ⶤ�ǹL�}�k���ܡM�i�H�N�����������´��
                   �Y�ذ}�ΡM�զ��}�Ϊ����A�u�n��S�@���ʴN�|�Ѱ��C

�����U team ���O�ɫh�|��ܧA�ثe�O�_���[�J����ζ����W��, �Ĥ@�ӬO��S�C
 quit �ɷ|�۰ʲ�������, ��S quit �ɫh��Ӷ���Ѵ��C

��: team �� follow �O�W�ߪ��M�A���@�w�n follow �����S�C
HELP
    );
    return 1;
}
