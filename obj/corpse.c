/*  corpse.c - the coprse object

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit ITEM;

static int decayed = 0;
static int decay_interval = 120;

void create()
{
    set_name("�L�W����", ({ "corpse" }) );
    set("long", "�o�O�@��L�W����C\n");
    set("unit", "��" );
    setup();
}

void
start_decay(int interval)
{
    if( interval < 1 ) interval = 0;

    decay_interval = interval;

    remove_call_out("decay");
    decayed = 0;
    call_out("decay", decay_interval * 2);
}

int is_corpse() { return decayed < 2; }
int is_character() { return decayed < 1; }

string short() { return name() + "(" + capitalize(query("id")) + ")"; }

void decay()
{
    switch(++decayed) {
        case 1:
            say( query("name") + "�}�l�G��F�M�o�X�@�����D���c��C\n" );
            switch(query("gender")) {
                case "male":
                    set_name("�G�ꪺ�k��", ({ "corpse" }) );
                    break;
                case "female":
                    set_name("�G�ꪺ�k��", ({ "corpse" }) );
                    break;
                default:
                    set_name("�G�ꪺ����", ({ "corpse" }) );
                    break;
            }
            set("long", "�o�������M�w�g���b�o�̦��@�q�ɶ��F�M�����o�ۤ@�ѻG�ͪ����D�C\n");
            call_out("decay", decay_interval);
            break;
        case 2:
            say( query("name") + "�Q���j���F�M�ܦ��@���e���C\n" );
            set_name("�\\�����e��", ({ "skeleton" }) );
            set("long", "�o���e���w�g���b�o�̫ܤ[�F�C\n");
            call_out("decay", decay_interval);
            break;
        case 3:
            say( "�@�}���j�L�M��" + query("name") + "�Ʀ����ǧj���F�C\n" );
            destruct(this_object());
            break;
    }
}

int receive_object(object oob, int from_inventory) { return 1; }
