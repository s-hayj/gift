//----------------------------------------------------------
// file name: RenderableContainer.h
//
// memo: �`�惁�\�b�h�Ăяo���I�u�W�F�N�g�A�i�[�Ǘ��N���X
//----------------------------------------------------------

#ifndef	__RENDERABLE_CONTAINER_H
#define	__RENDERABLE_CONTAINER_H

#include <stdio.h>
#include "IRenderableContainer.h"

namespace gift
{

	namespace Private
	{

		namespace Renderable
		{

//----------------------------------------------------------
// name: gift::Private::Renderable::RenderableContainer
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableContainer is interface
//
// memo: �q�Ƃ��ĘA��������ۂɊi�[�A���䂷��R���e�i
//----------------------------------------------------------
class	RenderableContainer
	: public gift::Renderable::IRenderableContainer
{
private:
	bool			_isDisposable;	//	�j���̗L��
	float			_priority;		//	���s�D��x
	gift::Renderable::IDrawCommand*	_pCommand;		//	�`��Ăяo��

	//	�Ăяo�����s���̐U�镑��
	RenderStates* (RenderableContainer::*_strategy)(RenderStates*);

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	RenderableContainer(void)
		: _isDisposable(false), _priority(0.0f),
		_pCommand(NULL), _strategy(RenderableContainer::Begin)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~RenderableContainer(void)
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
	//	�`��J�n���̃��\�b�h�Ăяo�������s������
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c ���Ɏg�������_�[�X�e�[�g�ւ̃|�C���^
	//----------------------------------------------------------
	RenderStates* Begin(RenderStates* pStates);

	//----------------------------------------------------------
	//	�`��̌㏈�����\�b�h�̌Ăяo�������s������
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c ���Ɏg�������_�[�X�e�[�g�ւ̃|�C���^
	//----------------------------------------------------------
	RenderStates* End(RenderStates* pStates);

	//----------------------------------------------------------
	//	��񂵗p�̃��\�b�h
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c �����̃����_�[�X�e�[�g
	//----------------------------------------------------------
	RenderStates* Null(RenderStates* pStates)
	{
		_strategy = RenderableContainer::Begin;

		return pStates;
	};
};

};//namespace Renderable
};//namespace Private
};//namespace gift

#endif
