inherit BULLETIN_BOARD;

void create()
{
	set_name("XX�O", ({ "X board" }) );
	set("long", "���� XX �O");
	set("location", "/d/snow/X");
	set("board_id", "X");		//�Y�ɦW�� abc.c �h X �� abc
	set("capacity", 30);		//�O���j�p, ���`�ϰ� 30 
	setup();
	replace_program(BULLETIN_BOARD);
}
//�g�n�ᦹ�ɷ|�h�� /daemon/board �U��
//�O�o�b�� location room �� setup() �U�n�g load_object("/daemon/board/X");
