//----------------------------------------------------------
// file name: IRenderableCollection.h
//
// memo: �`��̎��s����Ɋւ���e�I�u�W�F�N�g�擾�p�C���^�[�t�F�[�X
//----------------------------------------------------------

#ifndef	__IRENDERABLE_COLLECTION_H
#define	__IRENDERABLE_COLLECTION_H

#include "IRenderableContainer.h"
#include "RenderableComponent.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::IRenderableCollection
//
// attrib: interface
//
// memo: �`����s�Ǘ��Ɋւ���e�I�u�W�F�N�g�Q�̐����Ǘ�
//----------------------------------------------------------
class	IRenderableCollection
{
public:
	//----------------------------------------------------------
	//	�`��Ăяo������i�[�R���e�i��A������R���|�[�l���g���擾
	//
	// return: IRenderableComponent* �c �R���e�i�i�[�R���|�[�l���g
	//----------------------------------------------------------
	virtual IRenderableComponent* OrderComponent(void) = 0;

	//----------------------------------------------------------
	//	�`��Ăяo���Ǘ��I�u�W�F�N�g���擾
	//
	// return: IRenderableContainer* �c �`��Ăяo���Ǘ��I�u�W�F�N�g
	//----------------------------------------------------------
	virtual IRenderableContainer* OrderContainer(void) = 0;

	//----------------------------------------------------------
	//	�����_�[�X�e�[�g��Ǝ��ɕێ�����A�`��Ăяo���Ǘ��I�u�W�F�N�g���擾
	//
	// parameter: (in)RenderStates& state �c �����_�[�X�e�[�g�R�s�[���ւ̎Q��
	// parameter: (in)bool isMyStates �c �`�掞�Ɏ��g�̃X�e�[�g���p�̗L��
	//
	// return: IRenderableContainer* �c �`��Ăяo���Ǘ��I�u�W�F�N�g
	//----------------------------------------------------------
	virtual IRenderableContainer* OrderContainer(RenderStates& state, bool isMyStates) = 0;

	//----------------------------------------------------------
	//	�`�搧��i�[�R���e�i�A���R���|�[�l���g��ԋp����
	//
	// parameter: (in)IRenderableComponent pComponent* �c �ԋp����I�u�W�F�N�g�ւ̃|�C���^
	//----------------------------------------------------------
	virtual void ReturnComponent(IRenderableComponent* pComponent) = 0;

	//----------------------------------------------------------
	//	�`��Ăяo���Ǘ��I�u�W�F�N�g��ԋp����
	//
	// parameter: (in)IRenderableContainer* pContainer �c �ԋp����I�u�W�F�N�g�ւ̃|�C���^
	//----------------------------------------------------------
	virtual void ReturnContainer(IRenderableContainer* pContainer) = 0;

protected:
	virtual ~IRenderableCollection(void) {};
};

	};//namespace Renderable
};//namespace gift

#endif
