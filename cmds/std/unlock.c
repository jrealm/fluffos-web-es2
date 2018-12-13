// open.c

#include <room.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping doors;
	string *dirs, dir, key;
	object key_ob;
	int i;

	if( !arg ) return notify_fail("�A�n�}����F�誺��H\n");
	if( sscanf(arg, "%s with %s", arg, key) != 2 )
		return notify_fail("�A�n�Τ���F��}��H\n");
	if( !objectp(key_ob = present(key, me)) )
		return notify_fail("�A���W�S���o�تF��C\n");

	doors = environment(me)->query_doors();
	if( mapp(doors) ) {
		dirs = keys(doors);
		if( member_array(arg, dirs)!=-1 ) dir = arg;
		else for(i=0; i<sizeof(dirs); i++)
			if( arg==doors[dirs[i]]["name"] || member_array(arg, doors[dirs[i]]["id"])!=-1 ) {
				dir = dirs[i];
				break;
			}
		if( !dir ) return notify_fail("�A�n�}����F�誺��H\n");
	
		if( environment(me)->unlock_door(dir, key_ob->query("lock")) ) {
			message_vision("$N�N" + doors[dir]["name"] + "�W���ꥴ�}�C\n", me);
			return 1;
		}
	}

	return 0;
}

int help(object me)
{
        write(@HELP
���O�榡 : unlock <���~�Ϊ�> with <�_��>
 
�o�ӫ��O�i�H���A���}��۪����ήe���C
 
HELP
    );
    return 1;
}
