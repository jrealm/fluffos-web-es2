/*  passwd.c

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

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object ob;

#ifndef SAVE_USER
    return notify_fail("�t�Υثe���x�s�ϥΪ̸�ơC\n");
#endif

    if( me != this_player(1)
    ||    previous_object() != this_player(1) ) return 0;

    ob = me->link();
    if( !ob ) return 0;
    while( ob && ob->is_character() ) ob = ob->link();

    if( stringp(ob->query("password")) ) {
        write("���F�w���_���M�Х���J�z��Ӫ��K�X�R");
        input_to("get_old_pass", 1, ob);
    } else {
        write("�п�J�s�K�X�G");
        input_to("get_new_pass", 1, ob);
    }

    return 1;
}

private void get_old_pass(string pass, object ob)
{
    string old_pass;

    write("\n");
    old_pass = ob->query("password");
    if( crypt(pass, old_pass)!=old_pass ) {
        write("�K�X���~�T\n");
        return;
    }
    write("�п�J�s�K�X�R");
    input_to("get_new_pass", 1, ob );
}

private void get_new_pass(string pass, object ob)
{
    write("\n�ЦA��J�@���s�K�X�R");
#ifdef	ENABLE_MD5_PASSWORD
    input_to("confirm_new_pass", 1, ob, crypt(pass,sprintf("$1$%d", random(99999999))));
#else
    input_to("confirm_new_pass", 1, ob, crypt(pass,0));
#endif
}

private void confirm_new_pass(string pass, object ob, string new_pass)
{
    write("\n");
    if( crypt(pass, new_pass)!=new_pass ) {
        write("�藍�_�M�z��J���K�X�ä��ۦP�M�~��ϥέ�Ӫ��K�X�C\n");
        return;
    }
    seteuid(getuid());
    if( !ob->set("password", new_pass) ) {
        write("�K�X�ܧ󥢱ѡT\n");
        return;
    }

#ifdef SAVE_USER
    ob->save();
    write("�K�X�ܧ󦨥\\�C\n");
    log_file("PASSWD", sprintf("[%s] %s changed password from %s\n",
        ctime(time()), getuid(this_player(1)), query_ip_name(this_player(1)) ));
#endif
}

int help(object me)
{
    write(@HELP
���O�榡 : passwd
 
�o�ӫ��O�i�H�ק�A���H���K�X�C
 
HELP
    );
    return 1;
}
 
