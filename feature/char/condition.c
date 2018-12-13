/*  condition.c - character condition interface

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <condition.h>

mapping conditions = ([]);

/* update_condition()
 *
 * �o�Ө�Ʒ|�Q�H���� heart_beat �b�C�� tick �ɩI�s�@���A�t�d��s�H��
 * �Ҧ������Ī��A�C
 */

nomask void
update_condition()
{
    string cnd;
    mixed cnd_data;

    if( !mapp(conditions) || !sizeof(conditions) ) return;

    foreach(cnd, cnd_data in conditions)
	CONDITION_D(cnd)->condition_update(this_object(), cnd, cnd_data);
}

/* restore_condition()
 *
 * �o�Ө�ƥΨӦb�@�ӤH���q�ɮר��^���Ī��A����Ƥ���A��_���Ī��A��
 * �v�T�C��h�W�o�Ө�����ӥu���H���ۤv�~�|�ݭn�I�s�A�ҥH�ŧi�� static�C
 */

static nomask void
restore_condition()
{
    string cnd;
    mixed cnd_data;

    if( !mapp(conditions) || !sizeof(conditions) ) return;

    foreach(cnd, cnd_data in conditions)
	CONDITION_D(cnd)->condition_apply(this_object(), cnd, cnd_data);
}

nomask void
clear_condition()
{
    string cnd;
    mixed cnd_data;

    if( !mapp(conditions) || !sizeof(conditions) ) return;

    foreach(cnd, cnd_data in conditions)
	CONDITION_D(cnd)->condition_unapply(this_object(), cnd);

    conditions = ([]);
}

nomask void
set_condition(string cnd, mixed info)
{
    if( !mapp(conditions) ) conditions = ([]);

    /* �I�s���Ī��A daemon �Ѱ�(unapply) ��Ӫ��P�@���Ī��A */
    if( conditions[cnd] )
	CONDITION_D(cnd)->condition_unapply(this_object(), cnd,
		conditions[cnd]);

    conditions[cnd] = info;
    CONDITION_D(cnd)->condition_apply(this_object(), cnd, info);
}

nomask mixed
query_condition(string cnd)
{
    return mapp(conditions) ? conditions[cnd] : 0;
}

nomask void
delete_condition(string cnd)
{
    if( !mapp(conditions) || undefinedp(conditions[cnd]) ) return;

    CONDITION_D(cnd)->condition_unapply(this_object(), cnd);
    map_delete(conditions, cnd);
}

 