/*  disable.c

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
    object ob;
    mapping m;
    string sk, sk_m;

    if( !arg || !(ob = SKILL_D(arg)) || ob==SKILL_D("none") )
        return notify_fail("�A�n���Τ���ޯ�H\n");

    if( me->is_busy() )
        return notify_fail("�A���b���ۧO����, �L�k�M�ߡC\n");

    if (!me->query_learn(arg)) 
        return notify_fail("�A�ثe���|�o���ޯ�C\n");

    if( !function_exists("valid_enable", ob) ) {
        me->map_skill(arg, "none");
        write("�A�M�w�Ȯɰ���ϥΩҾǦ����u" + to_chinese(arg) + "�v���ޥ��C\n");
    } else {
	int c = 0;
	m = me->query_skill_map();
	foreach(sk, sk_m in m) {
	    if( sk_m==arg ) {
		me->map_skill(sk);
		write("�A�M�w����b�u" + to_chinese(sk) + "�v�譱����ϥΩҾǦ����u" + to_chinese(arg) + "�v���ޥ��C\n");
		c++;
	    }
	}
	if( !c ) {
	    write("�A�M�w����ϥΩҾǦ����u" + to_chinese(arg) + "�v���ޥ��C\n");
	    me->map_skill(arg, "none");
	}
    }

    return 1;
}

int help()
{
    write(@TEXT
���O�榡�Gdisable <�ޯ�>

�o�ӫ��O���A����ϥάY�اޯ�A�o�̩ҫ����ޯ�O����s�q���A�p�C�k�B�M�k
���A�p�G�A�n����ϥάY�ؼC�k���Z�\�A�u�n�� enable �]�w�C�k����L�Z�\�Y
�i�C

��L�������O�Genable�Bskills
TEXT
    );
    return 1;
}
