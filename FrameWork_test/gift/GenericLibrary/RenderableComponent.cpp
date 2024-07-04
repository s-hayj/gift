//----------------------------------------------------------
// file name: RenderableComponent.cpp
//
// memo: �`����s�Ǘ��I�u�W�F�N�g��`�揇�ԂɘA���Ǘ��A���s����
//----------------------------------------------------------

#include <stdio.h>
#include "RenderableComponent.h"

using namespace gift;
using namespace gift::Renderable;
using namespace gift::Private;
using namespace gift::Private::Renderable;

//----------------------------------------------------------
//	RenderableComponent �̐ÓI�����o�ϐ��̏�����
//----------------------------------------------------------
ObjectBank<IRenderableComponent*>* RenderableComponent::s_pBank = NULL;

//----------------------------------------------------------
//	�R���X�g���N�^
//----------------------------------------------------------
RenderableComponent::RenderableComponent(void)
: _pRenderable(NULL), _sort(false), _used(false),
	_finish(true), _isDisposable(false), _counter(0)
{
	_pNext[BACK] = NULL;
	_pNext[MAIN] = &_dummyTop;
	_pNext[NEXT] = NULL;

	_dummyTop.SetNext(&_dummyLast);
	_dummyLast.SetBack(&_dummyTop);
}

//----------------------------------------------------------
//	�f�X�g���N�^
//----------------------------------------------------------
RenderableComponent::~RenderableComponent(void)
{
	this->Initialize();
}

//----------------------------------------------------------
//	�����̃R���e�i�����g�ɘA��������
//
// parameter: (in)IRenderableComponent* pComponent �c �A��������R���e�i
//----------------------------------------------------------
void RenderableComponent::Connect(IRenderableComponent* pComponent)
{
	IRenderableComponent* pTemp = _dummyLast.GetBack();

	//	���[�i�_�~�[�̎�O�j�ɑ��ݘA��
	pComponent->SetNext(&_dummyLast);
	_dummyLast.SetBack(pComponent);

	//	�V�����R���e�i��{���̖��[�ɑ��ݘA��
	pComponent->SetBack(pTemp);
	pTemp->SetNext(pComponent);
}

//----------------------------------------------------------
//	���g�����g���A������I�u�W�F�N�g�Q����A��������
//----------------------------------------------------------
void RenderableComponent::Disconnect(void)
{
	//	���g���N���̌��ɘA������Ă���
	if (_pNext[BACK])
	{
		//	���g�̑O�̃R���e�i�����̃R���e�i�ƘA��������
		_pNext[BACK]->SetNext(_pNext[NEXT]);
	}

	//	���g���N�������ɘA�������Ă���
	if (_pNext[NEXT])
	{
		//	���g�̌��̃R���e�i��O�̃R���e�i�ƘA��������
		_pNext[NEXT]->SetBack(_pNext[BACK]);
	}

	_pNext[BACK] = NULL;
	_pNext[NEXT] = NULL;


	//	���g���Ǘ����Ă����`��I�u�W�F�N�g�Q��j������
	IRenderableComponent* pTemp = _pNext[MAIN]->GetNext();

	//	���[�܂ő���
	while (pTemp != (&_dummyLast))
	{
		//	�A���I�u�W�F�N�g�Q���番��������
		pTemp->Disconnect();

		//	���[�U�[���Ǘ����Ă��Ȃ�
		if (!pTemp->IsUsed())
		{
			//	�������̏�Ԃɖ߂�
			pTemp->Initialize();

			//	�R���e�i�q�ɂɃR���e�i��ԋp����
			RenderableComponent::s_pBank->Return(pTemp);
		}

		//	���̃R���e�i�𑖍�
		pTemp = _pNext[MAIN]->GetNext();
	}

	_dummyTop.SetNext(&_dummyLast);
	_dummyLast.SetBack(&_dummyTop);
}

//----------------------------------------------------------
//	�R���e�i�����s���ꂽ��Ԃɖ߂�
//----------------------------------------------------------
void RenderableComponent::Initialize(void)
{
	_sort = false;
	_used = false;
	_finish = true;
	_counter = 0;

	//	�j����C����Ă���
	if (_isDisposable)
	{
		//	�j������Ă��Ȃ�
		if (_pRenderable)
		{
			delete _pRenderable;
		}
	}

	//	�e�A����Ԃ�j������
	this->Disconnect();
}

//----------------------------------------------------------
//	�i�[���Ă���`��I�u�W�F�N�g�����s����
//
// return: IRenderableComponent* �c ���Ɏ��s����R���e�i�ւ̃|�C���^
//----------------------------------------------------------
IRenderableComponent* RenderableComponent::Execute(void)
{
	IRenderableComponent* pTemp = NULL;

	switch	(_counter)
	{
	//	�͂��߂̎��s
	case 0:
		//	���g�̊i�[����`�惊�X�g��]��
		pTemp = _pNext[MAIN]->GetNext();
		break;

	//	���ڂ̎��s
	case 1:
		//	���g���A�����鎟�̃R���e�i��]��
		pTemp = _pNext[NEXT];
		break;

	//	�O��ڂ̎��s
	case 2:
		//	���g���A������O�̃R���e�i��]��
		pTemp = _pNext[BACK];
		break;

	default:
		break;
	}

	_counter = (_counter + 1) % 3;

	return pTemp;
}
