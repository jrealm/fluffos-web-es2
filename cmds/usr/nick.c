/*  nick.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    if( !arg ) return notify_fail("�A�n���ۤv������︹�S\n");
    if( strlen(arg) > 14 )
	return notify_fail("�A���︹�Ӫ��F�M�Q�@�ӵu�@�I���B�T�G�@�I���C\n");
/*
    arg = replace_string(arg, "$BLK$", BLK);
    arg = replace_string(arg, "$RED$", RED);
    arg = replace_string(arg, "$GRN$", GRN);
    arg = replace_string(arg, "$YEL$", YEL);
    arg = replace_string(arg, "$BLU$", BLU);
    arg = replace_string(arg, "$MAG$", MAG);
    arg = replace_string(arg, "$CYN$", CYN);
    arg = replace_string(arg, "$WHT$", WHT);
    arg = replace_string(arg, "$HIR$", HIR);
    arg = replace_string(arg, "$HIG$", HIG);
    arg = replace_string(arg, "$HIY$", HIY);
    arg = replace_string(arg, "$HIB$", HIB);
    arg = replace_string(arg, "$HIM$", HIM);
    arg = replace_string(arg, "$HIC$", HIC);
    arg = replace_string(arg, "$HIW$", HIW);
    arg = replace_string(arg, "$NOR$", NOR);
*/
    seteuid(getuid());
    me->set("nickname", arg);    // use arg + NOR if colorful nick is open
    write("Ok�C\n");
    return 1;
}

int help(object me)
{
    write(@HELP
���O�榡 : nick <�~��, �︹>
 
�o�ӫ��O�i�H���A���ۤv���@���T�G���W�����Y�ΡC

�A�p�G�Ʊ�b�︹���ϥ� ANSI ������r�������C��M�i�H�ΥH�U������r��R
(�Ȥ��}��)

$BLK$ - �¦�	$NOR$ - ��_���`�C��
$RED$ - ����	$HIR$ - �G����
$GRN$ - ���	$HIG$ - �G���
$YEL$ - �g����	$HIY$ - ����
$BLU$ - �`�Ŧ�	$HIB$ - �Ŧ�
$MAG$ - �L����	$HIM$ - ������
$CYN$ - �ź��	$HIC$ - �ѫC��
$WHT$ - �L�Ǧ�	$HIW$ - �զ�

HELP
        );
        return 1;
}
