//----------------------------------------------------------
// file name: RenderableContainer.cpp
//
// memo: �`��Ăяo���I�u�W�F�N�g�̓o�^�ƁA���s����
//----------------------------------------------------------

#include <assert.h>
#include "RenderableContainer.h"

using namespace gift;
using namespace gift::Renderable;
using namespace gift::Private;
using namespace gift::Private::Renderable;

//----------------------------------------------------------
//	�`��Ăяo���I�u�W�F�N�g�A���s�D��x�A�j��������o�^����
//
// parameter: (in)IDrawCommand* pCommand �c �`��Ăяo���ւ̃|�C���^
// parameter: (in)float priority �c ���s�D��x
// parameter: (in)bool isDisposable �c �j�������̗L��
//
// return: bool �c ���s����
//�@�@�@�@true �c �o�^����
//�@�@�@�@false �c ���łɓo�^����Ă��邽�ߎ��s
//----------------------------------------------------------
bool RenderableContainer::Load(IDrawCommand* pCommand,
							   float priority, bool isDisposable)
{
	//	���łɓo�^����Ă���
	if (_pCommand)
	{
		return false;
	}

	_isDisposable = isDisposable;
	_priority = priority;
	_pCommand = pCommand;

	return true;
}

//----------------------------------------------------------
//	�`��Ăяo���I�u�W�F�N�g�A���s�D��x��o�^����
//
// parameter: (in)IDrawCommand* pCommand �c �`��Ăяo���ւ̃|�C���^
// parameter: (in)float priority �c ���s�D��x
//
// return: bool �c ���s����
//�@�@�@�@true �c �o�^����
//�@�@�@�@false �c ���łɓo�^����Ă��邽�ߎ��s
//----------------------------------------------------------
bool RenderableContainer::Load(IDrawCommand* pCommand, float priority)
{
	//	�j���������s�킹�Ȃ��ŁA�o�^�J�n
	return this->Load(pCommand, priority, false);
}

//----------------------------------------------------------
//	�`��Ăяo���I�u�W�F�N�g�A�j��������o�^����
//
// paramter: (in)IDrawCommand* pCommand �c �`��Ăяo���ւ̃|�C���^
// paramter: (in)bool isDisposable �c �j�������̗L��
//
// return: bool �c ���s����
//�@�@�@�@true �c �o�^����
//�@�@�@�@false �c ���łɓo�^����Ă��邽�ߎ��s
//----------------------------------------------------------
bool RenderableContainer::Load(IDrawCommand* pCommand, bool isDisposable)
{
	//	�f�t�H���g�̗D��x�ŁA�o�^�J�n
	return this->Load(pCommand, 0.0f, isDisposable);
}

//----------------------------------------------------------
//	�`��Ăяo���I�u�W�F�N�g��o�^����
//
// paramter: (in)IDrawCommand* pCommand �c �`��Ăяo���ւ̃|�C���^
//
// return: bool �c ���s����
//�@�@�@�@true �c �o�^����
//�@�@�@�@false �c ���łɓo�^����Ă��邽�ߎ��s
//----------------------------------------------------------
bool RenderableContainer::Load(IDrawCommand* pCommand)
{
	//	�j���������s�킸�A�f�t�H���g�̗D��x�œo�^�J�n
	return this->Load(pCommand, 0.0f, false);
}

//----------------------------------------------------------
//	�`��̌Ăяo�����������s������
//
// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
//
// return: RenderStates* �c ���̌Ăяo���Ŏg���郌���_�[�X�e�[�g
//----------------------------------------------------------
RenderStates* RenderableContainer::Execute(RenderStates* pStates)
{
	assert(_pCommand != NULL);

	//	�`��Ăяo�����������s������
	return (this->*_strategy)(pStates);
}

//----------------------------------------------------------
//	�`��Ăяo���I�u�W�F�N�g�Ȃǂ��i�[����������
//----------------------------------------------------------
void RenderableContainer::Reload(void)
{
	//	�g���̂ăI�u�W�F�N�g
	if (_isDisposable)
	{
		assert(_pCommand != NULL);
		delete _pCommand;
	}

	_isDisposable	= false;
	_priority		= 0.0f;
	_pCommand		= NULL;
	_strategy		= RenderableContainer::Begin;
}

//----------------------------------------------------------
//	�`��J�n���̃��\�b�h�Ăяo�������s������
//
// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
//
// return: RenderStates* �c ���Ɏg�������_�[�X�e�[�g�ւ̃|�C���^
//----------------------------------------------------------
RenderStates* RenderableContainer::Begin(RenderStates* pStates)
{
	//	�`��J�n�̌Ăяo��
	_pCommand->DrawBegin(pStates);

	//	���͕`��̌㏈�����Ăяo������
	_strategy = RenderableContainer::End;

	return pStates;
}

//----------------------------------------------------------
//	�`��̌㏈�����\�b�h�̌Ăяo�������s������
//
// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
//
// return: RenderStates* �c ���Ɏg�������_�[�X�e�[�g�ւ̃|�C���^
//----------------------------------------------------------
RenderStates* RenderableContainer::End(RenderStates* pStates)
{
	//	�`��̌㏈�����Ăяo��
	_pCommand->DrawEnd(pStates);

	//	���͕`��J�n�������Ăяo������
	_strategy = RenderableContainer::Null;

	return pStates;
}
