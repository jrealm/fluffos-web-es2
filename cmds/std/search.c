// search.c

inherit F_CLEAN_UP;

int searching(object me, object env);
int find_drug(object me,int drug_num);

int main(object me, string arg)
{
	if(!arg)
		return notify_fail("�A�J�ӥ|�B½½���, ���S�ݨ�ԣ�S�O���F��C\n");

	if(arg!="drug" || !wizardp(me))
		return notify_fail("�A�J�ӧ�F�� " + arg +" �M���Oԣ�S�O���F��]�S���C\n");

/*
	if(me->is_fighting() || me->is_busy())
		return notify_fail("�A���b����, �иյۥ� halt ����Ҧ����ơC\n");

	message_vision("$N�S�X�ԷV������, �}�l�|�B½½���C\n", me);
	me->start_busy((:searching, me, environment(me):));
*/
	return 1;
}

/*
int searching(object me, object env)
{
	int sk_me, tmp, searched;
	
	if(!me || !env)	return 0;

	env->add_temp("searched", 10);
	sk_me = me->query_skill("alchemy-medication",1);
	searched = env->query_temp("searched");

	// the larger it is, the better drug will apear
	// ���L:room searched descrease
	//  max (100 + 0), min(0 -200)
	tmp = (sk_me - searched)%10;

	if(tmp<2)	tmp=2;
	else if(tmp>50)	tmp=50;

	switch(random(tmp)){
	case 2:
		return find_drug(me,2);
	case 1:
		if( random(me->query_score("explorer fame") + 2)<1 ) {
			message_vision("�F½�����, $N���G�֦b�䤤�C\n",me);
			return 1;
		}
		return find_drug(me,1);
	case 0:
	default:
		message_vision("�F½�����, ���F�@�}�}���ǹ�, $N���򳣨S���C\n",me);
		return 0;
	}
}

int find_drug(object me,int num)
{
	object ob;
	ob=new(DRUG_OB +"d_"+num);
	if(!ob){
		tell_object(me, "�o�د��ĳQ�Ův�U�F�r, �I��H�K�\\��F, �Ч�Ův����.\n");
		return 0;
	}
	message_vision(ob->query("found_msg")? ob->query("found_msg") : "$N�b���㨤����, �o�{�F�@" + ob->query("base_unit") + ob->name() + "�C\n",me);
	if( ob->move(environment(this_player())) )
		environment(this_player())->add_temp("searched", 100);
	return 0;
}
*/

int help(object me)
{
	write(@HELP
���O�榡�Rsearch [<�Y��>]

�o�ӫ��O�i�H���A���A�����Ҥ��O�_���S���F��, �\�h�����ȡB�t�СB�S���~
���i�� search ��ì�o�@�Ǻݭ٩δMì�N�~���F��C

HELP
	);
	return 1;
}
/*
�Ǥ��L
��L�⦸ searched=200, random( sk_me - searched ) { 0 no, 200 best}
searched ���ȭn show �� ppl ?
*/