/*  object.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

varargs int
getoid(object ob)
{
    int id;

    if (!ob) ob = previous_object();
    sscanf(file_name(ob), "%*s#%d", id);
    return id;
}

// Get the owner of a file.  Used by log_error() in master.c.
string
file_owner(string file)
{
    string name, rest, dir;

    if (file[0] != '/') file = "/" + file;
    if (sscanf(file, "/u/%s/%s/%s", dir, name, rest) == 3) {
        return name;
    }
    return 0;
}

/*  creator_file()
 *
 *  �o�Ө�ƬO ES2 �w���t�Ϊ��֤ߡA�C��@�Ӫ���Q load ���ɭԡA�t�η|
 *  �N�o�Ӫ����ɦW�ǵ� simul_efun ���� creator_file() ��ơA�åB��
 *  �o�Ө�ƪ��Ǧ^�ȧ@�����@���� uid�C�b ES2 ���w���t�Τ��A����
 *  uid ��ܳo�Ӫ��󪺳̰��v��( ����i�H�g�� seteuid �Ӵ����έ��C�ۤv
 *  ���v�� )�A�o�ӳ̰��v���O��¥Ѫ����ɦW�M�w���A�]���A�]�i�H��ES2
 *  ���w���t�άO�ڰ�b�ɮ�Ū�g�v���ި�W�C
 *
 *  ES2 �ثe�� uid ���o��覡�аѦҵ{���X�������ѡC
 */
string
creator_file(string file)
{
    string *path, euid;

    path = explode(file, "/") - ({ "" });
    if( ! sizeof(path) )
	return 0;	/* �o�ӱ��p���Ӥ��|�o�͡A�u�O�w���U�@ */

    switch(path[0])
    {
	// ----------------------------------------------------------
	// �b /adm �M /cmds �U������֦��̰����v�� ROOT_UID�A�i�H����
	// ��ơC
	// ----------------------------------------------------------
	case "adm":
	case "cmds":	return ROOT_UID;

	// -----------------------------------------------------------
	// �}��ϰ쪺�v���� DOMAIN_UID�A�i���ܨϥΪ̪��ݩʡA������g�J
	// �ɮסC
	// -----------------------------------------------------------
	case "d":	return DOMAIN_UID;

	// -----------------------------------------------------------
	// �b /u �� /open �U������p�G�O�ѨϥΪ̸��J�A�h��o�ϥΪ̪���
	// �P�v���A�p�G���O�ѨϥΪ̸��J�A�h��o�M���J��������ۦP���v
	// ���C
	// -----------------------------------------------------------
	case "u":
	case "open":
	    if( this_player(1) ) euid = getuid(this_player(1));
	    if( !euid ) euid = geteuid(previous_object(1));
	    if( euid && euid != ROOT_UID ) return euid;
            return "NONAME";

	// ------------------------------------------------------------
	// �b /obj �U�������̰��v���Ѹ��J�Ӫ����v��(euid)�M�w�A���y
	// �ܻ��Ѩ㦳 ROOT_UID �v����������J�� /obj ����A�N�㦳 ROOT
	// �v���A�ѨϥΪ̸��J������N�㦳�ϥΪ̪��v���C�@��㦳 ROOT �v
	// ��������p�G�n���J /obj ����A�q�`�|�� seteuid ���A���v��
	// �A�i����J�C
	// ------------------------------------------------------------
	case "obj":
	    if( previous_object(1) ) return geteuid(previous_object(1));
	    return "NONAME";

	// ------------------------------------------------------------
	// ��L�ؿ��U�����󳣵��� MUDLIB_UID ���v��
	// ------------------------------------------------------------
	case "daemon":
	default:
	    return MUDLIB_UID;
    }
}

void
destruct(object ob)
{
    string err;

    if( !ob ) return;

    err = catch(ob->remove());

    if( err )
	log_file("destruct", sprintf("[%s] %O: %s", ctime(time()), ob, err));

    if( userp(ob)
    &&	(geteuid(previous_object())!=ROOT_UID)
    &&	(geteuid(previous_object())!=geteuid(ob)) ) {
	log_file("destruct", sprintf("[%s] %O: Destructed by %s denied\n",
	    ctime(time()), ob, err));
	error("Destruction denied.\n");
    }

    efun::destruct(ob);
}
