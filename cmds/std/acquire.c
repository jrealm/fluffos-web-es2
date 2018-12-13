/*  acquire.c

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
    string skill, who;
    object ob;

    if( !arg || sscanf(arg, "%s from %s", skill, who)!= 2)
        return notify_fail("���O�榡�Racquire <�ޯ�W��> from <�H��>\n");

    if( !objectp(ob = present(who, environment(me))) )
        return notify_fail("�o�̨S���o�ӤH�C\n");

    // add by dragoon
    if( ob->query("no_fight") )
	return notify_fail("����??\n");

    if( !ob->query_skill(skill, 1) )
        return notify_fail(ob->name() + "�ä��|�o�اޯ�C\n");

    if( me->query_skill(skill, 1) > 0 )
        return notify_fail("�A�w�g�|�o�اޯ�F�C\n");

    // Produce proper message according to relation between player and teacher.
    if( me->is_apprentice_of(ob) ) {
        message_vision("$N�V$n�W�Y��§�M�����q�q�a���D�R�v���b�W�M�D�z�Ǳ®{��"
            + "�u" + to_chinese(skill) + "�v�T\n",
            me, ob);
    } else if( ob->query("age") > me->query("age") ) {
        message_vision("$N�V$n�}���U���M���D�R�߽�" + me->name() + "�M��e�����I"
            + me->rank("self") + "�u" + to_chinese(skill) + "�v�T\n",
            me, ob);
    } else {
        message_vision("$N�V$n�����§�M���D�R�гo��" + ob->rank("respectful") 
            + "���I" + me->rank("self") + "�u" + to_chinese(skill) + "�v�T\n",
            me, ob);
    }

    notify_fail("�ݰ_��" + ob->name() + "���Q�ЧA�o���ޯ�C\n");
    return ob->acquire_skill(me, skill);
}

int help()
{
    write(@TEXT
���O�榡�Racquire <�ޯ�W��> from <�H��>

�o�ӫ��O�i�H���A�V�Y�H�u�D�Сv�Y�اޯ�M���L����@���@�N�ЧA�M�ä��O�A�ۤv
�i�H�M�w���M�q�`�Z�L�H�h���|�����a�ЧA�Z�\�M�ӥB���ɭԧY�ϱЧA�M�]�����o�|
���n�۱¡C
TEXT
    );
    return 1;
}
