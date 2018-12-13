/*  cestablish.c - to establish a clan

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/
#include <login.h>
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object who;

	if( !arg ) {
		if( me->query("level") < 50 
		|| me->query_score("reputation") < 60000 ) return 
			notify_fail("¥u¦³Án±æ°÷°ªªº³»¯Åª±®a¤~¦³«ØÀ°ªº¸ê®æ¡C\n");

		if( me->query("clan/create") ) return 
			notify_fail("¨C­Ó¤H¤@¥Í¥u¤¹³\\³Ð³y¤@¦¸·sÀ°¬£¡C\n");

		if( me->query("clan/clan_level") ) return 
			notify_fail("§A¤w¸g¬OÀ°¬£¦¨­û¤F, ½Ð¥ý²æÂ÷­ì¨ÓÀ°¬£¡C\n");

		if( me->query_temp("clan/sign_number") < 2 ) return
			notify_fail("§A¦Ü¤Ö±o§ä¨â­Ó°Æ¤â¨ÓÀ°¦£¤~¯à«ØÀ°¡C\n");
		write("¥Ø«e¤w¦³ªºÀ°¬£¦p¤U: \n\n");
		seteuid(ROOT_UID);
		write( read_file("/obj/CLAN") );
		write("\n¦bÀ°¦W¨M©w¤§«e, ¥iÀH®É¥H«ü¥O:q²æÂ÷«ØÀ°¤âÄò¡C½Ð\n");
		write("³Ð¤@¨ã­·®æªº¥þ·sÀ°¬£¡C½Ð¿é¤JÀ°¬£¦W: ");
		input_to("get_clan_name", me);
		return 1;
	}

	if( sscanf(arg, "with %s", arg) ) {
		if( me->query("level") < 44 ) return 
			notify_fail("§Aªºµ¥¯Å¤£¨¬¥H°Ñ»P«ØÀ°¡C\n");

		if( me->query("clan/clan_level") ) return 
			notify_fail("§A¤w¸g¬OÀ°¬£¦¨­û¤F, µLªkÀ°§U¥~¤H«ØÀ°¡C\n");

		if( me->query("clan/signed") ) return 
			notify_fail("§A¤w¸gÀ°¦£¦¨¥ß¹LÀ°·|¤F¡C\n");

		who = present(arg, environment(me));

		if( who == me ) return notify_fail("½Ð§ä¦Û¤v¥H¥~ªº¤HÀ°¦£¡C\n");

		if( !objectp(who) || !living(who) ) 
			return notify_fail("³o¸Ì¨S¦³³o­Ó¤H¡C\n");

		message_vision(HIW"$N¨M©w¨ó§U$n³Ð¥ß¤@­Ó·sÀ°¬£¡C\n"NOR
		, me, who);

		who->add_temp("clan/sign_number", 1);
		me->set("clan/signed", 1);
#ifdef SAVE_USER
        me->save();
#endif
		return 1; }
	else {
		tell_object(me, 
		"«ü¥O®æ¦¡: cestablish ©Î¬O cestablish with <¬Y¤H>\n");
		return 1;
	}
}

private void get_clan_name(string arg, object me)
{
        seteuid(getuid(me));
	me->set("clan/clan_name", arg);
	write("±z½T©w­n¥Î³o·í±zªºÀ°¬£¦W¶Ü(y/n/q)¡S");
	input_to("confirm_name", me);
}

private void confirm_name(string yn, object me)
{        
	if( yn=="" ) {
		write("±z½T©w­n¥Î³o·í±zªºÀ°¬£¦W¶Ü(y/n)¡S");
                input_to("confirm_name", me);
                return;
	}
	if( yn == "q" ) {
		write("¨º»ò....¤U¦¸§a¡C\n");
		return;
	}

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("¨º»ò½Ð­«·s¿é¤J±z·Q­nªºÀ°¬£¦W¦r: ");
                input_to("get_clan_name", me);
                return;
        }
	seteuid(ROOT_UID);
	// keep in /log/CLAN
	log_file("CLAN", sprintf("[%s] %s ¥Ñ %s(%s) ³Ð¥ß\n",
        ctime(time()), me->query("clan/clan_name"), me->name(),
        me->query("id")) );
	// write in /obj/CLAN for player to query clan data
	write_file("/obj/CLAN", sprintf("[%s] %s ¥Ñ %s(%s) ³Ð¥ß\n",
	ctime(time()), me->query("clan/clan_name"), me->name(),
	me->query("id")) );
	write("½Ð¿é¤J³o­ÓÀ°¬£»â¾É¤HªººÙ¸¹(¦p: À°¥D, ªù¥D, ´xªù): ");
	input_to("get_clan_rank", me);
}

private void get_clan_rank(string arg, object me)
{
	if( strlen(arg) > 4 ) {
		write("ºÙ¸¹¹Lªø, ½Ð­«·s¿é¤J: ");
		input_to("get_clan_rank", me);
	}
	seteuid(getuid(me));
	me->set("clan/rank", arg);
	me->set("clan/nick", "²Ä¤@¥N¤jÀY¥Ø");
	me->set("clan/clan_level", 3);
	me->set("clan/elder", 0);
	write("±z½T©w­n¥Î³o·í±zªºÀ°¬£ºÙ¸¹¶Ü(y/n)¡S");
	input_to("confirm_rank", me);
}

private void confirm_rank(string yn, object me)
{
	object mark;

	if( yn=="" ) {
		write("±z½T©w­n¥Î³o·í±zªºÀ°¬£ºÙ¸¹¶Ü(y/n)¡S");
                input_to("confirm_rank", me);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("¨º»ò½Ð­«·s¿é¤J±z·Q­nªºÀ°¬£ºÙ¸¹: ");
                input_to("get_clan_rank", me);
                return;
        }
#ifdef SAVE_USER
        me->save();
#endif
	message("system", HIW"¤Ñ´Â¤½§i: "+me->query("clan/clan_name")
	+"¤w¥Ñ"+me->name()+"³Ð¥ß§¹¦¨, ¶}©l©Û¦¬À°²³!!\n"NOR, users());
	mark = new("/obj/clan_symbol");
	mark->move(me);
	return;		
}


int help(object me)
{
write(@HELP
¥»«ü¥O¥Î³~¬°¦¨¥ßÀ°¬£, ·Q¦¨¥ßÀ°¬£ªº¤H(¥H¤U¥HÀ°¥DºÙ¤§)­º¥ý»Ý
§ä¤H(¥H¤U¥HÀ°²³ºÙ¤§)¨ó§U¤@°_¶i¦æ, ¤è¯à¦¨¥ß·sÀ°¬£¡C¦b¦¨¥ßÀ°
¬£¤§ªì, À°²³¤H¼Æ¥²»Ý¦b¨â¤H¥H¤W, ¦Ó¦U¶µ¦¨¥ßÀ°¬£¤§­­¨î½Ð°Ñ¾\
: help clan, «ü¥O®æ¦¡¦p¤U:
1. À°²³Ì
   cestablish with <¬Y¤H>
2. À°¥D
   cestablish
   ¨ÃÀH«ü¥Ü¶ñ¤JÀ°¬£¦U¶µ°ò¥»¸ê®Æ¡CÙ>
HELP
    );
    return 1;
}
