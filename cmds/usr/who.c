/*  who.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>
//#include <net/dns.h>

inherit F_CLEAN_UP;

object *all, *target;
string msg;
int i, j;

void msg_format(string arg);

void create() { seteuid(getuid()); }

mixed main(object me, string arg, int remote)
{
    int center_lv;

    target = ({});
    msg = "";

    /* ���L�o�|���n�J�������ϥΪ̡A�P���Ϊ��W�ŧŮv�C
     * �`�N�b�Q rwho_q �I�s�����p�U�Athis_player() �� 0�C
     */
    if( this_player(1) )
	all = filter(users(), (:
	    objectp(environment($1))
	    && (!wizardp($1) || wiz_level($2)>wiz_level($1) || $1->visible($2))
	:), this_player(1));
    else
	all = filter(users(), (: objectp(environment($1)) && !wizardp($1) :));

    i = sizeof(all);
    
    if( !arg || arg=="" ) {
	center_lv = me->query_level();
        while( i-- ) {
            if( all[i]->query("level") - center_lv < 6
            &&  center_lv - all[i]->query("level") < 6
            && !wizardp(all[i]) )
                target += ({ all[i] });
        }
        msg_format("1");
    } else {
        switch(arg){
        case "-l":
            if( me->is_character() && !wizardp(me) ) {
                write("���F��C�t�έt��, �ثe�u���Ův�i�H�ϥ� who -l�C\n");
                return 1;
            }
            target = all;
            msg_format("5");
            break;
	case "-1":
	    target = filter(all, (:($1->query_level()-1)/10==0 && !wizardp($1) :));
            msg_format("1");
            break;
	case "-2":
	    target = filter(all, (:($1->query_level()-1)/10==1 && !wizardp($1) :));
            msg_format("1");
            break;
        case "-3":
	    target = filter(all, (:($1->query_level()-1)/10==2 && !wizardp($1) :));
            msg_format("1");
            break;
        case "-4":
	    target = filter(all, (:($1->query_level()-1)/10==3 && !wizardp($1) :));
            msg_format("1");
            break;
        case "-5":
	    target = filter(all, (:($1->query_level()-1)/10==4 && !wizardp($1) :));
            msg_format("1");
            break;
	case "-w":
	    target = filter(all, (: wizardp :));
            msg_format("5");
            break;
        case "-i":
            msg_format("41");
            break;
        case "-n":
            msg_format("42");
            break;
        case "-bh":
	    target = filter(all, (: $1->query_race()=="blackteeth" :));
	    msg_format("50");
	    break;
        case "-hn":
	    target = filter(all, (: $1->query_race()=="human" :));
	    msg_format("50");
	    break;
	case "-wn":
	    target = filter(all, (: $1->query_race()=="woochan" :));
	    msg_format("50");
	    break;
        case "-jo":
	    target = filter(all, (: $1->query_race()=="jiaojao" :));
	    msg_format("50");
	    break;
        case "-yd":
	    target = filter(all, (: $1->query_race()=="yenhold" :));
	    msg_format("50");
	    break;
        case "-rr":
	    target = filter(all, (: $1->query_race()=="rainnar" :));
	    msg_format("50");
	    break;
        case "-aa":
	    target = filter(all, (: $1->query_race()=="ashura" :));
	    msg_format("50");
	    break;
        case "-hs":
	    target = filter(all, (: $1->query_race()=="headless" :));
	    msg_format("50");
	    break;
        case "-ya":
	    target = filter(all, (: $1->query_race()=="yaksa" :));
	    msg_format("50");
	    break;
        case "-ml":
	    target = filter(all, (: $1->query_race()=="malik" :));
	    msg_format("50");
	    break;
        case "-at":
	    target = filter(all, (: $1->query_class()=="alchemist" :));
	    msg_format("50");
	    break;
        case "-cr":
	    target = filter(all, (: $1->query_class()=="commoner" :));
	    msg_format("50");
	    break;
        case "-fr":
	    target = filter(all, (: $1->query_class()=="fighter" :));
	    msg_format("50");
	    break;
        case "-sr":
	    target = filter(all, (: $1->query_class()=="soldier" :));
	    msg_format("50");
	    break;
        case "-tf":
	    target = filter(all, (: $1->query_class()=="thief" :));
	    msg_format("50");
	    break;
        case "-tt":
	    target = filter(all, (: $1->query_class()=="taoist" :));
	    msg_format("50");
	    break;
        case "-sc":
	    target = filter(all, (: $1->query_class()=="scholar" :));
	    msg_format("50");
	    break;
	default :
	    if( objectp(me) && wizardp(me)
	    &&  arg[0]=='@' ) {
		//RWHO_Q->send_rwho_q(arg[1..sizeof(arg)], me, 0);
		write("�����T���w�e�� " + arg[1..sizeof(arg)] + " �еy�ԡC\n");
		return 1;
	    }
	    return notify_fail("���O�榡��s�R�Ь� help who�C\n");
        }
    }

    msg = sprintf("�� %s\n"
	"�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w\n"
	"%s�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w\n"
	"�@�C�X %d/%d ��ϥΪ̡M�t�έt���R%s\n",
	MUD_NAME, msg, sizeof(target), sizeof(all), query_load_average());

    if( me && me->query_stat_current("sen") > 5 )
        me->consume_stat("sen", 5);
    
    if( remote ) return msg;

    me->start_more(msg);
    return 1;
}

int sort_user(object ob1, object ob2)
{
    int ord;

    ord = wiz_level(ob1) - wiz_level(ob2);
    if( ord==0 )
        ord = (int)ob1->query_level() - (int)ob2->query_level();
    return ord;
}

void msg_format(string arg)
{
    if( !arg || arg=="" )    return;

    j = sizeof(target);
    target = sort_array(target, "sort_user", this_object());

    switch(arg){
    case "1":
    case "5":
    case "50":
        // detail message
        while( j-- ) {
            // <ansi.h> will confuse sprintf's format
            if( wizardp(target[j]) )
                msg = sprintf("%s%s�i %|10s �j%+42s %-14s%s\n",
                    msg,
                    BOLD,
                    target[j]->rank(),
                    (target[j]->query("title") ? target[j]->query("title") : "") + (target[j]->query("nickname") ? "�u"+ target[j]->query("nickname") +"�v" : "") + (target[j]->query("name", 1)),
                    "(" + capitalize(target[j]->query("id")) + ")",
                    NOR
                );
            else
      		msg = sprintf("%s�i %2d%|8s �j%-12s%30s %-14s\n",
                    msg,
                    target[j]->query_level(),
                    target[j]->rank(),
                    target[j]->query("title") ? target[j]->query("title") : "",
		    (target[j]->query("nickname") ? "�u"+ target[j]->query("nickname") +"�v" : "")
			+ target[j]->query("name", 1),
                    "(" + capitalize(target[j]->query("id")) + ")",
                );
        }
        break;
    case "41":
        // who i, id of all
        target = sort_array(all, "sort_user", this_object());
        j = sizeof(target);
        while( j-- ) {
            msg = sprintf("%s%-13s%s",
                msg,
                capitalize(target[j]->query("id")),
                (( i - j ) % 6 ) ? "" : "\n"
            );
        }
        if( i % 6 )    msg += "\n";
        break;
    case "42":
        // who n, name of all
        target = sort_array(all, "sort_user", this_object());
        j = sizeof(target);
        while( j-- ) {
            msg = sprintf("%s%-13s%s",
                msg,
                target[j]->query("name", 1),
                (( i - j ) % 6 ) ? "" : "\n"
            );
        }
        if( i % 6 )    msg += "\n";
        break;
    default:
        msg = "Error at msg_format.\n";
    }
}

int help(object me)
{
    write(@HELP
���O�榡 : who [�ﶵ]
�o�ӫ��O�i�H�C�X�b�u�W���ϥΪ̤Ψ䵥��������T�C�� > 5 �ɷ|�l���C
�ﶵ���U�C�X��, �@���u�i�ϥΤ@�ؿﶵ, �Y who -i -w ���P who -i�C

    �L�ﶵ��, �C�X�P�A���Ŭۮt 5 �ťH�����ϥΪ̡C
-1    �C�X����  1 �쵥�� 10 ���ϥΪ̡C
-5    �C�X���� 41 �쵥�� 50 ���ϥΪ̡C
-w    �u�C�X�Ův, ���t�γ]�p�W�����D�лP�Ův���q�C
-i    �u�C�X�ϥΪ̭^�� id�C
-n    �u�C�X�ϥΪ̤���W�١C
-l    �C�X�Ҧ��ϥΪ̸ԲӸ�T (�Ův�M��)�C

-hn    �C�X race ��  human ���ϥΪ̡C    bh => blackteeth
    hn => human        wn => woochan    jo => jiaojao    yd => yenhold
    rr => rainnar    aa => ashura    hs => headless    ya => yaksa
    ml => malik
-at    �C�X class �� alchemist ���ϥΪ̡C
    at => alchemist    cr => commoner    fr => fighter    sr => soldier
    tf => thief        tt => taoist	 sc => scholar

�������O�R finger
HELP
    );
    if( wizardp(me) )
	write(@HELP
�Ův�i�H�Q�� who @celestial.empire  �ӱo����L�s�u�����u�W�H��, �w�s�u���i
�Hmudlist �o���C
HELP
	);
    return 1;
}
