/*  edemote.c

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

int in_use;

int main(object me, string arg)
{
    mapping emote;

    SECURED_COMMAND;

    if( !arg ) return notify_fail("�A�n�s�褰�� emote�S\n");

    if( sscanf(arg, "-d %s", arg) ) {
        write("�R�� emote�R" + arg + "\n");
        EMOTE_D->delete_emote(arg);
        return 1;
    }

    if( sscanf(arg, "-p %s", arg) ) {
        emote = EMOTE_D->query_emote(arg);
        printf("�W���ק�R%s\n", emote["updated"]);
        printf("�w�w�w�w�w�w�w�w�w�w�w�w�w\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
            emote["myself"], emote["others"], emote["myself_self"],
            emote["others_self"], emote["myself_target"], emote["target"],
            emote["others_target"] );
        return 1;
    }

    emote = EMOTE_D->query_emote(arg);
    emote = (["updated":geteuid(me)]);

    write("�s�� emote�R" + arg + "\n");
    write("�T���i�H���n�X��M�� . ��ܵ����C\n");
    write("�T�����i�ϥΪ��ѼƦ��H�U�X�ءR\n");
    write("  $N  �ۤv���W�r�C\n");
    write("  $n  �ϥι�H���W�r�C\n");
    write("  $P  �ۤv���H�٥N�W���M�p�A�B�p�B�L�B�o�B�e�B���C\n");
    write("  $p  �ϥι�H���H�٥N�W���M�p�A�B�p�B�L�B�o�B�e�B���C\n");
    write("�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w\n");
    write("�����w��H�ϥγo�� emote �ɡM�A�ۤv�ݨ쪺�T���R\n->");
    input_to("get_msg_myself", emote, arg);
    return 1;
}


private int
get_msg_myself(string msg, mapping emote, string pattern)
{
    if (msg==".") {
        if( !undefinedp(emote["myself"]) ) emote["myself"] += "\n";
        write("�����w��H�ϥγo�� emote �ɡM��L�H�ݨ쪺�T���R\n->");
        input_to("get_msg_others", emote, pattern);
        return 1;
    }
    if( !undefinedp(emote["myself"]) )
        emote["myself"] += msg + "\n";
    else emote["myself"] = msg;
    write("->");
    input_to("get_msg_myself", emote, pattern);
    return 1;
}

private int
get_msg_others(string msg, mapping emote, string pattern)
{
    if (msg==".") {
        if( !undefinedp(emote["others"]) ) emote["others"] += "\n";
        write("��ۤv�ϥγo�� emote �ɡM�ۤv�ݨ쪺�T���R\n->");
        input_to("get_msg_myself_self", emote, pattern);
        return 1;
    }
    if( !undefinedp(emote["others"]) )
        emote["others"] += msg + "\n";
    else emote["others"] = msg;
    write("->");
    input_to("get_msg_others", emote, pattern);
    return 1;
}

private int
get_msg_myself_self(string msg, mapping emote, string pattern)
{
    if (msg==".") {
        if( !undefinedp(emote["myself_self"]) ) emote["myself_self"] += "\n";
        write("��ۤv�ϥγo�� emote �ɡM��L�H�ݨ쪺�T���R\n->");
        input_to("get_msg_others_self", emote, pattern);
        return 1;
    }
    if( !undefinedp(emote["myself_self"]) )
        emote["myself_self"] += msg + "\n";
    else emote["myself_self"] = msg;
    write("->");
    input_to("get_msg_myself_self", emote, pattern);
    return 1;
}

private int
get_msg_others_self(string msg, mapping emote, string pattern)
{
    if (msg==".") {
        if( !undefinedp(emote["others_self"]) ) emote["others_self"] += "\n";
        write("��O�H�ϥγo�� emote �ɡM�ۤv�ݨ쪺�T���R\n->");
        input_to("get_msg_myself_target", emote, pattern);
        return 1;
    }
    if( !undefinedp(emote["others_self"]) )
        emote["others_self"] += msg + "\n";
    else emote["others_self"] = msg;
    write("->");
    input_to("get_msg_others_self", emote, pattern);
    return 1;
}

private int
get_msg_myself_target(string msg, mapping emote, string pattern)
{
    if (msg==".") {
        if( !undefinedp(emote["myself_target"]) ) emote["myself_target"] += "\n";
        write("��O�H�ϥγo�� emote �ɡM�ϥι�H�ݨ쪺�T���R\n->");
        input_to("get_msg_target", emote, pattern);
        return 1;
    }
    if( !undefinedp(emote["myself_target"]) )
        emote["myself_target"] += msg + "\n";
    else emote["myself_target"] = msg;
    write("->");
    input_to("get_msg_myself_target", emote, pattern);
    return 1;
}

private int
get_msg_target(string msg, mapping emote, string pattern)
{
    if (msg==".") {
        if( !undefinedp(emote["target"]) ) emote["target"] += "\n";
        write("��O�H�ϥγo�� emote �ɡM���A�ۤv�M�ϥι�H�~�M��L�H�ݨ쪺�T���R\n->");
        input_to("get_msg_others_target", emote, pattern);
        return 1;
    }
    if( !undefinedp(emote["target"]) )
        emote["target"] += msg + "\n";
    else emote["target"] = msg;
    write("->");
    input_to("get_msg_target", emote, pattern);
    return 1;
}

private int
get_msg_others_target(string msg, mapping emote, string pattern)
{
    if (msg==".") {
        if( !undefinedp(emote["others_target"]) ) emote["others_target"] += "\n";
        EMOTE_D->set_emote(pattern, emote);
        write("Emote �s�赲���C\n");
        return 1;
    }
    if( !undefinedp(emote["others_target"]) )
        emote["others_target"] += msg + "\n";
    else emote["others_target"] = msg;
    write("->");
    input_to("get_msg_others_target", emote, pattern);
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡�Gedemote [-d|-p] <emote>
 
�o�ӫ��O�i�H�ק�, �R�� emote �ΦC�X�䤺�e. �[�W -d �ѼƷ|�R��
���w�� emote, -p �Ѽƫh�|�C�X���w emote �����e. �C�X�����ǻP�s
�� emote �ɬۦP.
 
��J emote �T���ɦ��T�Ӷ���: �S���ؼ�, ���w�ؼЩάO��ۤv. �Y
���Q���Y���T��, �h�����b�ťզ��J '.' ���L.
 
�@�� emote �T���i�H���ܦh��, �b�ťզ��J '.' ������J�Ӷ� emote.
 
�s�� emote �ɥi�H�ΥH�U���Ÿ��Ӫ��:
 
$N : �ۤv���W�r.
$n : �ؼЪ��W�r.
$P : �ۤv���H�٥N�W��.
$p : �ؼЪ��H�٥N�W��.
 
HELP
    );
    return 1;
}
