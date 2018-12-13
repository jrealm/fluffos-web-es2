/*  post_office.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

inherit ROOM;

void create()
{
    set("short", "���F��");
    set("long", @LONG
�o�̬O���F���毸�M���M�毸�D�n�O���x�����e��ѡM���L�ѩ��~��
�g��j�s�X�S�W�c�M�]���֦ʩm�|��@�ǿ����毸���x�������e�H���H�A�쳱
�������O�{���g���Z���O�x�����I�F�ʥ��A�毸�Y�O�٦��ʩm�����A��b�O��
�����\�A���ʤU�O�����毸��ʩm���l���e�U�@�ߤ��o���O�C

�p�G�A�Q�n���o�H�A�i�H�� request �V�毸�x��������o�H���H���C
LONG
    );
    set("exits", ([ /* sizeof() == 1 */
        "east" : __DIR__"nstreet2",
    ]));
    set("post_office", 1);    // mailbox checks this flag.
    set("no_fight", 1);

    setup();
}

void init()
{
    add_action("do_request", "request");
}

int do_request(string arg)
{
    object mbox;

    if( objectp(mbox = this_player()->query_temp("mbox_ob"))
    &&	base_name(mbox)==MAILBOX_OB
    &&	environment(mbox)==this_player() )
        return notify_fail("�A�w�g�⦳�@�ӫH���F�C\n");

    mbox = new(MAILBOX_OB);
    mbox->move(this_player());

    write("�毸���x���N�@�Ӽg�ۧA�W�r���H�����F���A�C\n");
    return 1;
}

int
valid_leave(object ob)
{
    object mbox;

    if( objectp(mbox=ob->query_temp("mbox_ob")) ) {
	mbox->retire();
	write("�A�N�H����^���毸�x���O�ޡC\n");
	ob->delete_temp("mbox_ob");
    }

    return 1;
}
