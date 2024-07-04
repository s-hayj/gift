//----------------------------------------------------------
// file name: IRenderableContainer.h
//
// memo: �`�惁�\�b�h�Ăяo���悤�I�u�W�F�N�g�ƁA������i�[�p�C���^�[�t�F�[�X
//----------------------------------------------------------

#ifndef	__IRENDERABLE_CONTAINER_H
#define	__IRENDERABLE_CONTAINER_H

#include "IDrawCommand.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::IRenderableContainer
//
// attrib: interface
//
// memo: �`��Ăяo���I�u�W�F�N�g���A�D��x�Ƌ��Ɋi�[�p�C���^�[�t�F�[�X
//----------------------------------------------------------
class	IRenderableContainer
{
public:
	virtual ~IRenderableContainer(void) {};

	//----------------------------------------------------------
	//	�`��D��x���擾
	//
	// return: float �c �D��x
	//----------------------------------------------------------
	virtual float GetPriority(void) = 0;

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
	virtual bool Load(IDrawCommand* pCommand,
		float priority, bool isDisposable) = 0;

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
	virtual bool Load(IDrawCommand* pCommand, float priority) = 0;

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
	virtual bool Load(IDrawCommand* pCommand, bool isDisposable) = 0;

	//----------------------------------------------------------
	//	�`��Ăяo���I�u�W�F�N�g��o�^����
	//
	// paramter: (in)IDrawCommand* pCommand �c �`��Ăяo���ւ̃|�C���^
	//
	// return: bool �c ���s����
	//�@�@�@�@true �c �o�^����
	//�@�@�@�@false �c ���łɓo�^����Ă��邽�ߎ��s
	//----------------------------------------------------------
	virtual bool Load(IDrawCommand* pCommand) = 0;

	//----------------------------------------------------------
	//	�`��̌Ăяo�����������s������
	//
	// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
	//
	// return: RenderStates* �c ���̌Ăяo���Ŏg���郌���_�[�X�e�[�g
	//----------------------------------------------------------
	virtual RenderStates* Execute(RenderStates* pStates) = 0;

	//----------------------------------------------------------
	//	�`��Ăяo���I�u�W�F�N�g�Ȃǂ��i�[����������
	//----------------------------------------------------------
	virtual void Reload(void) = 0;
};

	};//namespace Renderable
};//namespace gift

#endif
