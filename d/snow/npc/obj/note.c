// note.c
//�@�i���W���ϥ֭��M�W���a�l����²�n�a�e�F�ǹϻP���O�M�̫᭱�٪��O�F �p����
//�T�Ӧr�M�����O�ƻ�N��C

inherit ITEM;

void create()
{
	set_name("���F�p���D", ({ "snow note","note","map"}));
	set_weight(50);
	if( !clonep() ) {
		set("unit", "�i");
		set("long",@LONG
�@�i���W���ϥ֭��M�W���a�l������²�n�a�e�F�ǹϻP���O�C

�̪�f�̸̫ܯʤH��M���|                          �[�[
�B�����{�ɤu�C              �u���Ϥs�v           �ˡ�
                                ��      �y������z�ˡ�
���R���p�Ѥl�̸g�`�ƥX��       �s��         �x     �ˡ�
�]�l�������ӡMť�����Ǧn  ��    �x         ����     �ˡ�
�Y�����Ĥl�`�`½��h���Y �F��w��D�w�p���w�p��  ���� �ˡ�
��C                            �x             �@ �x   �ˡ�
                                �x               ����  �ˡ�
���ǹx�֪��p�Ĥl�`���b��       ��D              �p���w������y���u���z
�̼p�и̤μs���������j�_        �x                �x   �ˡ�
��W�������g�áM�C�C���L        �x               ����  �ˡ�
�̪������䤣��H�C             �s��              �p��   �ˡ�
                  ��  ��        �x                �x     �ˡˡˡu���a���v
                    �p         �s��        ���R  ���R  �}��  �ˡ��ˡˡˡ�
             �p�Тw�ȴ̢w�s���w�����w�s���w�p�Ѣw�p�Ѣw�j�v�w�e�� �ˡˡ�
                  ��  ��  �x    �x          �x
             �m��         �x    �x          �p
   �u�ø��^�v �x          �x    �x         �ľQ
            ����          �x    �x   ���K
	     �F��w��D�w��D�w�s���w�Q�l   �b�s�����������f�j����(pot)�K�O
                    �x          �x          �Ѥ����L���ȶ��ΡC
                    �x          �x   ���O
                   �p��  �f�̢w��D�w�p�Q   ���O�p�Q���F��Ǥ�����f�~�M�]
                                �x          �g��������ưȡC
                 �u���Z�x��v�����
                                 ��         ���F�洣�ѫH���໼�A�ȡC
                                  �u�ѪQ�L�v
LONG
		);
		set("value", 1);
	}
	setup();
}
