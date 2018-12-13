// close.c

#include <room.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping doors;
	string *dirs, dir;
	int i;

	if( me->is_busy() ) return notify_fail("�A�{�b�S���šT\n");
	if( !arg ) return notify_fail("�A�n��������S\n");

	doors = environment(me)->query_doors();
	if( mapp(doors) ) {
		dirs = keys(doors);
		if( member_array(arg, dirs)!=-1 ) dir = arg;
		else for(i=0; i<sizeof(dirs); i++)
			if( arg==doors[dirs[i]]["name"] || member_array(arg, doors[dirs[i]]["id"])!=-1 ) {
				dir = dirs[i];
				break;
			}
		if( !dir ) return notify_fail("�A�n��������S\n");
	
		if( environment(me)->close_door(dir) ) {
			message_vision("$N�N" + doors[dir]["name"] + "���W�C\n", me);
			return 1;
		}
	}

	return 0;
}

int help(object me)
{
        write(@HELP
���O�榡 : close <door> �� <��V>
 
�o�ӫ��O�i�H���A���W��.
 
HELP
    );
    return 1;
}
