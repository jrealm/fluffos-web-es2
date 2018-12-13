// open.c

#include <room.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping doors;
	string *dirs, dir;
	int i;

	if( !arg ) return notify_fail("�A�n���}����S\n");

	doors = environment(me)->query_doors();
	if( mapp(doors) ) {
		dirs = keys(doors);
		if( member_array(arg, dirs)!=-1 ) dir = arg;
		else for(i=0; i<sizeof(dirs); i++)
			if( arg==doors[dirs[i]]["name"] || member_array(arg, doors[dirs[i]]["id"])!=-1 ) {
				dir = dirs[i];
				break;
			}
		if( !dir ) return notify_fail("�A�n���}����S\n");
	
		if( environment(me)->open_door(dir) ) {
			message_vision("$N�N" + doors[dir]["name"] + "���}�C\n", me);
			return 1;
		}
	}

	return 0;
}

int help(object me)
{
        write(@HELP
���O�榡 : open <door> �� <��V>
 
�o�ӫ��O�i�H���A���}��.
 
HELP
    );
    return 1;
}
