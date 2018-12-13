/*  clone.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <command.h>
#include "/doc/help.h"

inherit F_CLEAN_UP;

int main(object me, string file)
{
    int amount;
    object obj;
    string err, msg;

    SECURED_WIZARD_COMMAND;

    /* �ϥΤU�R�O�̪��v���ƻs���� */
    seteuid(geteuid(this_player(1)));

    if (!file) file = me->query("cwf");
    if (!file) return notify_fail("�A�n�ƻs���򪫥�S\n");

    if(sscanf(file, "%d %s", amount, file)==2 && amount < 1 )
	return notify_fail("�ƦX���~���ƶq�ܤ֥����O 1�C\n");

    file = resolve_path(me->query("cwd"), file);
    if( sscanf(file, "%*s.c") != 1 ) file += ".c";

    if( file_size(file) < 0 )
	return notify_fail("�S���o���ɮ�(" + file + ")�C\n");

    if( !amount ) me->set("cwf", file);
    else me->set("cwf", amount + " " + file);

    if( !find_object(file) ) {
	err = catch(load_object(file));
	if (err) {
	    printf("���J���ѡG%O\n", err);
	    return 1;
	}
    }

    err = catch(obj = new(file));
    if( err || !obj ) {
	printf("�ƻs���ѡG%O\n", err);
	return 1;
    }

    if( amount ) {
	if( function_exists("set_amount", obj) )
	    obj->set_amount(amount);
	else if( function_exists("set_volume", obj) )
	    obj->set_volume(amount);
	else
	    write("( " + obj->name() + "���O�ƦX����C )\n");
    }

    if( !stringp(msg = me->query("env/msg_clone")) )
	msg = "�u��$N�����Ť@���M�ܥX�F$n�C\n";

    // re-set by dragoon
    log_file("static/CLONE", 
	sprintf("[%s] %s(%s) �ƻs %s at %s\n",
	ctime(time()), me->name(1), geteuid(me), file, 
	file_name(environment(me)) ) );

    notify_fail("�L�k�ƻs���ಾ�ʪ�����(" + file + ")�C\n");

    if( !obj->query("no_get")
    && !obj->is_character()
    && !living(obj)
    && obj->move(me) ) {
	write(obj->query("name") + "�ƻs���\\�M��b�A�����~��C\n");
	message_vision(msg + "\n", me, obj);
	return 1;
    }
    if( obj->move(environment(me)) ) {
	write(obj->query("name") + "�ƻs���\\�M��b�o�өж��C\n");
	message_vision(msg + "\n", me, obj);
	return 1;
    }
        

    if( function_exists("set_volume", obj) ) {
	object bottle;
	if( !obj->query("default_container") )
	    bottle = new("/obj/bottle");
	else
	    bottle = new(obj->query("default_container"));
	if( obj->move(bottle) ) {
	    write(obj->query("name") + "�ƻs���\\�M��Ӥ@��" + bottle->name() + "���C\n");
	    bottle->move(me);
	    message_vision(msg + "\n", me, obj);
	    return 1;
	}
	destruct(bottle);
    }

    destruct(obj);
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : clone <�ɦW>

�Q�Φ����O�i�ƻs����ಾ�ʤ�����(�t�Ǫ�)�C
HELP
    );
    return 1;
}
