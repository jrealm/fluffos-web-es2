// miller.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("���j�T", ({ "miller" }));
	set_race("human");
	set_level(2);

	set("gender", "female");
	set("long",
		"���j�T�O�e�X�~�~�h��o�Ӧa�誺�M�ڻ��L���V�ҬO�¤������x�M���O\n"
		"�o�F�\\�W�I�Q����o�߱�d��M���O���j�T�ۤv�q���ӻ{�M�u���V�Ҧb\n"
		"�ʫ��g�ӡC\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}
