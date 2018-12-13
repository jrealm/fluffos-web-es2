/*  void.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <login.h>

inherit F_DBASE;

string out_path()
{
    string from;

    if( this_player()
    &&	stringp(from = this_player()->query_temp("last_location")) )
        return from;

    return START_ROOM;
}

private void
create()
{
    set("short", "�̫�ֶ�");
    set("long",
        "���߱z�Ө�o�ӥ@�ɪ��Ĥ@�өж��T�o�̤]�O�b�z�άY�H�d�{�F\n"
        "�Y�˪F�褧��M�Ψӷ�@�����Ҫ��a��C�p�G�z�O���b�|�լ[�]�@��\n"
        "�ϥ� ES2 mudlib ����¦�� MUD�M�аѦ� /doc/admin/README�M�p�G\n"
        "�z�O�L�d�����a�M�Х� 'out' ���}�C\n");
    set("exits/out", (: out_path :) );
    set("no_fight",1);
}

int
do_look(object me, string arg)
{
    printf( "%s - %s\n    %s",
	query("short"),
	wizardp(me)? file_name(this_object()) : "",
	query("long") );
    return 1;
}

int
receive_object(object ob)
{
    return userp(ob);
}
