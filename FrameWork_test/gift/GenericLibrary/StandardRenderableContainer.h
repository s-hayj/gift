//----------------------------------------------------------
// file name: StandardRenderableContainer.h
//
// memo: �����_�[�X�e�[�g�ƕ`��Ăяo���I�u�W�F�N�g���i�[�A���䂷��
//----------------------------------------------------------

#ifndef	__STANDARD_RENDERABLE_CONTAINER_H
#define	__STANDARD_RENDERABLE_CONTAINER_H

#include <stdio.h>
#include "IRenderableContainer.h"


namespace gift
{

	namespace Private
	{

		namespace Renderable
		{

//----------------------------------------------------------
// name: gift::Private::Renderable::StandardRenderableContainer
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableContainer is interface
//
// memo: �`���̐e�Ƃ��āA�f�[�^�i�[�A���䂷��R���e�i
//----------------------------------------------------------
class	StandardRenderableContainer
	: public gift::Renderable::IRenderableContainer
{
private:
	bool			_isDisposable;	//	�j���̗L��
	bool			_ChangeState;	//	�f�[�^�����̗L��
	float			_priority;		//	���s�D��x
	gift::Renderable::IDrawCommand*	_pCommand;		//	�`��Ăяo��
	RenderStates	_myState;		//	�������Ă���`��f�[�^
	RenderStates*	_pAnyState;		//	�]������Ă����f�[�^�L���p

	//	�Ăяo�����s���̐U�镑��
	RenderStates* (StandardRenderableContainer::*_strategy)(RenderStates*);

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	StandardRenderableContainer(void)
		: _isDisposable(false), _ChangeState(false), _pCommand(NULL), _myState(),
		_pAnyState(NULL), _strategy(StandardRenderableContainer::BeginAnyState)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~StandardRenderableContainer(void)
	{
		//	�j����C����Ă���
		if (_isDisposable)
		{
			//	�j������Ă��Ȃ�
			if (_pCommand)
			{
				delete _pCommand;
			}
		}
	};

	//----------------------------------------------------------
	//	�`�掞�Ɏ��g�̃����_�[�X�e�[�g�𗘗p���邩�̗L��
	//
	// parameter: (in)bool value �c �����_�[�X�e�[�g�؂�ւ��̗L��
	//
	// memo: true �Ȃ�A���g�̃����_�[�X�e�[�g���Ȍ�g���悤�ɂ���
	//�@�@�@false �Ȃ�A�]������Ă��������_�[�X�e�[�g�𗘗p����
	//----------------------------------------------------------
	void Enable(bool value)
	{
		_ChangeState = value;

		//	���g�̃����_�[�X�e�[�g���g��
		if (_ChangeState)
		{
			_strategy = StandardRenderableContainer::BeginMyState;
		}
		//	�]������ė��������_�[�X�e�[�g���g��
		else
		{
			_strategy = StandardRenderableContainer::BeginAnyState;
		}
	};

	//----------------------------------------------------------
	//	���g���܂߂�����̕`�掞�ɗ��p���郌���_�[�X�e�[�g��ݒ肷��
	//
	// parameter: (in)const RenderStates& states �c �R�s�[���ւ̎Q��
	//----------------------------------------------------------
	void SetRenderStates(const RenderStates& states)
	{
		_myState = states;
	};

	//----------------------------------------------------------
	//	�`��D��x���擾
	//
	// return: float �c �D��x
	//
	// attrib: override
	//----------------------------------------------------------
	float GetPriority(void)
	{
		return _priority;
	};

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
	//
	// attrib: override
	//----------------------------------------------------------
	bool Load(gift::Renderable::IDrawCommand* pCommand, float priority, bool isDisposable);

	//----------------------------------------------------------
	//	�`��Ăяo���I�u�W�F�N�g�A���s�D��x��o�^����
	//
	// parameter: (in)IDrawCommand* pCommand �c �`��Ăяo���ւ̃|�C���^
	// parameter: (in)float priority �c ���s�D��x
	//
	// return: bool �c ���s����
	//�@�@�@�@true �c �o�^����
	//�@�@�@�@false �c ���łɓo�^����Ă��邽�ߎ��s
	//
	// attrib: override
	//----------------------------------------------------------
	bool Load(gift::Renderable::IDrawCommand* pCommand, float priority);

	//----------------------------------------------------------
	//	�`��Ăяo���I�u�W�F�N�g�A�j��������o�^����
	//
	// paramter: (in)IDrawCommand* pCommand �c �`��Ăяo���ւ̃|�C���^
	// paramter: (in)bool isDisposable �c �j�������̗L��
	//
	// return: bool �c ���s����
	//�@�@�@�@true �c �o�^����
	//�@�@�@�@false �c ���łɓo�^����Ă��邽�ߎ��s
	//
	// attrib: override
	//----------------------------------------------------------
	bool Load(gift::Renderable::IDrawCommand* pCommand, bool isDisposable);

	//----------------------------------------------------------
	//	�`��Ăяo���I�u�W�F�N�g��o�^����
	//
	// paramter: (in)IDrawCommand* pCommand �c �`��Ăяo���ւ̃|�C���^
	//
	// return: bool �c ���s����
	//�@�@�@�@true �c �o�^����
	//�@�@�@�@false �c ���łɓo�^����Ă��邽�ߎ��s
	//
	// attrib: override
	//----------------------------------------------------------
	bool Load(gift::Renderable::IDrawCommand* pCommand);

	//----------------------------------------------------------
	//	�`��̌Ăяo�����������s������
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c ���̌Ăяo���Ŏg���郌���_�[�X�e�[�g
	//
	// attrib: override
	//----------------------------------------------------------
	RenderStates* Execute(RenderStates* pStates);

	//----------------------------------------------------------
	//	�`��Ăяo���I�u�W�F�N�g�Ȃǂ��i�[����������
	//
	// attrib: override
	//----------------------------------------------------------
	void Reload(void);

private:
	//----------------------------------------------------------
	//	���g�̃����_�[�X�e�[�g�ŕ`��J�n���̃��\�b�h�Ăяo�������s������
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c ���g�̃����_�[�X�e�[�g�ւ̃|�C���^
	//----------------------------------------------------------
	RenderStates* BeginMyState(RenderStates* pStates);

	//----------------------------------------------------------
	//	���g�̃����_�[�X�e�[�g�ŕ`��̌㏈�����\�b�h�̌Ăяo�������s������
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c ���̃����_�[�X�e�[�g�ւ̃|�C���^
	//----------------------------------------------------------
	RenderStates* EndMyState(RenderStates* pStates);

	//----------------------------------------------------------
	//	��񂵗p�̃��\�b�h
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c �����̃����_�[�X�e�[�g
	//----------------------------------------------------------
	RenderStates* NullMyState(RenderStates* pStates)
	{
		_strategy = StandardRenderableContainer::BeginMyState;

		return pStates;
	};

	//----------------------------------------------------------
	//	�`��J�n���̃��\�b�h�Ăяo�������s������
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c ����g�������_�[�X�e�[�g�ւ̃|�C���^
	//----------------------------------------------------------
	RenderStates* BeginAnyState(RenderStates* pStates);

	//----------------------------------------------------------
	//	�`��̌㏈�����\�b�h�̌Ăяo�������s������
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c ����g�������_�[�X�e�[�g�ւ̃|�C���^
	//----------------------------------------------------------
	RenderStates* EndAnyState(RenderStates* pStates);

	//----------------------------------------------------------
	//	��񂵗p�̃��\�b�h
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c �����̃����_�[�X�e�[�g
	//----------------------------------------------------------
	RenderStates* NullAnyState(RenderStates* pStates)
	{
		_strategy = StandardRenderableContainer::BeginAnyState;

		return pStates;
	};
};

};//namespace Renderable
};//namespace Private
};//namespace gift

#endif
