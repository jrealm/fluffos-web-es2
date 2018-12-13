/*  poison.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("poison");
}

/*
    �o�Ӥ��r�g���O�@��ʪ��A�Ϊ�������g�өw�q�r���ʽ�A�H��|��N���H�i�H�E�_
    �X�r���ʽ�A�}�ĸѬr�C

    �@��Ө��A�i�H�ۥѩw�q�r���������ݩʡA�H�U�����u�ѰѦҡG

    �� - �q�����r�A�C���o�@�|�l�˯������A�ȡC
    �� - ��줧�r�A���o���r���H�����ʷ|���C�C
    �� - ���ʤ��r�A�C���o�@�|�l�˺몺���A�ȡC
    �� - ���ʤ��r�A�C���o�@�|�l�ˮ𪺪��A�ȡC
    �g - �γD���r�A���o���r���H���M�O�|���C�C

    �@�جr���q�`�Ѥ��椤����T�ةʽ�c���A�p�ڭ̩w�q�Y�سD�r�O[�g 10, �� 10]�A
    ���Ī��v���o�سD�r�N�ݭn�Ϋg��g�M�����զX�ӹ�I�A�]���ݭn�@�ةʽ謰[�� 10,
    �g 10]���Ī��~��Ѭr�C

    ���r�g���t�~�i�H�w�q�X�ӰѼơG

    duration	- ����ɶ��A�C�o�@�@���N��@�A��� 0 �r�ʴN�����C
    damage	- �r�ʵo�@�Ҧ��ͩR�I�ơC
		  �ˮ`�O�O�b update_condition ���@�ΡA�ݺC�ʶˮ`�C
*/

void
condition_update(object me, string cnd, mixed cnd_data)
{
    // �u�� living ���ͩR���A�|����r���v�T�C
    if( me->query("life_form") != "living"
    ||	!mapp(cnd_data)
    ||	(cnd_data["duration"]--) < 1 ) {
	me->delete_condition(cnd);
	return;
    }

    if( cnd_data["damage"] )
    {
	int dam = cnd_data["damage"];

	tell_object(me, "�A�����r�o�@�F�C\n");

	dam -= random( me->query_temp("apply/resist_poison") );
	if( dam < 0 ) dam = 0;

	me->consume_stat("HP", dam);
	if( cnd_data["��"] > 0 ) me->damage_stat("gin", cnd_data["��"] );
	if( cnd_data["��"] > 0 ) me->damage_stat("kee", cnd_data["��"] );
        if( cnd_data["��"] > 0 ) me->damage_stat("sen", cnd_data["��"] );
    }
    me->set_condition("poison", cnd_data);
}
/*
void
condition_apply(object me, string cnd, mapping cnd_data)
{
    if( ! mapp(cnd_data) ) return;
    if( cnd_data["damage"] && cnd_data["�g"] )
	me->add_temp("apply/str", - cnd_data["�g"]);
    if( cnd_data["damage"] && cnd_data["��"] )
	me->add_temp("apply/int", - cnd_data["��"]);
}

void
condition_unapply(object me, string cnd, mapping cnd_data)
{
    if( ! mapp(cnd_data) ) return;
    if( cnd_data["damage"] && cnd_data["�g"] )
	me->add_temp("apply/str", cnd_data["damage"]);
    if( cnd_data["damage"] && cnd_data["��"] )
	me->add_temp("apply/int", cnd_data["damage"]);
}
*/

