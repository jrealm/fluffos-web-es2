/*  version.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <mudlib.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
  string name;
  printf("�C�����A���G%s %s\n", capitalize(__DRIVER__), __VERSION__ );
  printf("Mudlib �����G%s\n", MUDLIB_VERSION );
  return 1;
}

int help(object me)
{
  write(@HELP
���O�榡 : version
 
�o�ӫ��O�|��ܹC���ثe�ҥΪ� LP driver �����H�� mudlib �����C
HELP
  );
  return 1;
}
