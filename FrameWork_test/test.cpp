

#include <stdio.h>
#include "gift.h"

using namespace gift;


class TestRelease
{
public:
	void Release(void)
	{
		printf("cull Release()\n");

		delete this;
	};

private:
	~TestRelease(void)
	{
		printf("�j������\n");
	};
};

class TestDelete
{
public:
	~TestDelete(void)
	{
		printf("�j������\n");
	};
};

//----------------------------------------------------------
//	DeleteHelper �̎g�p��
//----------------------------------------------------------
void Sample_DeleteHelper(void)
{
	/*
	DeleteHelper<> �� ICommand ���p�����Ă���A
	�j���̐ӔC�� ICommand �ֈϑ����邱�Ƃ��ł���B
	*/

	gift::ICommand* pCommand = gift::DeleteHelper<true>(new TestRelease());

	/*
	��L�ł́ADeleteHelper �̃p�����[�^�[�� true �𒼐ڎw�肷��B
	����ɂ��A������ TestRelease �̃C���X�^���X�́ARelease() �����o�֐�
	�ɂ���Ĕj�������悤�ɂȂ�B
	���R�ATestRelease �� Release() �����o�֐�����������Ă��Ȃ���΂Ȃ�Ȃ��B
	*/

	pCommand->Execute();
	delete pCommand;

	/*
	ICommand �Ɉϑ������ꍇ�B��L�̂悤�ɕK�� delete���Z�q�Ŕj������K�v������B
	���̂Ƃ��ɁA�o�^���ꂽ TestRelease �� Release() �����o�֐����Ăяo�����B
	�܂��AICommand::Execute() �ł��A���l�̌��ʂ�������B
	�������ATestRelease �� Release() ���Ăяo���̂́A�ǂ��炩���݂̂ł���B
	*/

	DeleteHelper<false> test(new int(5));

	/*
	int �^�̂悤�ɁARelease() �����o�֐��������Ȃ��C���X�^���X�̏ꍇ�B
	�e���v���[�g�p�����[�^�[�� false ���w�肷�邱�ƂŁAdelete���Z�q�ɂ����
	�j���������s���悤�ɂȂ�B
	*/

	DeleteHelper<false> hoge( test );

	/*
	�R�s�[�R���X�g���N�^�ɂ���āA�j���̐ӔC���ϑ����邱�Ƃ��ł���B
	���̏ꍇ�A�ӔC�������� test ���A�j���������s�����Ƃ��Ă��X���[�����B
	*/

	test();
	hoge();

	/*
	��L�ł́Atest() �̐U�镑���̓X���[����Ahoge() �ɂ���āAint�^��
	�C���X�^���X�́Adelete���Z�q��ʂ��Ĕj������܂��B
	�܂��A�j���̐ӔC������ɂ��ϑ������A�j�����������s���Ȃ������ꍇ�B
	DeleteHelper<> �͎��g�̔j���Ƌ��ɁA�i�[���ꂽ�C���X�^���X�̔j����
	���s���܂��B
	*/

	DeleteHelper<false>* pHoge = new DeleteHelper<false>(new TestDelete());

	delete pHoge;

	DeleteHelper<true> hige(new TestRelease());

	/*
	DeleteHelper<> �ɂ���āA�C���X�^���X�̔j�����ϑ�����ꍇ�B
	�R���X�g���N�^�̃I�[�o�[���[�h�ɂ���āA�i�[����^��I�����Ă��܂��B
	����āA�ȉ��̂悤�ȕ��@�����Ȃ���΂Ȃ�Ȃ��ꍇ������B
	*/

	int* pInt = new int(10);

	DeleteHelper<>((int*)pInt);

	/*
	�e���v���[�g�p�����[�^�[�̓f�t�H���g�� false ���w�肵�Ă���̂ŁA
	����͏ȗ����Ă��܂��B
	���炩�̌^�ւ̃|�C���^�^���w�肷��ꍇ�B
	���̌^�Ȃ̂��A�����I�ɂ��Ȃ���΂Ȃ�Ȃ��B
	*/
}

