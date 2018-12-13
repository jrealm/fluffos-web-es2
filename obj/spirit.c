// spirit.c
// ask player some question, and log some data to check he is robot or not
#include <npc.h>
#include <ansi.h>

//default question and answer, can be changed by setq seta
string question = "�аݧA�{�b�b����?";
string answer = "�����H�q";

void ask_q();

void create()
{
	set_name("�p���F", ({ "spirit","robot" }) );
	set("long", "
�p���F��ݵۧA, ��A�S�X�޲������e�C
�p���F���ۤ@�Ӥpï�l, �b�W���O���ۤ��^�����D�� robot, �@�I�n��Ův���i������.
	");
	set("chat_chance",20);
	set("chat_msg", ({
		(: ask_q :),
	}));
	setup();
}

void init()
{
	int arr_time = time();
	object me = this_player();
	
	if(!userp(me))
		return;
	if(wizardp(me)) {
		add_action("set_question", "setq");
		add_action("set_answer", "seta");
		add_action("about_robot", "about");
		add_action("robot_help", "help");
		call_out((:message("tell_ob", HIY+ "<help spirit> to complement robot check\n" +NOR, $1):), 1, me);
		return;
	}
	if(!me->query_temp("robot/time")){
		call_out((:message("tell_en", HIY+ "�p���F���D: " +$1+ " �ӳ��ڤF, �C! �{�b�O " +ctime($2)+ ".\n" +NOR, $3):), 2, me->query("id"), arr_time, environment());
		me->set_temp("robot/time", arr_time);
		me->set_temp("robot/question", question);
		me->set_temp("robot/answer", answer);
		log_file("block_robot", sprintf("%s %s %12s ====init====\n",
			ctime(time()), ctime(arr_time), me->query("id")));
	}
}

//�H�K��@�Ӧb���� player, �i�D�L �L�����D
void ask_q()
{
	object *all, target;
	int i, tmp;

	all = all_inventory(environment(this_object()));
	i = sizeof(all);
	target = all[random(i)];
	if(!target || target == this_object())
		return;
	if( wizardp(target)
	|| target->query_temp("robot/time") <=0 )
		return;

	if( (tmp=(time() - target->query_temp("robot/time"))/60) > 20 )
		tell_object(target, tmp+ " �����F, �A�ݩ� robot ��.\n");
	tell_object( target, "�p���F���D: �Х� say �^���ڤU�������D: \n" +question+ "\n>");
}

//�w�� who, �]�p�L�� question
int set_question(string arg)
{
	string who, que;
	object target;
	if(!arg || arg==""){
		write("SYNTAX: setp <ID> <question>\n");
		return 1;
	}
	if(sscanf(arg, "%s %s", who, que)!=2){
		write("SYNTAX: setp <ID> <question>\n");
		return 1;
	}
	if( !(target=present(who, environment())) ){
		write(who+ " �ä��b�o, ����L summon �ӧa.\n");
		return 1;
	}
	target->set_temp("robot/question", que);
	write("�A�� " +target->name()+ "�����D�]��: " +que+ "\n");
	return 1;
}

//�w�� who �]�� answer
int set_answer(string arg)
{
	string who, ans;
	object target;
	if(!arg || arg==""){
		write("SYNTAX: setp <ID> <answer>\n");
		return 1;
	}
	if(sscanf(arg, "%s %s", who, ans)!=2){
		write("SYNTAX: setp <ID> <answer>\n");
		return 1;
	}
	if( !(target=present(who, environment())) ){
		write(who+ " �ä��b�o, ����L summon �ӧa.\n");
		return 1;
	}
	target->set_temp("robot/answer", ans);
	write("�A�� " +target->name()+ "�����D <"
		+target->query_temp("robot/question")+ "> �����׳]�� <" +ans+ ">\n");
	return 1;
}

//�d�Y�H �� robot ��T
int about_robot(string who)
{
	object target;
	int arr_time;
	if(!who){
		write("SYNTAX: about <ID>\n");
		return 1;
	}
	if( !(target=present(who, environment())) ){
		write(who+ " �ä��b�o, ����L summon �ӧa.\n");
		return 1;
	}
	if( !(arr_time=target->query_temp("robot/time")) ){
		write(who+ " ����F�ɶ��w����, �i�঳���u�L, �ά��Ův��...\n");
		return 1;
	}
	write(who+ " �}�l�ɶ�: " +ctime(arr_time)+ "\n");
	write(who+ " �[��ɶ�: �w�� " +(time() - arr_time)/60+ " �����S����\n");
	write(who+ " �����D��: " +target->query_temp("robot/question") +"\n");
	write(who+ " ���n�^��: " +target->query_temp("robot/answer") +"\n");
	return 1;
}

int robot_help(string arg)
{
	if(arg!="spirit")	return 0;
	write(@HELP
1. summon <ID>
2. setq <ID> <question>
3. seta <ID> <answer>
4. about <ID>
�Y�n�d�Y player �O�_�� robot, �i���p���F�ݥL�@�Ӱ��D, �� robot ��ɨ�, ��
�� say �F���Ǹ�, ���|�O������, �j�Ův�H�W�|�b���Ůɬd�ݰO���óB�z.
App, Wiz �h�� robot �ɧ��i�Q�Φ��p���F, ���нT�w�����a�b�Q�A��Ӥ��e�O�B��
�m�\�����A, �åH post �y�z�@�U����.
HELP
	);
	return 1;
}

//�H say �^��, 20 min ���Y����|�M�� temp mark �� move �� snow
void relay_say(object me,string msg)
{
	int tmp;
	log_file("block_robot", sprintf("%s %12s %8s <%s>\n", 
		ctime(time()),
		me->query("id"),
		me->query_temp("robot/time")>0 ? 
			(time() - me->query_temp("robot/time"))/60+ " min" : " * min",
		msg,
	));

	if( (tmp=(time() - me->query_temp("robot/time"))/60) > 20 ){
		tell_object(me, 
"�A�w�W�L " +tmp+ " �����S����, �j�Ův�H�W�|�b���ŮɳB�z(����), �Y����ĳ�ФΦ���
��, �øԭz���p�z��. �Y�A�n suicide ���m, �O�o post �q���Ův, �_�h�s�m����
�Q�夣�t�d. �Y�n���}, ���_�u 15 ����\n"
		);
		return;
	}
	if( me->query_temp("robot/answer") ){
		if( strsrch(msg, me->query_temp("robot/answer"))>=0 ){
//		CHANNEL_D->do_channel( this_object(), "chat", "���ӧŮv����, �Ӻ�q�@�U.") );
			tell_object(me, "�p���F���D: �A����F, �U�����ŦA�Ӫ�.\n�p���F�V�A�j�F�f��, �A�����Ʀa���F�X�h.\n\n");
			if( me->move("/d/snow/inn_hall") ){
				tell_room(environment(me), me->name()+ "�Q�p���F�j�F�L��.\n");
				log_file("block_robot", sprintf("%s %12s %8s �ᵪ�����}\n",
					ctime(time()),
					me->query("id"),
					(int)(time() - me->query_temp("robot/time"))/60+ " min",
				));
				this_player()->delete_temp("robot/");	//clean robot record
				return;
			}
			tell_object(me, "�p���F�D: �n����,  �j���ʧA, �A�h��O�H������A�j�X�h, �H�a���ޤF.\n");
			return;
		}
	}
	tell_object(me, "�p���F�D: �A�n�������F, �٬O�A�����ܧ�ť����, �ڦA�ݤ@��:\n" +me->query_temp("robot/question")+ "\n");
}
