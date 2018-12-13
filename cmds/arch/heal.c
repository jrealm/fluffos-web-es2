/*  heal.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit F_CLEAN_UP;

int main(object me, string str)
{
    object ob;
    int i;

    seteuid(ROOT_UID);
    if(!str) return notify_fail("���O�榡: heal <�ϥΪ�>\n");

    ob = present(str, environment(me));
    if( !ob ) ob = LOGIN_D->find_body(str);
    if( !ob ) ob = me;

    ob->heal_stat("gin", 9999);
    ob->heal_stat("kee", 9999);
    ob->heal_stat("sen", 9999);

    ob->supplement_stat("gin", 9999);
    ob->supplement_stat("kee", 9999);
    ob->supplement_stat("sen", 9999);

    // ok ..
    message_vision("$N�ΧŮv�����O�v��$n���˶աC\n", me, ob);
    return 1;
}

int help(object me)
{
write(@HELP
���O�榡 : heal <�Y�H>

�����O�i���A(�p)�N�Y�H����𯫧�����_�C
HELP
    );
    return 1;
}
