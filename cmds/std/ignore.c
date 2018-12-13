
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main( object me, string name )
{
  string * ignore;
  int i;

  // add by dragoon
  if( name == "all" ) {
	me->set_temp("ignore/all", 1);
	tell_object(me, "�A�}�l�ڵ��Ҧ��H��A���ܡC\n");
	return 1;
  }
  if( name == "cancel" ) {
	me->delete_temp("ignore/all");
	tell_object(me, "�A�}�l�����Ҧ��H��A���ܡC\n");
	return 1;
  }

  seteuid(getuid(me));
  ignore = me->query( "ignore" );
  if( !pointerp( ignore ) ) ignore = ({ });
  if( !name )
  {
    if( !sizeof( ignore ) ) write( "�A�{�b�S���ڵ��O�H��A��͡C\n" );
    else write( "�A�{�b�ڵ���A��ͪ��H���G" + implode( ignore, ", " ) + "\n");
    return 1;
  }
  if( -1 == member_array( name, ignore ) )
  {
    write( "�A�{�b�}�l����  " + name + "  ��A��͡C\n" );
    ignore += ({ name });
  } else {
    write( "�A�{�b�}�l��  " + name + "  ��A��͡C\n" );
    ignore -= ({ name });
  }
  me->set( "ignore", ignore );
  return 1;
}

int help()
{
        write(@HELP
���O�榡�Rignore < player > | all | cancel

��A���Q��Y�H��ͮɴN�i�H�γo�ӫ��O�C

�d�ҡR
    ignore cuteweca             �ڵ�ť�� cuteweca ���n���C
    ignore cuteweca             �� cuteweca �i�H�A��z���ܤF�C
    ignore all			�ڵ�ť�����H��A���ܡC
    ignore cancel		���� ignore all ���ĥΡC

HELP
        );
  return 1;
}
