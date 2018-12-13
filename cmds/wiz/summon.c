/*  summon.c

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

inherit F_CLEAN_UP;

int main(object me, string str)
{
    object ob;
    int i;

    seteuid(getuid(me));
    if(!str) return notify_fail("���O�榡: summon <�ϥΪ�>\n");
    ob = LOGIN_D->find_body(str);
    if(!ob) return notify_fail("�u�W���ϥΪ̤��S���o�ӤH�C\n");

    // moving
    tell_room(environment(ob), "�ѪŤ����X�@���j���"+
	ob->name() + "��F�_�ӡM�M�ᤣ���F�C\n", ob);
    tell_object(ob,"�@�����A��F�_�ӡM�A���e�@�}�� ....\n");
    ob->move(environment(me));
    tell_object(me, "�A��" + ob->name() + "���A�����e�C\n");
    tell_object(ob,".... ���Ӯɵo�{�O" + me->name() +
	"��A�˹L�Ӫ��C\n");
    log_file("static/SUMMON",
	sprintf("%s(%s) summon %s(%s) �� %s at  %s\n",
	me->name(1), geteuid(me), ob->name(1), geteuid(ob),file_name(environment(me)),ctime(time()) ) );
    tell_room(environment(ob), ob->name() + "��M�X�{�b�A���e�C\n",({me,ob}));

    // ok ..
    return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : summon <�Y�H>

�����O�i���A(�p)�N�Y�H���A���e�C
HELP
    );
    return 1;
}
