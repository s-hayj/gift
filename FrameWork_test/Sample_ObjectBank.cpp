

#include <stdio.h>
#include "gift.h"

class	Object
{
public:
	int	_id;

	static int s_count;

public:
	Object(void)
	{
	};

	~Object(void)
	{
	};

	//	��������邲�ƂɁA�񐔂�����ł���
	static Object*& Create(Object*& pValue)
	{
		pValue = new Object();

		pValue->_id = Object::s_count;

		Object::s_count++;

		return pValue;
	};

	static Object*& Release(Object*& pValue)
	{
		delete pValue;

		pValue = NULL;

		return pValue;
	};
};

int Object::s_count = 0;


void Sample_ObjectBank(void)
{
	/*
	�e���v���[�g�p�����[�^�[�̌^�i��Ƀ|�C���^�^�j�̃I�u�W�F�N�g���ė��p����
	���߂ɁA�݌ɊǗ�������N���X�B
	�o�ׂ��������Ǘ�����̂ł͂Ȃ��A�����ς݂ŏo�ׂ��Ă��Ȃ��I�u�W�F�N�g��
	�Ǘ�������B
	*/

	gift::ObjectBank<Object*> bank;

	/*
	���[�U�[�̓e���v���[�g�p�����[�^�[�i����� Object* �^�j�𔭍s���Ă��炤�B
	�܂��A�K�v�Ȃ��Ȃ����Ƃ��́A�����ԋp���邱�Ƃ��ł���B
	����ɂ��A�ԋp���ꂽ���̂��ēx�o�ׂ��A�݌ɂ��Ȃ��Ȃ����ꍇ�ɏ��߂āA
	�V������������B
	����́A���I�ȃ������m�ۂ��K�v�ł��āA�����Ɣj�����p�ɂɍs���鏈����
	���Ɍ��ʂ����҂�����̂ł���B
	����āAObjectBank<> �̓p�����[�^�[�̏������Ɣj�����@��m���Ă���K�v������
	*/

	bank.Register(gift::NewDelManager<Object*>(Object::Create, Object::Release));

	/*
	�����Ɣj�����Ɏ󂯓n�����^�́AObjectBank<> �̃p�����[�^�[�Ȃ̂ŁA
	NewDelManager<> �̃p�����[�^�[�ƈ�v���Ă��Ȃ��Ă͂Ȃ�Ȃ��B
	����́A�R���X�g���N�^�̈����Ƃ��ēn���Ă��A���l�̌��ʂ𓾂�B
	*/

	Object* pTemp[20];

	//	10��Object�𔭍s���Ă��炤
	for (int i = 0; i < 10; i++)
	{
		pTemp[i] = bank.Order();

		printf("%d\n", pTemp[i]->_id);
	}

	//	�g���I������̂ŕԋp
	for (int i = 0; i < 10; i++)
	{
		//	�X�^�b�N�̂悤�ɗ��߂Ă���
		bank.Return(pTemp[i]);
	}

	//	20���s���Ă��炤
	for (int i = 0; i < 20; i++)
	{
		pTemp[i] = bank.Order();

		printf("%d\n", pTemp[i]->_id);
	}

	//	�g���I������̂ŕԋp
	for (int i = 0; i < 20; i++)
	{
		bank.Return(pTemp[i]);
	}

	/*
	0�`9 ��������x�g���Ă���悤�ɁA�ԋp���ꂽ���̂���ēx�g���Ă���
	�v�ɂȂ�܂��B
	�c�O�ȓ_�Ƃ��āA�o�^���������A�j�������́A���߂Ĕ��s�����Ƃ��ƁA�Ǘ���
	�j�������Ƃ��ɂ̂݌Ăяo����邽�߁A�ė��p����ۂ̏����������́A
	���p�҂��C�ӂōs�����ƂɂȂ�܂��B
	*/

	bank.Release();

	/*
	��L�̃����o�֐��ɂ��A�݌ɂ�S�Ĕj�����܂��B
	*/
}
