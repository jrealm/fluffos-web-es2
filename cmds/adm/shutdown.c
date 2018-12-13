/*  shutdown.c

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

int
main(object me, string arg)
{
    string wiz_status;
    object *user, link_ob;
    int i;

    SECURED_ADMIN_COMMAND;

    seteuid(geteuid(this_player(1)));

    message("system", "�C�����s�ҰʡM�еy�Ԥ@�����A login �C\n", users() );

    user = users();
    for(i=0; i<sizeof(user); i++) {
        if( !environment(user[i]) ) continue;
        user[i]->save();
    }

    shutdown();
    return 1;
}
int help (object me)
{
        write(@HELP
���O�榡: shutdown
 
���W���s�_�ʹC���C
 
HELP
);
        return 1;
}
 
