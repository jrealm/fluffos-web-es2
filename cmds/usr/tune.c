/*  tune.c

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

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string *tuned_ch;

    tuned_ch = me->link()->query("channels");
    if( !arg ) {
        if( !pointerp(tuned_ch) || !sizeof(tuned_ch) )
            write("�A�{�b�èS����ť�����W�D�C\n");
        else
            write("�A�{�b��ť���W�D�R" + implode(tuned_ch, ", ") + "�C\n");
        return 1;
    }

    if( pointerp(tuned_ch) && member_array(arg, tuned_ch)!=-1 ) {
        write("���� " + arg + " �W�D�C\n");
        tuned_ch -= ({ arg });
        me->link()->set("channels", tuned_ch);
        return 1;
    } else {
        write("�n���}�Y���W�D�u�n�θ��W�D���ܧY�i�C\n");
        return 1;
    }
}

int help(object me)
{
    write(@HELP
���O�榡�Rtune [<�W�D�W��>]

�o�ӫ��O���A��ܬO�_�n��ť�Y�@�W�D���T���M�p�G�S�����w�W�D�W�١M�N�|�C�X
�A�ثe��ť�����W�D�M�p�G���w�F�W�D�M��Ӧ�ť�����N�|�����M�Ϥ����}�C

�p�G�A��@�ӨS����ť�����W�D���ܡM�|�۰ʱN�����}�C
�n��@���W�D���ܡM�u�n�ΡR

<�W�D�W��> <�T��> ....

�Ҥl�R
  chat hello everyone!
  
�A�i�H�� help channels �d�ߥثe�������W�D�i�H��ť�C

see also : shout
HELP
    );
    return 1;
}

