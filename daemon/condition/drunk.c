/*  drunk.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit CONDITION;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("drunk");
}

void condition_update(object me, string cnd, mixed cnd_data)
{
    object *inv, ob, target;
    int drunk_cap;

    if( !intp(cnd_data) || cnd_data < 1 || !living(me) ) {
        me->delete_condition(cnd);
        return;
    }

    drunk_cap = me->query_attr("spi", 1) * me->query_stat_maximum("water") / 100;
    drunk_cap += me->query_skill("force");

    if( cnd_data >= drunk_cap ) {
        me->unconcious(" <��K�p�d>");
        cnd_data = 0;
    } else if( cnd_data >= drunk_cap / 2 ) {
        switch(random(5)) {
        case 0:
            message_vision("$N�K�o�@�Ͻk��A�u�z�v�a�@�n�R�F�@�a���O�A�� ...\n", me);
            me->consume_stat("food", cnd_data + random(cnd_data));
            cnd_data -= random(cnd_data);
            break;
        case 1:
            message_vision("$N�K�o�k�̽k��A�N���W�F��@����F�U�ӡI\n", me);
            inv = all_inventory(me);
            inv->unequip();
            break;
        case 2:
            if( (ob = present("coin_money", me))
            ||	(ob = present("silver_money", me))
            ||	(ob = present("gold_money", me)) ) {
                message_vision("$N�K�o�äC�K�V�A�N���W�Ȩ�ɿ��u�M�աv�@�n���F���a�I\n", me);
                ob->move(environment(me));
                break;
            }
        case 3:
            me->unconcious(" <��K�p�d>");
            cnd_data = 0;
            break;
        default:
            cnd_data -= 1;
            me->supplement_stat("kee", me->query_attr("con"));
            break;
        }
    } else if( cnd_data > drunk_cap / 4 ) {
        switch(random(5)) {
        case 0:
            message_vision("$N�}�U�@�Ӥ�í�A�B�N�@�n�L�F�@��I\n", me);
            me->damage_stat("kee", random(5)+1);
            cnd_data -= 10;
            break;
        case 1:    // Randomly drop something ... :P
            inv = all_inventory(me);
	    // �����D, �����H�����]��no_drop������ᱼ -Dragoon
	    // inv[random(sizeof(inv))]->move( environment(me) );
	    target = inv[random(sizeof(inv))];
	    if( !target->query("no_drop") )
		target->move( environment(me) );
            break;
        case 2:
            message_vision("$N�K�A�i�šA�̨̧r�r�a�۰_�q�ӡC\n", me);
            break;
        default:
            cnd_data -= 1;
            me->supplement_stat("kee", me->query_attr("con")/2 );
            break;
        }
    } else if( cnd_data > drunk_cap / 8 ) {
        switch(random(10)) {
        case 0:
            message_vision("$N���y�q���A�u�c�v�a�@�n���F���СC\n", me);
            cnd_data -= 3;
            break;
        case 1:
            message_vision("$N�s�N�W��A�|�F�|�����C\n", me);
            break;
        default:
            cnd_data -= 1;
	    // �L�K���A��𯫪��A�Ȫ���_�O���`���T���C
            me->heal_stat("gin", me->query_attr("dex") / 3 );
            me->heal_stat("kee", me->query_attr("con") / 3 );
            me->heal_stat("sen", me->query_attr("spi") / 3 );
            break;
        }
    }
    else cnd_data -=1;

    me->set_condition(cnd, cnd_data);
}

void apply_drunk(object me, int drunkness)
{
    int drunk, drunk_cap;

    drunk = me->query_condition("drunk") + drunkness;

    drunk_cap = me->query_attr("spi", 1) * me->query_stat_maximum("water") / 100;
    drunk_cap += me->query_skill("force");

    me->set_condition("drunk", drunk);
    if( drunk >= drunk_cap / 2 )
        tell_object(me, "�A�w�g�ܱo�ѱۦa��A�n�n���Y�F�A�A�ܤU�h�w�|�K�ˡC\n");
    else if( drunk >= drunk_cap / 4 )
        tell_object(me, "�A�w�g���C���K�N�F�A�����ݥX�h���O�a�g�g���@���C\n");
    else if( drunk >= drunk_cap / 8 )
        tell_object(me, "�Aı�o���ǾK�N�F�C\n");
}

