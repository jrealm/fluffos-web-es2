// open.c

#include <room.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping doors;
	string *dirs, dir, key;
	object key_ob;
	int i;

	if( !arg ) return notify_fail("�A�n��W����F��H\n");
	if( sscanf(arg, "%s with %s", arg, key) != 2 )
		return notify_fail("�A�n�Τ���F��W��H\n");
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
		if( !dir ) return notify_fail("�A�n��W����F��S\n");
	
		if( environment(me)->lock_door(dir, key_ob->query("lock")) ) {
			message_vision("$N�N" + doors[dir]["name"] + "��W�C\n", me);
			return 1;
		}
	}

	return 0;
}

int help(object me)
{
        write(@HELP
���O�榡 : lock <���~�Ϊ�> with <�_��..>
 
�o�ӫ��O�i�H���A��W�Y�Ǫ��ήe���C
 
HELP
    );
    return 1;
}
