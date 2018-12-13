/*  help.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include "/doc/help.h"

inherit F_CLEAN_UP;

static string *default_search = DEFAULT_SEARCH_PATHS;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string file, *search;

    if( !arg ) {
        cat(HELP_DIR + "help/topics");
        return 1;
    }

    arg = replace_string(arg, " ", "_");

    // Else, try if a command name is specified.
    seteuid(getuid());
    if( stringp(file = me->find_command(arg)) ) {
        notify_fail("���o�ӫ��O�s�b�M���O�èS���ԲӪ��������C\n");
        return file->help(me);
    }

    // Support efun/lfun help with same name as other topics such as
    // ed() and ed command.
    sscanf(arg, "%s()", arg);

    search = DEFAULT_SEARCH_PATHS;
    if( wizardp(me) )
        search += WIZARD_SEARCH_PATHS;
        
    foreach(string path in search)
    {
	if( file_size(path + arg) < 0 ) continue;
	if( wizardp(me) )
	    write("�������G" + path + arg
		+ "\n---------------------------------------------------------------------\n");
	me->start_more( read_file(path + arg) ); 
	return 1;
    }

    return notify_fail("�S���w��o���D�D���������C\n");
}

int help(object me)
{
    write(@HELP
���O�榡�Rhelp <�D�D>              �Ҧp�R> help all
          help <��ƦW��>()        �Ҧp�R> help call_out()

�o�ӫ��O���ѧA�w��Y�@�D�D���Բӻ������M�Y�O�����w�D�D�M�h���ѧA�����D�D
�����M�Ҧ����D�D�P��ƦW�٬Ҭ��^��C
HELP
    );
    if( wizardp(me) )
        write(@HELP
�����O�|���j�M�D�D�O�_�� command, ( �Y�I�s�̬��Ův, �h���۷j�M /doc/help.h
���� WIZARD_SEARCH_PATHS ), �A�j�M DEFAULT_SEARCH_PATHS�C 
�Y���P�ɦW�����B��o�Ƿj�M��m��, �h����j���|�̱N���Q�j�M, �Y�u�ݨ��
�e�j�M�� doc, �s�s�s���ɽЯd�N�C
HELP
        );
    return 1;
}
