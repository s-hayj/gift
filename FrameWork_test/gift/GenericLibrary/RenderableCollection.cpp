//----------------------------------------------------------
// file name: RenderableCollection.cpp
//
// memo: �`��Ăяo���Ǘ��I�u�W�F�N�g��A�������i�[�Ǘ�����N���X
//----------------------------------------------------------

#include "RenderableCollection.h"
#include "RenderableComponent.h"

#include "NewDelManager.h"

using namespace gift;
using namespace gift::Renderable;
using namespace gift::Private;
using namespace gift::Private::Renderable;

//----------------------------------------------------------
//	�R���X�g���N�^
//----------------------------------------------------------
RenderableCollection::RenderableCollection(void)
{
	//	�`����s�Ǘ��I�u�W�F�N�g�i�[�A���p�I�u�W�F�N�g�̐����A�j�����@�̓o�^
	_pComponentBank = new ObjectBank<IRenderableComponent*>(
		NewDelManager<IRenderableComponent*>(
			RenderableFactory(), RenderableFactory::Create,
			RenderableFactory(), RenderableFactory::Delete));

	//	�`����s�Ǘ��I�u�W�F�N�g�̐����A�j�����@��o�^
	_pRenderableBank = new ObjectBank<RenderableContainer*>(
		NewDelManager<RenderableContainer*>(
			RenderableFactory(), RenderableFactory::Create,
			RenderableFactory(), RenderableFactory::Delete));

	//	�����_�[�X�e�[�g��ێ������`����s�Ǘ��I�u�W�F�N�g�̐����A�j�����@�̓o�^
	_pStandardBank = new ObjectBank<StandardRenderableContainer*>(
		NewDelManager<StandardRenderableContainer*>(
			RenderableFactory(), RenderableFactory::Create,
			RenderableFactory(), RenderableFactory::Delete));

	//	�`����s�Ǘ��I�u�W�F�N�g�̘A���p�I�u�W�F�N�g�ɁA�݌ɊǗ��I�u�W�F�N�g��o�^
	RenderableComponent::sRegister(_pComponentBank);
}

//----------------------------------------------------------
//	�f�X�g���N�^
//----------------------------------------------------------
RenderableCollection::~RenderableCollection(void)
{
	delete _pComponentBank;
	delete _pRenderableBank;
	delete _pStandardBank;
}

//----------------------------------------------------------
//	�`��Ăяo������i�[�R���e�i��A������R���|�[�l���g���擾
//
// return: IRenderableComponent* �c �R���e�i�i�[�R���|�[�l���g
//
// attrib: override
//----------------------------------------------------------
IRenderableComponent* RenderableCollection::OrderComponent(void)
{
	//	�I�u�W�F�N�g�𔭒�����
	return _pComponentBank->Order();
}

//----------------------------------------------------------
//	�`��Ăяo���Ǘ��I�u�W�F�N�g���擾
//
// return: IRenderableContainer* �c �`��Ăяo���Ǘ��I�u�W�F�N�g
//
// attrib: override
//----------------------------------------------------------
IRenderableContainer* RenderableCollection::OrderContainer(void)
{
	//	�I�u�W�F�N�g�𔭒�����
	return _pRenderableBank->Order();
}

//----------------------------------------------------------
//	�����_�[�X�e�[�g��Ǝ��ɕێ�����A�`��Ăяo���Ǘ��I�u�W�F�N�g���擾
//
// parameter: (in)RenderStates& state �c �����_�[�X�e�[�g�R�s�[���ւ̎Q��
// parameter: (in)bool isMyStates �c �`�掞�Ɏ��g�̃X�e�[�g���p�̗L��
//
// return: IRenderableContainer* �c �`��Ăяo���Ǘ��I�u�W�F�N�g
//
// attrib: override
//----------------------------------------------------------
IRenderableContainer* RenderableCollection::OrderContainer(RenderStates& state,
														   bool isMyStates)
{
	//	�I�u�W�F�N�g�𔭒�����
	StandardRenderableContainer* pTemp = _pStandardBank->Order();

	//	�����_�[�X�e�[�g�̏��������s��
	pTemp->SetRenderStates(state);
	pTemp->Enable(isMyStates);

	return pTemp;
}

//----------------------------------------------------------
//	�`�搧��i�[�R���e�i�A���R���|�[�l���g��ԋp����
//
// parameter: (in)IRenderableComponent pComponent* �c �ԋp����I�u�W�F�N�g�ւ̃|�C���^
//
// attrib: override
//----------------------------------------------------------
void RenderableCollection::ReturnComponent(IRenderableComponent* pComponent)
{
	//	���X�g��ԋp����
	_pComponentBank->Return(pComponent);
}

//----------------------------------------------------------
//	�`��Ăяo���Ǘ��I�u�W�F�N�g��ԋp����
//
// parameter: (in)IRenderableContainer* pContainer �c �ԋp����I�u�W�F�N�g�ւ̃|�C���^
//
// attrib: override
//----------------------------------------------------------
void RenderableCollection::ReturnContainer(IRenderableContainer* pContainer)
{
	//	�ԋp������ʂ���
	RenderableContainer* pTemp = dynamic_cast<RenderableContainer*>(pContainer);

	if (pTemp)
	{
		//	���X�g��ԋp����
		_pRenderableBank->Return(pTemp);
	}
	else
	{
		//	���X�g��ԋp����
		StandardRenderableContainer* p = (StandardRenderableContainer*)(pContainer);
		_pStandardBank->Return(p);
	}
}
