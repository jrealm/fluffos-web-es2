/*  gain.c

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

int main(object me, string arg)
{
    string term, txt;
    int g;
    mapping score_g, skill_g;

    score_g = me->query_score_gain();
    me->reset_score_gain();
    skill_g = me->query_skill_gain();
    me->reset_skill_gain();

    txt = "�q�A�W���ϥ� gain ���O�A��{�b����A�A�@��o�G\n\n";
    
    txt += "�g���I�ơG\n";
    if( !sizeof(score_g) )
	txt += "    �L�C\n";
    else {
	foreach(term, g in score_g)
	    txt += sprintf("    %-16s %+d �I\n",
		to_chinese("score of " + term), score_g[term] );
    }

    txt += "\n�ޯ��I�ơG\n";
    if( !sizeof(skill_g) )
	txt += "    �L�C\n";
    else {
	foreach(term, g in skill_g)
	    txt += sprintf("    %-16s %+d �I\n",
		to_chinese(term), skill_g[term] );
    }

    write(txt);
    return 1;    
}

int help()
{
    write(@TEXT
���O�榡�Ggain

�o�ӫ��O�i�H�Ψ�����A���H�������A�C���A���H����o����g���I�ƩΧޯ��I�ơA�t
�η|�O������o���ȡA��A�ϥ� gain ���O�A�|��ܳo�ǭȡA�M��M���o�Ǭ����q�Y�}
�l�A�A�i�H�b�԰��}�l�e���� gain �M���A�M��b�԰�������� gain �˵��A���H���q
��誺�԰����򪺦h�ֶi�B�C
TEXT
    );
    return 1;
}
