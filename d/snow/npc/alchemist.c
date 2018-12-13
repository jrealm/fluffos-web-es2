// alchemist.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("�����L", ({ "chen weisha", "weisha", "chen" }));
	set("nickname", "���s�~�h");
	set_attr("dex", 18);
	set_attr("int", 24);
	set_attr("wis", 25);
	set_attr("spi", 22);
	set_attr("cps", 19);
	set_attr("con", 20);
	set_race("human");
	set_level(30);
	set_class("alchemist");
	set_skill("unarmed", 60);
	set_skill("sword", 60);
	set_skill("parry", 80);
	set_skill("dodge", 70);
	set_skill("force", 70);
	set_skill("kee anatomy", 100);
	set_skill("dragon force", 60);
	set_skill("alchemy-medication", 140);
	set_skill("alchemy-wealth", 40);
	set_skill("alchemy-magic", 80);
	set_skill("alchemy-immortality", 30);
	map_skill("force", "dragon force");

	advance_stat("gin", 180);
	advance_stat("kee", 180);
	advance_stat("sen", 180);

	set("age", 55);
	set("long",
		"�����L�O�ӵۦW����h�M�g�`�ө���Ѩ���P�쳱���������ĤδM�V\n"
		"�é_�q���M�L�M���F�������~�O�¤�P���M�o�X��쥻�n�����Ϥs\n"
		"���ġM���O�]���s��v�h�ҥH�Ȯɦb�����~�a�L�ټƤ�C\n"
		"�����L���W���סM���L�O�L���ǥ̰ͭe���L���ٸ��M�N��O���L�۷�\n"
		"���L��M���w���ꤣ���M�Y���O�������~���W�l���F���i�ͤ��N�M\n"
		"�u�Ȧ��X��e�N�W���Ϥs�а��s��h�F�C\n");
	setup();
	carry_object(__DIR__"obj/silversword")->wield();
	carry_object("/obj/area/obj/cloth")->wear();
}

void set_flag(object me)
{
	if( me && present(me, environment()) ) {
		if( me->query_class() != "commoner"
		||	me->query("title") )
			return;
		me->set_temp("pending/alchemist", 1);
	}
	else
		do_chat("�����L���D�R�K ... �H�����F�M�ڳo���Y�٦b�ۨ��ۻy ...�C\n");
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;
	if( me->query_temp("pending/alchemist") ) return 1;
	if( me->query("title") ) {
		do_chat("�����L�D: �~���H, ���Ŧh�h�N������, �O�o��|�B���A�C\n");
		return 0;
	}
	do_chat(({
		"�����L���D�R���ڬ��v�S���� ... �ڥi���O����Z�L����r�C\n",
		"�����L��۫Υ~�X�F�|���M���D�R�ڥu�O�ӳ��w�Ҥ����ġB���ꤣ�������Y��C\n",
		"�����L���M���F�_�ӡM���D�R�u�Ҥ����ġB���ꤣ���v... ������...�C\n",
		"�����L���D�R�ڬݧA�o�~���H���ٶ����M�p�G�A���Ȱ��ǿN�����Ī��ʬ� ...\n",
		"�����L���D�R�ѤҪ��{���U�d�H�M�K�h�A�@�Ӥ]�����C\n",
		(: set_flag, me :)
	}));
	return 0;
}

int init_apprentice(object me)
{
	// add by dragoon
	if( me->query_class() != "commoner" ) {
		do_chat(({
			"�����L���D�R�A�J�w�J�O���M�Z���l�O�A�ߧڤ��N?\n",
			"�����L������M���D�R�h�a.....�C\n"
		}));
		return 1;
	}
	if( ::init_apprentice(me) ) {
                seteuid(getuid());
		me->set_class("alchemist");
		me->set("title", "�s�Ϥ����̤l");
		do_chat(({
			"�����L�I�F�I�Y�M���D�R�A���M�J�ڪ��U�M���O�o���N�����ĤQ�~�C\n",
			"�����L���D�R�Q�~����M�p�G���v�ݧA�ٳ��y�N�M�o�~�ǧA���N�C\n",
			"�����L�\\�F�\\��M���D�R�n�F�M�A���U�h�a�C\n"
		}));
	}
}

int acquire_skill(object ob, string skill)
{
	if( is_chatting() )
		return notify_fail("�A�̦n���L�ѤH�a���ܻ����A���L ...�C\n");
	if( !ob->is_apprentice_of(this_object()) ) return 0;

	switch(skill) {
	case "alchemy-medication":
		if( !ob->query_learn(skill)
		&&	ob->query_score("alchemy") >= 1000 ) {
			say("�����L�I�F�I�Y�A���D�G���v�o�N�ǧA�Ať�n�F�C\n");
			message_vision("$N�N�s�Ϥ��D�������A���N�j�n�Ǳµ�$n�C\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("wis")) + 1);
		}
		break;
	case "alchemy-wealth":
	case "alchemy-magic":
	case "alchemy-immortality":
	default:
		return 0;
	}

	do_chat(({
		"�����L���D�G�Z�ڤ�h���H�A�L���w�٥@�ϤH���v���C\n",
		"�����L���D�G���D�J�������A���O���᪺�׽m�~��}�l ...\n",
		"�����L���D�G�A�n���O���i�_�J������F���������y�A���X������~���X���ܡC\n",
		"�����L���D�G�Ʊ�A�n�۬����C\n",
	}));

	return 1;
}
