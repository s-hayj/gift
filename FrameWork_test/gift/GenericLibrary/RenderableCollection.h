//----------------------------------------------------------
// file name: RenderableCollection.h
//
// memo: �`����s�I�u�W�F�N�g�Q�̊i�[�A����Ǘ�
//----------------------------------------------------------

#ifndef	__RENDERABLE_COLLECTION_H
#define	__RENDERABLE_COLLECTION_H

#include "IRenderableCollection.h"
#include "RenderableContainer.h"
#include "StandardRenderableContainer.h"

namespace gift
{

	namespace Private
	{

		namespace Renderable
		{

//----------------------------------------------------------
// name: gift::Private::Renderable::RenderableCollection
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableCollection is interface
//
// memo: �`����s�Ɋւ���o�^�I�u�W�F�N�g�Q�̐����Ǘ�
//----------------------------------------------------------
class	RenderableCollection
	: public gift::Renderable::IRenderableCollection
{
private:
	//----------------------------------------------------------
	// name: gift::Private::Renderable::RenderableCollection::RenderableFactory
	//
	// attrib: private nested function object
	//
	// memo: �`����s�Ɋւ���e�I�u�W�F�N�g�������@
	//----------------------------------------------------------
	class	RenderableFactory
	{
	public:
		//----------------------------------------------------------
		//	�`����s�Ǘ��I�u�W�F�N�g�i�[�A���p�I�u�W�F�N�g�̐���
		//
		// parameter: (in)(out)IRenderableComponent*& pValue �c �������ʊi�[��
		//
		// return: IRenderableComponent*& �c �������ʂւ̎Q��
		//----------------------------------------------------------
		gift::Renderable::IRenderableComponent*& Create(gift::Renderable::IRenderableComponent*& pValue)
		{
			pValue = new RenderableComponent();

			return pValue;
		};

		//----------------------------------------------------------
		//	�`����s�Ǘ��I�u�W�F�N�g�̐���
		//
		// parameter: (in)(out)RenderableContainer*& pValue �c �������ʊi�[��
		//
		// return: RenderableContainer*& �c �������ʂւ̎Q��
		//----------------------------------------------------------
		RenderableContainer*& Create(RenderableContainer*& pValue)
		{
			pValue = new RenderableContainer();

			return pValue;
		};

		//----------------------------------------------------------
		//	�����_�[�X�e�[�g��ێ������`����s�Ǘ��I�u�W�F�N�g�̐���
		//
		// parameter: (in)(out)RenderableContainer*& pValue �c �������ʊi�[��
		//
		// return: RenderableContainer*& �c �������ʂւ̎Q��
		//----------------------------------------------------------
		StandardRenderableContainer*& Create(StandardRenderableContainer*& pValue)
		{
			pValue = new StandardRenderableContainer();

			return pValue;
		}

		//----------------------------------------------------------
		//	�`����s�Ǘ��I�u�W�F�N�g�i�[�A���p�I�u�W�F�N�g�̔j��
		//
		// parameter: (in)(out)IRenderableComponent*& pValue �c �j������f�[�^
		//
		// return: IRenderableComponent*& �c �j�����ʂւ̎Q��
		//----------------------------------------------------------
		gift::Renderable::IRenderableComponent*& Delete(gift::Renderable::IRenderableComponent*& pValue)
		{
			delete pValue;

			pValue = NULL;

			return pValue;
		};

		//----------------------------------------------------------
		//	�`����s���ʃI�u�W�F�N�g�̔j��
		//
		// parameter: (in)(out)RenderableContainer*& pValue �c �j������f�[�^
		//
		// return: RenderableContainer*& �c �j�����ʂւ̎Q��
		//----------------------------------------------------------
		RenderableContainer*& Delete(RenderableContainer*& pValue)
		{
			delete pValue;

			pValue = NULL;

			return pValue;
		};

		//----------------------------------------------------------
		//	�����_�[�X�e�[�g��ێ������`����s�Ǘ��I�u�W�F�N�g�̔j��
		//
		// parameter: (in)(out)StandardRenderableContainer*& pValue �c �j������f�[�^
		//
		// return: StandardRenderableContainer*& �c �j�����ʂւ̎Q��
		//----------------------------------------------------------
		StandardRenderableContainer*& Delete(StandardRenderableContainer*& pValue)
		{
			delete pValue;

			pValue = NULL;

			return pValue;
		};
	};

private:
	ObjectBank<gift::Renderable::IRenderableComponent*>*	_pComponentBank;
	ObjectBank<RenderableContainer*>*	_pRenderableBank;
	ObjectBank<StandardRenderableContainer*>*	_pStandardBank;

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	RenderableCollection(void);

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~RenderableCollection(void);

	//----------------------------------------------------------
	//	�`��Ăяo������i�[�R���e�i��A������R���|�[�l���g���擾
	//
	// return: IRenderableComponent* �c �R���e�i�i�[�R���|�[�l���g
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* OrderComponent(void);

	//----------------------------------------------------------
	//	�`��Ăяo���Ǘ��I�u�W�F�N�g���擾
	//
	// return: IRenderableContainer* �c �`��Ăяo���Ǘ��I�u�W�F�N�g
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableContainer* OrderContainer(void);

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
	gift::Renderable::IRenderableContainer* OrderContainer(RenderStates& state, bool isMyStates);

	//----------------------------------------------------------
	//	�`�搧��i�[�R���e�i�A���R���|�[�l���g��ԋp����
	//
	// parameter: (in)IRenderableComponent pComponent* �c �ԋp����I�u�W�F�N�g�ւ̃|�C���^
	//
	// attrib: override
	//----------------------------------------------------------
	void ReturnComponent(gift::Renderable::IRenderableComponent* pComponent);

	//----------------------------------------------------------
	//	�`��Ăяo���Ǘ��I�u�W�F�N�g��ԋp����
	//
	// parameter: (in)IRenderableContainer* pContainer �c �ԋp����I�u�W�F�N�g�ւ̃|�C���^
	//
	// attrib: override
	//----------------------------------------------------------
	void ReturnContainer(gift::Renderable::IRenderableContainer* pContainer);
};

};//namespace Renderable
};//namespace Private
};//namespace gift

#endif
