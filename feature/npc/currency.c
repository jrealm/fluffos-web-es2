private string price_string(int v)
{
	if( v%10000 == 0 )
		return chinese_number(v/10000) + "�����";
	if( v%100 == 0 )
		return chinese_number(v/100) + "��Ȥl";
	return chinese_number(v) + "���";
}

