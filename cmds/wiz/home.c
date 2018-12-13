// home.c

#include "/doc/help.h"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string msg;

	seteuid(geteuid(this_player(1)));

	if( file_size(user_path(geteuid(me)) + "workroom.c") <= 0 ){
		message_vision("$N�V���H������, �^�a�h�F�C\n", me);
		me->move("/adm/guild/guildhall");
		message("tell_room", me->name() + "�^��F�ۤv���a���C\n", environment(me), me);
		return 1;
	}

	if( stringp(msg = me->query("env/msg_home")) )
		message_vision(msg + "\n", me);
	else
		message_vision("$N�V���H������, �^�a�h�F�C\n", me);
	me->move(user_path(geteuid(me)) + "workroom");
	message("tell_room", me->name() + "�^��F�ۤv���a���C\n", environment(me), me);
	return 1;
}

int help(object me)
{
  write(@HELP
���O�榡 : home

�Q�Φ��@���O�i�����^��ۤv���u�@��, �Y home directory ���L workroom.c ��, 
�h�^�� wiz guild �C �p�G�A workroom.c ���� 'msg_home' �o�ӳ]�w, �h�b�����H
���|�ݨ쨺�ӰT���C
HELP
    );
    return 1;
}
