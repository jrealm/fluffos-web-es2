/*  skills.c

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
#include <skill.h>

inherit F_CLEAN_UP;

string *skill_level_desc = ({
    "��ǥE�m",
    "�ʳq�֤�",
    "�b�ͤ���",
    "�������",
    "�r���N��",
    "�X���޵�",
    "���G���",
    "�l���«C",
    "�X���J��",
    "�n�p�y��",
    "�`���i��"
});

string *knowledge_level_desc = ({
    "�s�ǥE��",
    "��s���|",
    "�����@�G",
    "�������",
    "�w���p��",
    "�o������",
    "���M����",
    "�߻⯫�|",
    "�W���ѤU",
    "�@�N�v�v",
    "�`���i��"
});

string skill_level(string, int);

mapping _skill;

int main(object me, string arg)
{
    object ob;
    mapping skl, lrn, map, flag;
    string *sname, *mapped, s, old_s, line, option;
    int show_all = 0;

    seteuid(getuid());

    ob = me;

    if( arg && arg!="" )
        foreach(option in explode(arg, " "))
            switch(option) {
            case "-a":
                show_all = 1;
                break;
            default:
                ob = present(option, environment(me));
                if (!ob) ob = find_player(option);
                if (!ob) ob = find_living(option);
                if (!ob) return notify_fail("�A�n��ݽ֪��ޯ�S\n");
                if( !wizardp(me)
                &&    !ob->is_apprentice_of(me)
                &&    !me->is_apprentice_of(ob)
                &&    !ob->accept_info(me, "skills") )
                    return notify_fail("�u���Ův�Φ��v�{���Y���H���ݥL�H���ޯ�C\n");
            }

    flag = ob->query_skill_flags();
    if( !mapp(flag) ) flag = ([]);

    skl = ob->query_skills();
    if( !mapp(skl) ) skl = ([]);

    lrn = ob->query_learned();
    if( !mapp(lrn) ) lrn = ([]);

    if(!sizeof(skl) && !sizeof(lrn)) {
        write( (ob==me ? "�A" : ob->name()) + "�ثe�èS���Ƿ|����ޯ�C\n");
        return 1;
    }

    line = (ob==me ? "�A" : ob->name()) +"�ثe���ޯબ�A�R\n\n";

    // This is a very tricky code that setup a mapping of effective skill
    // level and an array of skill names (>0).
    _skill = ([]);
    sname = filter_array(keys(skl) + keys(lrn),
        (: undefinedp($3[$1]) ? $3[$1] = $2->query_skill($1) : 0 :), ob, _skill );

    map = ob->query_skill_map();
    if( mapp(map) ) mapped = values(map);
    else mapped = ({});

    sname = sort_array( show_all ? keys(_skill) : sname,
        (: _skill[$2] - _skill[$1] :));

    foreach(s in sname )
    {
        if( flag[s] & SKILL_FLAG_ABANDONED ) {
            if( !show_all ) continue;
            line += CYN;
        }

        if( !show_all ) {
            if( !undefinedp(map[s]) ) {
                line += sprintf(HIY "  %-50s" NOR " - %-10s %3d",
                    to_chinese(s) + " - " + to_chinese(map[s]) + " (" + map[s] + ")",
                    skill_level(SKILL_D(s)->type(), skl[s]),
                    _skill[s]);
                if( _skill[s] != skl[s] )
                    line += sprintf( HIW " (%+d)" NOR, _skill[s] - skl[s]);
                line += "\n";
                continue;
            }
            if( member_array(s, mapped) >= 0 ) continue;
        }

        line += sprintf("%s%-50s" NOR " - %-10s %3d", 
            (member_array(s, mapped)==-1? "  ": HIY "��"),
            to_chinese(s) + " (" + s + ")",
            skill_level(SKILL_D(s)->type(), skl[s]),
            _skill[s]
        );
        if( _skill[s] != skl[s] )
            line += sprintf( HIW " (%+d)" NOR, _skill[s] - skl[s]);
        line += "\n";
    }

    this_player()->start_more(line);
    return 1;
}

string skill_level(string type, int level)
{
    int grade;

    grade = sqrt(level/3);

    switch(type) {
        case "knowledge":
            if( grade >= sizeof(knowledge_level_desc) )
                grade = sizeof(knowledge_level_desc)-1;
            return knowledge_level_desc[grade];
        default:
            if( grade >= sizeof(skill_level_desc) )
                grade = sizeof(skill_level_desc)-1;
            return skill_level_desc[grade];
    }
}

int help(object me)
{
    write(@HELP
���O�榡 : skills [-a][<�Y�H>]

�o�ӫ��O�i�H���A�d�߾ǹL���ޯ�, ��i�d���M�A���v�{���Y����H���ޯબ�p�C
skill -a  �i�H�C�X�Ҧ��ǹL���ޯ�, �L�׬O�_�m�� 1 ���H�W�C

��A�b�� skill �W�� enable �Z�N��, �u�����Ī��O�����᪺��, �ҥH�A�Y�ݨ�
���\ (force) ... 145 (-5), �h��ܧA (�򥻤��\ + ���\�Z�N)/2 == 145,
�ӹ�ڪ��򥻤��\�� 150, ���\�Z�N�� 140�C ( �Y���p���I�i��, �h�|�t 1 �� )

�Ův�i�H�d�ߥ���H�� NPC ���ޯબ�p�C

HELP
    );
    return 1;
}
