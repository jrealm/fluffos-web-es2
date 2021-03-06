// steal.c

#include <ansi.h>
#include <login.h>

inherit F_CLEAN_UP;

private void compelete_steal(object me, object victim, object ob, int sp, int dp);

void create() {seteuid(getuid());}

int main(object me, string arg)
{
    string what, who;
    object ob, victim;
    int sp, dp, skill, forcesk;
    string stealer_class, stealer_race;

    stealer_class = me->query_class();
    stealer_race = me->query_race();
    forcesk = (me->query_skill("force", 1)/25) + 4;

    if( me->is_busy() ) return notify_fail("你現在沒有空﹗\n");

    if( me->query("life_form") == "ghost" )
	return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( environment(me)->query("no_fight") 
    || environment(me)->query("no_steal") )
	return notify_fail("這裡禁止行竊。\n");

    if( me->skill_mapped("stealing")==0 )
	return notify_fail("你必須使用 (enable) 妙手空空之技!\n");
                
    if( me->query_temp("stealing") )
	return notify_fail("你已經在找機會下手了﹗\n");

    if( !arg || sscanf(arg, "%s from %s", what, who)!=2 ) 
	return notify_fail("指令格式﹕steal <物品> from <人物>\n");

    victim = present(who, environment(me));
    if( !victim || victim==me || !victim->is_character() )
	return notify_fail("你想行竊的對象不在這裡。\n");
    if( !wizardp(me) && wizardp(victim) )
	return notify_fail("玩家不能偷巫師身上的東西。\n");

    // add by dragoon
    if( userp(victim) && !interactive(victim) ) 
	return notify_fail("這人現在不在線上。\n");

    // Don't let NPC steal NPC.
    if( !userp(me) && !userp(victim) )
	return 0;

/*
        if( userp(victim))
           { if(victim->query("level") < 5)
                return notify_fail("他等級太低, 不要偷他吧。\n"); }

        if( me->query("level") < 5)
           { if(userp(victim))
                return notify_fail("你等級太低, 長大點再出來偷竊吧。\n"); }     
*/
    if( !ob = present(what, victim) ) {
	object *inv;
        inv = all_inventory(victim);
        if( !sizeof(inv) )
            return notify_fail( victim->name() + "身上看起來沒有什麼值錢的東西好偷。\n");
                ob = inv[random(sizeof(inv))];
    }

    skill = me->query_skill("stealing");
    // change while to if -Dragoon
    if( me->query_stat("gin") < skill/3 )
        skill /= 2;
    me->consume_stat("gin", skill/3);

    // reset the power of steal -dragoon
    // steal技能低的時候, 本身的機敏和定力直接影響steal的能力, 當steal
    // 技能到達相當程度後, 技能對steal能力的影響開始高於屬性
    sp = skill*5 + (int)me->query("dex")*10 + (int)me->query("cps")*5;

    // 職業附加能力的提昇
    if( me->query("class") == "thief" ) 
	sp += skill*5 + (int)me->query("dex")*10;

    // 屬性和技能外為較固定的能力表現, 但不同小偷在技能及屬性練到頂點後
    // , 其steal能力的差異則由精的高低而有所差異, 精數值的高低對steal能
    // 力有不同層級的影響, 精越高, 能力呈二次級數上昇
    sp += 1 + (int)me->qeury_stat("gin")*(int)me->qeury_stat("gin")/600;
	    
    if( sp < 1 ) sp = 1;
    // jo一族賦與天生的能力, 能力與force相關, 但給與基本的能力乘數4, 即
    // force都沒練的狀況下, jo的steal能力還是比別人高出 (skill+dex)*4
    // 最高乘數為: 150/25+4=10, 以steal skill上限200, dex假設30, 整體steal
    // 能力比一般種族sp高出2300
    if( stealer_race == "jiaojao" ) 
	sp += (skill + (int)me->query("dex")) * forcesk;
    if( me->is_fighting() && stealer_race != "jiaojao" ) {
	sp /= 2;
        me->start_busy(3);
    }
    if( me->is_fighting() && stealer_race == "jiaojao" ) {
        me->start_busy(1);
    }

    dp = (int)victim->query_stat("sen") * 3 + (int)ob->weight() / 20;
    dp += (int)victim->qeury_stat("gin")*(int)victim->qeury_stat("gin")/700;
    
    if( stealer_race == "jiaojao" ) dp += (int)victim->query_stat("gin");
    if( victim->is_fighting() ) dp *= 2;
    if( ob->query("equipped") ) dp *= 3;
    // max dp for rr += 1500
    if ( victim->query("race") == "rainnar" ) {
	if ( present("black viper", victim) ) dp += 100;
        if ( present("red viper", victim) ) dp += 300;
        if ( present("green viper", victim) ) dp += 300;
        if ( present("white viper", victim) ) dp += 400;
        if ( present("yellow viper", victim) ) dp += 400;
    }

    write("你不動聲色地慢慢靠近" + victim->name() + "﹐等待機會下手 ...\n\n");

    me->set_temp("stealing", 1);
    me->delete_temp("pending/hidden");
    call_out((: compelete_steal :), 3, me, victim, ob, sp, dp);

    return 1;
}

private void compelete_steal(object me, object victim, object ob, int sp, int dp)
{
    if( !me ) return;

    me->delete_temp("stealing");

    if( !victim || environment(victim) != environment(me) ) {
	tell_object(me, "太可惜了﹐你下手的目標已經走了。\n");
        return;
    }

    if( victim->detect_steal(me, ob, sp) ) return;

    if( objectp(ob) && (!living(victim) || (random(sp+dp) > dp) )) {
	if ( ob->query("id") == "black viper"
        || ob->query("id") == "green viper"
        || ob->query("id") == "white viper"
        || ob->query("id") == "red viper"
        || ob->query("id") == "yellow viper" ) {
            tell_object(me, "你摸到一條" + ob->name() +
            "﹐牠張著一口毒牙向你咬來﹐嚇的你連退好幾步。\n");
            return;
        }
        if( ob->query("no_steal") ) {
            tell_object(me, "這東西不能偷。\n");
            return;
        }
        if( !ob->move(me) ) {
            tell_object(me, "你摸到一" + ob->query("unit") + ob->name()
                + "﹐可是對你而言太重了﹐不得不放棄。\n");
            return;
        }
        tell_object(me, HIW "得手了﹗\n\n" NOR);
        tell_object(me, "你成功\地偷到一" + ob->query("unit") + ob->name() + "﹗\n");
        if( living(victim) ) {
            int gain;
            me->improve_skill("stealing", me->query_attr("int"));
            gain = ob->query("value") / (me->query_skill("stealing")+50);
            if( gain > 100 ) gain = 100;
            me->gain_score("thievery", gain);
            if( userp(victim) )
                me->gain_score("mortal sin", random(me->query_skill("stealing") / 2) + 1 );
            }
            if( random(sp) < dp/2 )
                message("vision", "你看到" + me->name() + "鬼鬼祟祟地從"
                    + victim->name() + "身上偷走了一" + ob->query("unit")
                    + ob->name() + "﹗\n", environment(me), ({ me, victim }) );
#ifdef SAVE_USER
    victim->save();
#endif
	}
        else {
            if( !ob || random(sp) > dp/2 ) {
                if ( present("black viper", victim)
                || present("red viper", victim)
                || present("green viper", victim)
                || present("white viper", victim)
                || present("yellow viper", victim) ) {
                    tell_object(me, "嗤﹗地一聲﹐" + victim->name() + 
			"身上突然竄出一條昂首吐信的蛇﹐虎視眈眈著你﹗\n"
			"你嚇得趕緊縮手。\n");
                    return; 
		}
                else {
	            tell_object(me, victim->name() + "不經意地一轉頭﹐你急忙將手縮了回去﹗\n"
                         "還好﹐沒有被發現。\n");
                    return; 
		}
            }
            tell_object(me, HIR "糟糕﹗你失手了﹗\n\n" NOR);
            if ( present("black viper", victim)
            || present("red viper", victim)
            || present("green viper", victim)
            || present("white viper", victim)
            || present("yellow viper", victim) ) {
                message_vision("$N身上的蛇猛然咬向$n﹐讓$N驚覺$n的手正抓著$N的"
                + ob->name() + "﹗\n\n"
                +  "$N喝道﹕「幹什麼﹗」\n\n", victim, me); 
	    }
            else {
                message_vision("$N一回頭﹐正好發現$n的手正抓著$P身上的" + ob->name() + "﹗\n\n"
                        + "$N喝道﹕「幹什麼﹗」\n\n", victim, me);
            }
            me->improve_skill("stealing", random(me->query_attr("int")));
            me->gain_score("thievery", 1);
            if( userp(victim) ) victim->fight_ob(me);
        else {
                victim->accept_kill(me);
                victim->kill_ob(me);
        }
        me->fight_ob(victim);
        if( me->query_race() != "jiaojao" ) me->start_busy(3);
        if( me->query_race() == "jiaojao" ) me->start_busy(1);
    }
}

int help(object me)
{
write(@HELP
指令格式 : steal <某物> from <某人>

這個指令讓你有機會偷到他人身上的東西。成功了, 當然你就能獲得
該樣物品。可是, 馬有失蹄, 人總有失風的時候, 當你失敗時當然就
得付出代價, 至於是什麼代價......靠你自己去發掘囉。

當你是盜賊這個職業時，相對於其他的職業會有較高的偷盜能力，也
比較容易成功，甚至可以將目標的貼身衣物通通偷走，同樣的，對於
別人想動你身上東西的腦筋時，也比較容易察覺，當盜賊想要偷盜賊
的時候，這時就比看誰的功力高強了。

HELP
    );
    return 1;
}
