/*  death_white.c

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
#include <npc.h>

inherit F_SOLDIER;

private void
create()
{
    set_name( HIW "�¥��w�N�x" NOR, "hell general white", "general", "white");
    set("nickname", HIW "�յL�`" NOR);
    set("title", HIW "�Ļ�Ϫ�" NOR);
    set("long", @LONG
�A�ݨ�@�ӤS���S�G�����y�N�x�A�@�ڪ��������Y���R��ݫe�A�Ⱖ�Ӳ��N�۩��A
�o�䪽�@�C
LONG
    );
    set_attr("str", 45);
    set_attr("con", 40);
    set_attr("dex", 40);
    set_attr("cor", 35);
    set_attr("cps", 45);
    set_attr("spi", 40);
    set_attr("wis", 35);
    set_attr("int", 30);

    set_race("human");
    set_class("soldier");
    set_level(70);
    advance_stat("gin", 300);
    advance_stat("kee", 300);

    set_skill("twohanded sword", 60);
    set_skill("blunt", 100);
    set_skill("sword", 100);
    set_skill("parry", 90);
    set_skill("unarmed", 80);
    set_skill("dodge", 90);
    set_skill("blade", 70);
    set_skill("berserk", 150);

    setup();

    add_temp("apply/attack", 100);
    add_temp("apply/defense", 100);
    add_temp("apply/intimidate", 100);
    add_temp("apply/wittiness", 100);
    add_temp("apply/damage", 50);
    add_temp("apply/armor", 100);
}

