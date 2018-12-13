/*  mudlib.h

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#ifndef __MUDLIB_H
#define __MUDLIB_H

/* �o�ӬO mudlib ���W�١A���D�A�x�߹L��@�̪��P�N�A�_�h�A�����ӭק�o��
 * �W�١C�o�ӦW�ٰ��F�Ψ��ѧO mudlib ���t�Τ��~�A�]�Φb intermud ��w��
 * �� es �W�D�A�@���U MUD �����q�T�����ΡC
 */
#define MUDLIB_NAME		"Eastern Stories"

/* �o�ӬO mudlib ���������X�AES2 mudlib �b���X�s�����ɭԷ|���@�䪩�����X
 * �����Ʀr�����A�Ʀr�᭱�����r����N�q�p�U�G
 *	p: �쫬�� (prototype)�A����ΡC
 *	a: �������ժ� (alpha)�A���X�Ѧ��[���g��̴��եΡC
 *	b: ���}���ժ� (beta)�A���X�Ѥ@��ϥΪ̴��եΡC
 *	(�L): �������A�t mudlib ��ƻ����Τ����W��C
 */
#define MUDLIB_VERSION_NUMBER	"2.1.3a"

#define MUDLIB_VERSION		(MUDLIB_NAME + " " + MUDLIB_VERSION_NUMBER)

/* �o�O�A�� MUD �ϥΪ�����s�X�t�ΡA�w�]���x�W�a�ϱ`�Ϊ� BIG5�A�j���a�ϳq
 * �`�ϥ� GB �X�AES2 mudlib ���X�ɥH BIG5 �X���D�A�p�G���H�@�N��X�� GB ��
 * �w��M���p���C
 */
#define MUDLIB_LOCALE		"BIG5"

/* �o�ӦW�٬O�b intermud �W�� mud �W�١A�ѩ� intermud �|�M��ڤW����L mud
 * �۳q�s�A�ҥH�ФŨϥ� ASCII �H�~���r��(����X)�C
 */
#define INTERMUD_MUD_NAME	"Celestial Empire"

#endif	/* __MUDLIB_H */
