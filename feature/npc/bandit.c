// villager.c

// prototypes
mixed do_chat(mixed chat);
varargs string name(int raw);
void kill_ob(object ob);
varargs int is_fighting(object ob);

int accept_fight(object ob)
{
	if( is_fighting() ) {
		do_chat( name() + "���D�R�� ... �ʦh���Ӥ��O�n�~�M�ݷ|��A���A���T\n");
		return 0;
	}
	do_chat( name() + "���D�R���T�ݨӧA�O���o���@�ФF�M���ڨӱаV�аV�A�T\n");
	kill_ob(ob);
	return 1;
}

void accept_kill(object ob)
{
	do_chat( name() + "�u��v�a�@�n�M���D�R���o�@�A���S���o�ӥ��ơT\n");
}
