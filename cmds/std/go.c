/*  go.c - character move command

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int do_go(object me, object dest, string dir);

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

void create()
{
    /* �]�� go ���O�i��|���J��L����A�ҥH�ݭn�� euid */
    seteuid(getuid());
}

int main(object me, string arg)
{
    mixed dest;
    object env, obj;

    if( !arg ) return notify_fail("�A�n�����Ӥ�V���S\n");

    if( me->is_busy() ) {
	write("�n���ʽЧA���� halt �פ�A���b�����ơC\n");
	return 1;
    }

    if( me->over_encumbranced() ) {
	write("�A���t���L���M�ʼu���o�C\n");
	return 1;
    }

    env = environment(me);
    if( !env ) return notify_fail("�A���̤]�h���F�C\n");

    if( arg=="escape" ) {
	mapping exits = env->query("exits");
	string *dirs;
	if( mapp(exits) ) {
	    dirs = keys(exits);
	    arg = dirs[random(sizeof(dirs))];
	}
	else {
	    write("�A�w�g�L���i�k�F�I\n");
	    return 1;
	}
    }

    if( !(dest = env->query("exits/" + arg)) ) {
	write("�o�Ӥ�V�S���X���C\n");
	return 1;
    }

    // Load destination room and check its existence.
    if( !objectp(obj = stringp(dest) ? load_object(dest) : dest)) {
	write("�o�@�Ӥ�V���X�f�����D�M�гq���Ův�B�z�C\n");
	return 1;
    }
    
    // Check for mudlib apply valid_leave()
    if( function_exists("valid_leave", env) && !env->valid_leave(me, arg) )
	return 0;

    return do_go( me, obj, arg );
}

int do_go(object me, object obj, string dir)
{
    string min, mout, dir_name;
    object old_env;

    if( !me || !obj ) return 0;

    if( undefinedp(dir_name = default_dirs[dir]) ) dir_name = dir;

    if( me->is_fighting() ) {
	object *enemy, ob;
	int intimidate, my_energy;

	mout = "��" + dir_name + "����Ӱk�F�C\n";
	min = "�^�^�����a�]�F�L�ӡM�Ҽ˦��ǯT�V�C\n";

	enemy = me->query_enemy() - ({ 0 });
	intimidate = me->query_ability("intimidate");
	my_energy = me->query_stat("gin");
	foreach(ob in enemy)
	{
	    if( userp(ob) || !living(ob) ) continue;
	    if( environment(ob) != environment(me) ) continue;
	    if( ! me->visible(ob) ) continue;
	    if( ob->query_ability("intimidate") > intimidate
	    &&	random(ob->query_stat("gin")) > my_energy ) {
		tell_object(me, "�A�Q" + ob->name() + "�צ�F�I\n");
		me->start_busy(1);
		return 0;
	    }
	}
    } else {
        mout = "��" + dir_name + "���}�C\n";
        min = "���F�L�ӡC\n";
    }

    old_env = environment(me);
    message( "vision", me->name() + mout, old_env, me );
    if( me->move(obj) && environment(me)==obj ) {
        message( "vision", me->name() + min, obj, me );
        me->set_temp("pending", 0);
        all_inventory(old_env)->follow_me(me, dir);
        return 1;
    }

    return 0;
}

int help(object me)
{
    write(@HELP
���O�榡 : go <��V>
 
���A�����w����V���ʡC
 
HELP
    );
    return 1;
}
