/*  sneak.c - the alternate move command as 'go' that moves secretly.

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/


// This command is another command for movement. Those NPCs who intercept
// players by add_action(..., "go") won't intercept this command.

#include <ansi.h>

inherit F_CLEAN_UP;

int do_sneak(object me, object dest, string dir, string exit_dir, int type);
int halt_sneak(object me, object who, string how);

mapping default_dirs = ([
    "north":		"�_",
    "south":		"�n",
    "east":		"�F",
    "west":		"��",
    "northup":		"�_��",
    "southup":		"�n��",
    "eastup":		"�F��",
    "westup":		"����",
    "northdown":	"�_��",
    "southdown":	"�n��",
    "eastdown":		"�F��",
    "westdown":		"����",
    "northeast":	"�F�_",
    "northwest":	"��_",
    "southeast":	"�F�n",
    "southwest":	"��n",
    "up":		"�W",
    "down":		"�U",
    "out":		"�~",
]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    mixed dest;
    string mout, min, dir;
    object env, obj, *observer, obsr;
    int skill, obsp, type;

    if( !arg ) return notify_fail("�A�n�����Ӥ�V���ʡS\n");

    if( me->is_busy() )
        return notify_fail("�n���ʽЧA���� halt �פ�A���b�����ơC\n");

    env = environment(me);
    if( !env ) return notify_fail("�A���̤]�h���F�A�Ч�@��Ův�B�z�C\n");

    if( me->is_fighting() )
	return notify_fail("�A�٦b�԰��I\n");

    if( !(dest = env->query("exits/" + arg)) )
	return notify_fail("�o�Ӥ�V�S���X���C\n");

    // Load destination room and check its existence.
    if( stringp(dest) ) obj = load_object(dest);
    else obj = dest;
    if( !objectp(obj) )
	return notify_fail("�o�@�Ӥ�V���X�f�����D�M�гq���Ův�B�z�C\n");

    skill = me->query_skill("sneak");

    observer = all_inventory(obj);
    obsp = 0;
    // The sneak formula:
    //   postive factors: sneak skill, player's gin
    //   negative factors: gin of characters in both room, and their
    //                     sneak/force skill.
    foreach(obsr in observer) {
        if( !living(obsr) || obsr==me ) continue;
        obsp += random(obsr->query_stat("gin") / 3);
        obsp += obsr->query_skill("force");
    }

    skill = skill * 3 + me->query_stat("gin") / 10 + me->query_skill("move");

//    printf("���ޥ� %d�A�[��� %d�C\n", skill, obsp);

    // Test random match. If fail, move with go.
    if( random(skill*3 + me->query_stat("gin")) < random(obsp) )
        type = 0;
    else type = 1;
    
    if( !env->valid_leave(me, arg) ) return 0;

    if( !undefinedp(default_dirs[arg]) )    dir = default_dirs[arg];
    else                                    dir = arg;

    write("�A�}�l�\\���\\���a��" + dir + "���ʡC\n");

    me->set_temp("sneak_countdown", 3);
    me->start_busy( (: do_sneak, me, obj, dir, arg, type :), (: halt_sneak :) );

    return 1;
}

int do_sneak(object me, object obj, string dir, string exit_dir, int type)
{
    int rating;
    object old_env;

    if( !me || !obj ) return 0;
    if( me->query_temp("sneak_countdown") > 0 ) {
	me->add_temp("sneak_countdown", -1);
	tell_object(me, CYN "�p���l�l ...\n" NOR);
	me->improve_skill("sneak", 1);
	return 1;
    }

    me->delete_temp("sneak_countdown");
    old_env = environment(me);
    me->interrupt(me, "ready");
    switch(type) {
    case 0:
        me->force_me("go " + exit_dir);
        break;
    case 1:
	/* ��檺���õ{�� */
	rating = 1 + random( me->query_skill("sneak") * 2 );
        tell_object(me, "�ݰ_�ӡA���G�٨S���H�oı�A����ʡC\n");
	me->set_temp("pending/hidden", rating);
        me->improve_skill("sneak", me->query_attr("int") );
        if( !me->move(obj) ) me->set_temp("pending/hidden", 0);
        break;
    }

    return 0;
}

int halt_sneak(object me, object who, string how)
{
    if( who==me && how=="ready" ) return 1;
    tell_object(me, "�A������C\n");
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : sneak <��V>
 
���A�����w����V���M���ݭn�@�ǧޥ��A��A�ϥμ�檺�覡���ʡA�A�ۤv
�ä��|���D�O�H���S���o�{�A�w�w���D�L�̦]���o�{�A���������ӵo�ʧ����C
 
HELP
    );
    return 1;
}

