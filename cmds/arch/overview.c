// overview.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object *ob;
	int i, m;

	switch(arg) {
		case "user":
			ob = users();
			printf("�@�� %d �ӨϥΪ̪���C\n", sizeof(ob));
			break;
		case "living":
			ob = livings();
			printf("�@�� %d �ӥͪ�(�t�ϥΪ�)����C\n", sizeof(ob));
			break;
		case "char":
			ob = objects( (: $1->is_character() && !clonep($1) :) );
			printf("�@�� %d �ؤH������ master copy �Q���J�C\n", sizeof(ob));
			break;
		case "npc":
			ob = filter_array( livings(),
				(: $1->is_character() && !userp($1) && clonep($1) :) );
			printf("�@�� %d �� NPC ����C\n", sizeof(ob));
			break;
		case "combat":
			ob = objects( (: $1->is_fighting() :) );
			printf("�@�� %d �ӤH�����b�԰����A�C\n", sizeof(ob));
			break;
		case "kill":
			ob = objects( (: $1->is_killing() && $1->is_fighting() :) );
			printf("�@�� %d �ӤH�����b�ʩR�۷i���԰����A�C\n", sizeof(ob));
			break;
		case "hunt":
			ob = objects( (: $1->is_killing() :) );
			printf("�@�� %d �ӤH�����M��L�H�����ۤ���C\n", sizeof(ob));
			break;
		case "heart beat":
			ob = objects( (: query_heart_beat :) );
			printf("�@�� %d �Ӫ��� heart beat �����Ī��A�C\n", sizeof(ob));
			break;
		case "virtual":
			ob = objects( (: virtualp :) );
			printf("�@�� %d �ӵ�������C\n", sizeof(ob));
			break;
		case "room":
			ob = objects( (: function_exists("create_door", $1) :) );
			printf("�@�� %d �өж��C\n", sizeof(ob));
			break;
		case "special room":
			// inherits won't work if master copy got cleaned up.
			if( !find_object(ROOM) ) ROOM->foo();
			ob = objects( (: inherits(ROOM, $1) :) );
			printf("�@�� %d �Ӫ����~�Ӽзǩж��C\n", sizeof(ob));
			break;
		case "equip":
			// inherits won't work if master copy got cleaned up.
			if( !find_object(F_EQUIP) ) F_EQUIP->foo();
			ob = objects( (: inherits(F_EQUIP, $1) :) );
			printf("�@�� %d �Ӫ����~�ӼзǸ˳ơC\n", sizeof(ob));
			break;
		case "object":
			ob = objects();
			printf("�@�� %d �Ӫ���Q���J�C\n", sizeof(ob));
			break;
		default:
			return notify_fail("���O�榡�Roverview <topic>\n");
	}
	m = 0;
	i = sizeof(ob);
	while(i--)
		m += memory_info(ob[i]);
	printf("�`�@�ϥ� %d bytes �O����C\n", m);
	if( sizeof(ob) )
		printf("�����C�Ӫ���ϥ� %d bytes �O����C\n", m / sizeof(ob));
	return 1;
}

int help()
{
	write(@TEXT
���O�榡�Roverview <�D�D>

user:		userp()
living:		living()
room:		function_exists("create_door", ob);
TEXT
	);
	return 1;
}


