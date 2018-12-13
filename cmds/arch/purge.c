/*  purge.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#define SYNTAX	"���O�榡�Rpurge [<���W�u�Ѽ�>] | <�ϥΪ̩m�W> because <��]>\n"
#define SAVE_EXTENSION ".o"

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

private int do_purge_players(int day);

int
main(object me, string arg)
{
    string name, reason;
    int day;
    object ob, link_ob;

    SECURED_ARCH_COMMAND;

    if( !arg ) return notify_fail(SYNTAX);

    if( sscanf(arg, "%d", day) && day >= 100) return do_purge_players(day);

    if( day>0 && strsrch(arg, "!")>-1 )    return do_purge_players(day);
    
    if( sscanf(arg, "%s because %s", name, reason)!=2 )
        return notify_fail(SYNTAX);

    seteuid(getuid());
    if( file_size(DATA_DIR + "login/" + name[0..0] + "/" + name + SAVE_EXTENSION)<0 )
        return notify_fail("�S���o��ϥΪ̡C\n");

    ob = find_player(name);    // return include link dead player
    if( ob ) {
        link_ob = ob->link();
        // show message to users by dragoon
        message("system", HIY"\n"+ob->name()+"("+ob->query("id")+")���ɮצ] "
            +reason+" �Q"+me->name()+"�R���F�C\n\n"NOR, users());
        if( link_ob ) {
            destruct(link_ob);
        }
        destruct(ob);
    }

    rm(DATA_DIR + "login/" + name[0..0] + "/" + name + SAVE_EXTENSION);
    rm(DATA_DIR + "user/" + name[0..0] + "/" + name + SAVE_EXTENSION);
    rm(DATA_DIR + "user/" + name[0..0] + "/" + name + SAVE_EXTENSION + ".backup");
    write( "�ϥΪ� " + capitalize(name) + " �R�����F�C\n");
    log_file("static/PURGE", sprintf("[%s] %s purged %s because %s.\n",
        ctime(time())[0..15], geteuid(this_player(1)), name, reason));

    return 1;
}

private int
do_purge_players(int day)
{
    int i, j, ppl_cnt, count;
    string *dir, *ppls, name;
    mixed info;

    seteuid(getuid());
    message("system", "\n*** ��z���a�x�s�ɤ��M�еy��.... ***\n", users());
    write("�B�z���R");
    count = 0;
    ppl_cnt = 0;
    dir = get_dir(DATA_DIR + "login/");
    for(i=0; i<sizeof(dir); i++) {
        reset_eval_cost();
        write(dir[i]);
        ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
        ppl_cnt += sizeof(ppls);
        for(j=0; j<sizeof(ppls); j++) {
            if( sscanf(ppls[j], "%*s.backup")==1 ) continue;
            if( sscanf(ppls[j], "%s.o", name)==1 )
                if( (string)SECURITY_D->get_status(name)!="(player)" )
                    continue;
            info = stat(DATA_DIR + "login/" + dir[i] + "/" + ppls[j]);
            if( (time()-(int)info[1])/86400 >= day ) {
                rm(DATA_DIR + "login/" + dir[i] + "/" + ppls[j]);
                rm(DATA_DIR + "user/" + dir[i] + "/" + ppls[j]);
                rm(DATA_DIR + "user/" + dir[i] + "/" + ppls[j] + ".backup");
                count ++;
            }
        }
    }
    write("\n\n����`�@�� " + ppl_cnt + " ��ϥΪ̡C\n");
    write( count + " �ӶW�L " + day + " �ѥ��W�u���ϥΪ̳Q�M�����F�C\n");
    write("�{�b�`�@�� " + (ppl_cnt - count) + " ��ϥΪ̡C\n");
    log_file("static/PURGE", sprintf("[%s] %s cleaned up %d characters who didn't login for more than %d days\n"
        "\t\tResulting statistics: %d characters remaining.\n",
        ctime(time())[0..15], geteuid(this_player(1)), count, day, ppl_cnt - count));


    return 1;
}

int help(object me)
{
write(@HELP
���O�榡�Rpurge [<���W�u�Ѽ�>] | <�ϥΪ̩m�W> because <��]>

�M���@�ӨϥΪ�(���ި�O�_�b�u�W)���Ҧ��ɮ�, �βM���W�L�@�w�ѼƤ����W�u�̡C
rules �ȩw�̤p�����W�u�ѼƬ� 100, �� purge  �p�󦹤ѼƮ�, �Щ�Ѽƫ�[ "!"
��:
purge 120
purge 90 !
purge annihilator because �ӲV
HELP
    );
    return 1;
}
