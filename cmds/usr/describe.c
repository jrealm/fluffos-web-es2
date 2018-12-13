/*  describe.c

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

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string *txt;

    if( !arg ) return notify_fail("���O�榡�Rdescribe <�y�z>\n");

    txt = explode(arg, "\n");
    if( (strlen(arg) > 400) || (sizeof(txt) > 8) )
        return notify_fail("�z���ԭz�Ӫ��F�M�б���b�K��B��ʦr�H���C\n");

    arg = implode(txt, "\n") + "\n";

    me->set("long", arg);
    write("Ok�C\n");
    return 1;
}

int help()
{
    write(@TEXT
���O�榡�Rdescribe <�y�z>

�o�ӫ��O���A�]�w��O�H�� look ���O�ݧA�ɡM��A���y�z�M�q�`��A
���y�z�W�L�@��ɥi�H�� to describe ���覡�ӿ�J�C
TEXT
    );
    return 1;
}
