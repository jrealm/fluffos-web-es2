/*  alias.c

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

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int i;
    mapping alias;
    string verb, replace, *vrbs;
    object link;

    SECURED_COMMAND;

    if( !(link = me->link()) )
	return notify_fail("�A�S���s�u����C\n");

    if( !arg ) {
	alias = link->query_all_alias();
	if( !sizeof(alias) ) {
	    write("�A�ثe�èS���]�w���� alias�C\n");
	    return 1;
        } else  {
	    write("�A�ثe�]�w�� alias ���R\n");
	    vrbs = keys(alias);
	    for(i=0; i<sizeof(vrbs); i++)
		printf("%-15s = %s\n", vrbs[i], alias[vrbs[i]]);
	    return 1;
	}
    }

    if( sscanf(arg, "%s %s", verb, replace)!=2 )
	link->set_alias(arg, 0);
    else if( verb=="alias" )
	return notify_fail("�A����N \"alias\" ���O�]�w��L�γ~�C\n");
    else if( verb=="" )
	return notify_fail("�A�n�]���� alias�S\n");
    else
	link->set_alias(verb, replace);

    write("Ok.\n");
    return 1;
}

int help (object me)
{
    write(@HELP
���O�榡 : alias <���]�w�����O> <�t�δ��Ѥ����O>
 
���ɨt�ΩҴ��Ѥ����O�ݭn��J�ܪ����r��, �b�ϥή�(�ר�O�g�`�Ψ쪺)
�γ\�|�Pı����K, ���ɧA(�p)�Y�i�Φ��@���O�]�w�ô��N�즳�����O�C
 
�d��:
    'alias sc score' �|�H sc ���N score ���O�C
    'alias' �ᤣ�[�Ѽƫh�C�X�A�Ҧ������N���O�C
    'alias sc' �|���� sc �o�Ӵ��N���O�C (�p�G�A���]����)
 
�䤤�i�H�� $1, $2, $3 .... �Ө��N�Ĥ@�B�ĤG�B�ĤT�ӰѼơM�άO $* ���N
�Ҧ����ѼơM�p�R
    'alias pb put $1 in $2'

�h�C��A(�p)���R
    pb bandage bag

�N�|���N���R
    put bandage in bag
    
HELP
    );
    return 1;
}
