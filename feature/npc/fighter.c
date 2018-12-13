// fighter.c

#include <attack.h>
#include <statistic.h>

// prototypes
mixed do_chat(mixed chat);
varargs string name(int raw);
void kill_ob(object ob);
varargs int is_fighting(object ob);
int query_level();
string rank(string politeness);

int accept_fight(object ob)
{
    if( is_fighting() ) {
        int differ;

        differ = query_level() - (int)ob->query_level();
        if( differ > 10 ) {
            do_chat( name() + "���ۻ��D�R�K�K ... �ӤF����ܡS\n");
            return 1;
        } else if( differ > 5 ) {
            do_chat( name() + "���D�R�K�K ... " + rank("self") + "���ѭn�ӭӥH�������T\n");
            return 1;
        } else {
            do_chat( name() + "���D�R�o��" + ob->rank("respectful") + "���D�O�Q�ʦh���ӡS\n");
            return 0;
        }
    }

    if( ob->is_fighting() ) {
	do_chat( name() + "���D�G���R�Z���A�٬O�楴�W�����n�A�ڥ��b�@�Ǳ��}�a�C\n");
	return 0;
    }

    if( query_stat_current("kee") < query_stat_maximum("kee") ) {
	do_chat( name() + "���D�G���|��A���ڳݤf��C\n");
	return 0;
    }

    do_chat( name() + "���D�R�����M�н�ۡT\n");
    return 1;
}

void accept_kill(object ob)
{
    do_chat( name() + "���D�R" + rank("self") + "�P�o��" + ob->rank("respectful")
        + "�n���L�޵L���a�S��� ...�S\n");
}

void accept_negotiation(object who, string key)
{
    switch(key) {
    case "peace":
        if( !is_killing(who) ) {
            do_chat( name() + "�`����§�A���D�G�n���A�n���C\n");
            remove_enemy(who);
            who->remove_enemy(this_object());
        }
        else do_chat( name() + "���D�G�o�ܤֻ��A���餣�O�A���K�O�ڬ��I\n");
        return;
    case "mercy":
        if( is_killing(who) ) {
            do_chat( name() + "�����j���A���D�G�J�M�p���A���ѴN�ǤF�A�C\n");
            remove_killer(who);
            remove_enemy(who);
            who->remove_killer(this_object());
            who->remove_enemy(this_object());
	    // add by dragoon
	    if( who->query_class() == "fighter" )
                who->gain_score("martial fame", - who->query_level() * 10);
        }
    }
}
