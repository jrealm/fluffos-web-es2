// ���Q�g skill ���H��d�ҥΪ�
// fonxansword.c

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
	([	"action":		"$N�Ϥ@�ۡu�p�j����v�M�⤤$w�p�@���ȳD���V$n��$l",
		"dodge":		-20,
		"damae":		30,
		"damage_type":	"���"
	]),
	([	"action":		"$N�ϥX�ʤs�C�k�����u�Ťs���y�v�M�C���N�N�٦V$n��$l",
		"dodge":		-20,
		"damae":		30,
		"damage_type":	"�ζ�"
	]),
	([	"action":		"$N�@�ۡu�s���Ӧ�v�M���ΰ~�M�ƥX�ƤءM�⤤$w�٦V$n��$l",
		"dodge":		-30,
		"damae":		20,
		"damage_type":	"�ζ�"
	]),
	([	"action":		"$N�⤤$w���c���i�M�@���u����F�@�v���$n��$l��X�@�C",
		"dodge":		-40,
		"damage_type":	"���"
	]),
	([	"action":		"$N�a���@�D�M�⤤$w�@�ۡu�����m�a�v���$n��$l�ױר�X�@�C",
		"dodge":		-40,
		"damage_type":	"���"
	]),
	([	"action":		"$N��$w�̪Ť@���M�@�ۡu���l�޸��v��V$n��$l",
		"dodge":		20,
		"damage":		40,
		"damage_type":	"���"
	]),
	([	"action":		"$N�⤤$w�V�~�@���M�Ϥ@�ۡu�h�t����v�Ϥ���$n$l�@�C��h",
		"dodge":		-20,
		"damage":		20,
		"damage_type":	"���"
	]),
	([	"action":		"$N��C�W�e�M���Τ@��⤤$w�Ϥ@�ۡu�Ũ���i�v�e�X�@�D�����٦V$n��$l",
		"dodge":		-30,
		"damage":		10,
		"damage_type":	"�ζ�"
	]),
});

string *interattack = ({
        "$N�򴤵ۤ⤤��$n�M�����ӰʡC\n",

});

void create()
{
        seteuid(getuid());
		DAEMON_D->register_skill_daemon("fonxansword");
		setup();
}

void attack_using(object me, object opponent, object weapon)
{
		int damage;

        if( !opponent ) {
                if( me->query_temp("last_attacked_target"))
                message_vision(CYN + interattack[random(sizeof(interattack))] +
NOR,me, weapon);
                return;
        }

	damage = COMBAT_D->fight(me, opponent, "fonxansword",
		actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage)
{
        return usage=="sword" || usage=="parry";
}
