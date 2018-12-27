/*  edit.c - text editor

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/


#include <function.h>

private void input_line(string line, string text, function callback);

int edit(function callback, string text)
{
    write("�������}�� '.'�M������J�� '~q'�M�ϥΤ��ئC�s�边�� '~e'�C\n");
    write("�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w\n");
    if( (functionp(callback) & FP_NOT_BINDABLE)==0 )
	callback = bind(callback, this_object());
    
    if( text )      // �W�[ text �o���ܼ�, for board's followup
    {
        write( text );
        input_to((: input_line :), text, callback);
        return 1;
    }
    input_to((: input_line :), "", callback);
    return 1;
}

private void input_line(string line, string text, function callback)
{
    if( line=="." ) {
        if( functionp(callback) & FP_OWNER_DESTED ) 
            write("�Ұʽs��Ҧ�������w�g�����F�M��J�����C\n");
        else
            evaluate(callback, text);
        return;
    } else if( line=="~q" ) {
        write("��J�����C\n");
        return;
    } else if( line=="~e" ) {
    } else
        text += line + "\n";
    input_to((: input_line :), text, callback);
}
