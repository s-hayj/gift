//----------------------------------------------------------
// file name: StandardRenderableContainer.cpp
//
// memo: �����_�[�X�e�[�g�ƕ`��Ăяo���I�u�W�F�N�g���i�[�A���䂷��
//----------------------------------------------------------

#include <assert.h>
#include "StandardRenderableContainer.h"

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
bool StandardRenderableContainer::Load(IDrawCommand* pCommand,
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
bool StandardRenderableContainer::Load(IDrawCommand* pCommand, float priority)
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
bool StandardRenderableContainer::Load(IDrawCommand* pCommand,
									   bool isDisposable)
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
bool StandardRenderableContainer::Load(IDrawCommand* pCommand)
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
RenderStates* StandardRenderableContainer::Execute(RenderStates* pStates)
{
	assert(_pCommand != NULL);

	//	�`��Ăяo�����������s������
	return (this->*_strategy)(pStates);
}

//----------------------------------------------------------
//	�`��Ăяo���I�u�W�F�N�g�Ȃǂ��i�[����������
//----------------------------------------------------------
void StandardRenderableContainer::Reload(void)
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

	//	�`��Ăяo�����\�b�h��I������
	this->Enable(_ChangeState);
}

//----------------------------------------------------------
//	���g�̃����_�[�X�e�[�g�ŕ`��J�n���̃��\�b�h�Ăяo�������s������
//
// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
//
// return: RenderStates* �c ���g�̃����_�[�X�e�[�g�ւ̃|�C���^
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::BeginMyState(RenderStates* pStates)
{
	//	���̃����_�[�X�e�[�g�ւ̃|�C���^���L��
	_pAnyState = pStates;

	//	���g�̃����_�[�X�e�[�g��n���ĕ`��J�n�̌Ăяo��
	_pCommand->DrawBegin(&_myState);

	//	���͕`��̌㏈�����Ăяo������
	_strategy = StandardRenderableContainer::EndMyState;

	return &_myState;
}

//----------------------------------------------------------
//	���g�̃����_�[�X�e�[�g�ŕ`��̌㏈�����\�b�h�̌Ăяo�������s������
//
// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
//
// return: RenderStates* �c ���̃����_�[�X�e�[�g�ւ̃|�C���^
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::EndMyState(RenderStates* pStates)
{
	//	�`��̌㏈�����Ăяo��
	_pCommand->DrawEnd(&_myState);

	//	���͕`��J�n�������Ăяo������
	_strategy = StandardRenderableContainer::NullMyState;

	return _pAnyState;
}

//----------------------------------------------------------
//	�`��J�n���̃��\�b�h�Ăяo�������s������
//
// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
//
// return: RenderStates* �c ����g�������_�[�X�e�[�g�ւ̃|�C���^
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::BeginAnyState(RenderStates* pStates)
{
	//	�`��J�n�̌Ăяo��
	_pCommand->DrawBegin(pStates);

	//	���͕`��̌㏈�����Ăяo������
	_strategy = StandardRenderableContainer::EndAnyState;

	return pStates;
}

//----------------------------------------------------------
//	�`��̌㏈�����\�b�h�̌Ăяo�������s������
//
// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
//
// return: RenderStates* �c ����g�������_�[�X�e�[�g�ւ̃|�C���^
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::EndAnyState(RenderStates* pStates)
{
	//	�`��̌㏈�����Ăяo��
	_pCommand->DrawEnd(pStates);

	//	���͕`��J�n�������Ăяo������
	_strategy = StandardRenderableContainer::NullAnyState;

	return pStates;
}
