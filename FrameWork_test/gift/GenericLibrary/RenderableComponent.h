//----------------------------------------------------------
// file name: RenderableComponent.h
//
// memo: �`��Ăяo���R���e�i�A���p�N���X
//----------------------------------------------------------

#ifndef	__RENDERABLE_COMPONENT_H
#define	__RENDERABLE_COMPONENT_H

#include "IComponent.h"
#include "IRenderableContainer.h"
#include "ObjectBank.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::IRenderableComponent
//
// attrib: interface
//
// memo: �`��Ǘ��I�u�W�F�N�g��`�揇�ɘA���Ǘ����邽�߂̃C���^�[�t�F�[�X
//----------------------------------------------------------
class	IRenderableComponent
{
public:
	virtual ~IRenderableComponent(void) {};

	//----------------------------------------------------------
	//	���g���i�[���Ă���I�u�W�F�N�g�Q�̃\�[�g�̗L��
	//
	// return: bool �c �\�[�g�̗L��
	//�@�@�@�@true �c �\�[�g���s��
	//----------------------------------------------------------
	virtual bool IsSort(void) = 0;

	//----------------------------------------------------------
	//	�i�[���Ă���I�u�W�F�N�g�Q���\�[�g�����邩�̗L��
	//
	// parameter: (in)bool enable �c �\�[�g�̗L��
	//
	// memo: true �́A�\�[�g���s���悤�ɂ�����
	//----------------------------------------------------------
	virtual void SetSort(bool enable) = 0;

	//----------------------------------------------------------
	//	���[�U�[���������Ă��邩�A�V�X�e���ɃR���|�[�l���g��ԋp�̗L��
	//
	// return: bool �c �V�X�e���ɃI�u�W�F�N�g�̕ԋp�̗L��
	//
	// memo: true �́A�R���|�[�l���g�����[�U�[���ێ����Ă��邱�Ƃ��w���A
	//�@�@�@�V�X�e���ɂ́A�ԋp����Ȃ��B
	//----------------------------------------------------------
	virtual bool IsUsed(void) = 0;

	//----------------------------------------------------------
	//	���[�U�[���������Ă��邩�̗L��
	//
	// parameter: (in)bool UserUses �c ���[�U�[���������Ă��邩�̗L��
	//
	// memo: false �́A���[�U�[���������Ă��Ȃ����Ƃ��w���A
	//�@�@�@�g���Ȃ��Ȃ����Ƃ��ɁA�V�X�e���ɕԋp���ꗘ�p�ł��Ȃ��Ȃ�
	//----------------------------------------------------------
	virtual void SetUsed(bool UserUses) = 0;

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̘A����Ԃ��ێ������邩�̗L��
	//
	// return: bool �c �A����Ԉێ��̗L��
	//
	// memo: true �́A�A����Ԃ�j������B�j����A�V�X�e���ɕԋp���ꗘ�p�s��
	//----------------------------------------------------------
	virtual bool Finish(void) = 0;

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̘A����Ԃ��ێ����邩�̗L����ݒ�
	//
	// parameter: (in)bool enable �c �`��I�����ɘA����Ԃ��ǂ����邩
	//
	// memo: true �̂Ƃ��A�`��I�����ɘA����Ԃ�j�����A�V�X�e���ɕԋp���܂�
	//----------------------------------------------------------
	virtual void SetFinish(bool enable) = 0;

	//----------------------------------------------------------
	//	�`��Ǘ��I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableContainer* pContainer �c ���s����I�u�W�F�N�g
	// parameter: (in)bool isDisposable = false �c �o�^�I�u�W�F�N�g�j���̗L��
	//
	// memo: isDisposable �� true �ɂ���ƁA�`�揈���I����� pContainer
	//�@�@�@��j�����܂��B
	//----------------------------------------------------------
	virtual void Register(IRenderableContainer* pContainer,
		bool isDisposable = false) = 0;

	//----------------------------------------------------------
	//	�i�[���Ă���`��Ǘ��I�u�W�F�N�g���Q��
	//
	// return: IRenderableContainer* �c �`����s�Ǘ��I�u�W�F�N�g�ւ̃|�C���^
	//----------------------------------------------------------
	virtual IRenderableContainer* GetRenderable(void) = 0;

	//----------------------------------------------------------
	//	�����̃R���e�i�����g�ɘA��������
	//
	// parameter: (in)IRenderableComponent* pComponent �c �A��������R���e�i
	//----------------------------------------------------------
	virtual void Connect(IRenderableComponent* pComponent) = 0;

	//----------------------------------------------------------
	//	���g�̘A�����Ă��鎟�̃R���e�i�I�u�W�F�N�g���Q��
	//
	// return: IRenderableComponent* �c ���̃I�u�W�F�N�g
	//----------------------------------------------------------
	virtual IRenderableComponent* GetNext(void) = 0;

	//----------------------------------------------------------
	//	���g�̘A�����鎟�̃R���e�i�I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableComponent* pComponent �c �o�^����R���e�i
	//----------------------------------------------------------
	virtual void SetNext(IRenderableComponent* pComponent) = 0;

	//----------------------------------------------------------
	//	���g�̘A�����Ă���O�̃R���e�i�I�u�W�F�N�g���Q��
	//
	// return: IRenderableComponent* �c �O�̃I�u�W�F�N�g
	//----------------------------------------------------------
	virtual IRenderableComponent* GetBack(void) = 0;

	//----------------------------------------------------------
	//	���g�̘A������O�̃R���e�i�I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableComponent* pComponent �c �o�^����R���e�i
	//----------------------------------------------------------
	virtual void SetBack(IRenderableComponent* pComponent) = 0;

	//----------------------------------------------------------
	//	���g�����g���A������I�u�W�F�N�g�Q����A��������
	//----------------------------------------------------------
	virtual void Disconnect(void) = 0;

	//----------------------------------------------------------
	//	�R���e�i�����s���ꂽ��Ԃɖ߂�
	//----------------------------------------------------------
	virtual void Initialize(void) = 0;

	//----------------------------------------------------------
	//	�i�[���Ă���`��I�u�W�F�N�g�����s����
	//
	// return: IRenderableComponent* �c ���Ɏ��s����R���e�i�ւ̃|�C���^
	//----------------------------------------------------------
	virtual IRenderableComponent* Execute(void) = 0;
};

};//namespace Renderable

namespace Private
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Private::Renderable::DummyRenderableComponent
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableComponent is interface
//
// memo: �`��Ǘ��I�u�W�F�N�g��A���Ǘ����邽�߂̖��[�_�~�[�I�u�W�F�N�g
//----------------------------------------------------------
class	DummyRenderableComponent
	: public gift::Renderable::IRenderableComponent
{
private:
	gift::Renderable::IRenderableComponent*	_pNext;
	gift::Renderable::IRenderableComponent*	_pBack;

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	DummyRenderableComponent(void)
		: _pNext(NULL), _pBack(NULL)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~DummyRenderableComponent(void)
	{
	};

	//----------------------------------------------------------
	//	���g���i�[���Ă���I�u�W�F�N�g�Q�̃\�[�g�̗L��
	//
	// return: bool �c �\�[�g�̗L��
	//�@�@�@�@true �c �\�[�g���s��
	//
	// attrib: override
	//----------------------------------------------------------
	bool IsSort(void)
	{
		return false;
	};

	//----------------------------------------------------------
	//	�i�[���Ă���I�u�W�F�N�g�Q���\�[�g�����邩�̗L��
	//
	// parameter: (in)bool enable �c �\�[�g�̗L��
	//
	// memo: true �́A�\�[�g���s���悤�ɂ�����
	//
	// attrib: override
	//----------------------------------------------------------
	void SetSort(bool enable)
	{
	};

	//----------------------------------------------------------
	//	���[�U�[���������Ă��邩�A�V�X�e���ɃR���|�[�l���g��ԋp�̗L��
	//
	// return: bool �c �V�X�e���ɃI�u�W�F�N�g�̕ԋp�̗L��
	//
	// memo: true �́A�R���|�[�l���g�����[�U�[���ێ����Ă��邱�Ƃ��w���A
	//�@�@�@�V�X�e���ɂ́A�ԋp����Ȃ��B
	//
	// attrib: override
	//----------------------------------------------------------
	bool IsUsed(void)
	{
		return true;
	};

	//----------------------------------------------------------
	//	���[�U�[���������Ă��邩�̗L��
	//
	// parameter: (in)bool UserUses �c ���[�U�[���������Ă��邩�̗L��
	//
	// memo: false �́A���[�U�[���������Ă��Ȃ����Ƃ��w���A
	//�@�@�@�g���Ȃ��Ȃ����Ƃ��ɁA�V�X�e���ɕԋp���ꗘ�p�ł��Ȃ��Ȃ�
	//
	// attrib: override
	//----------------------------------------------------------
	void SetUsed(bool UserUses)
	{
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̘A����Ԃ��ێ������邩�̗L��
	//
	// return: bool �c �A����Ԉێ��̗L��
	//
	// memo: true �́A�A����Ԃ�j������B�j����A�V�X�e���ɕԋp���ꗘ�p�s��
	//
	// attrib: override
	//----------------------------------------------------------
	bool Finish(void)
	{
		return false;
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̘A����Ԃ��ێ����邩�̗L����ݒ�
	//
	// parameter: (in)bool enable �c �`��I�����ɘA����Ԃ��ǂ����邩
	//
	// memo: true �̂Ƃ��A�`��I�����ɘA����Ԃ�j�����A�V�X�e���ɕԋp���܂�
	//
	// attrib: override
	//----------------------------------------------------------
	void SetFinish(bool enable)
	{
	};

	//----------------------------------------------------------
	//	�`��Ǘ��I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableContainer* pContainer �c ���s����I�u�W�F�N�g
	// parameter: (in)bool isDisposable = false �c �o�^�I�u�W�F�N�g�j���̗L��
	//
	// memo: isDisposable �� true �ɂ���ƁA�`�揈���I����� pContainer
	//�@�@�@��j�����܂��B
	//----------------------------------------------------------
	void Register(gift::Renderable::IRenderableContainer* pContainer,
		bool isDisposable = false)
	{
	};

	//----------------------------------------------------------
	//	�i�[���Ă���`��Ǘ��I�u�W�F�N�g���Q��
	//
	// return: IRenderableContainer* �c �`����s�Ǘ��I�u�W�F�N�g�ւ̃|�C���^
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableContainer* GetRenderable(void)
	{
		return NULL;
	};

	//----------------------------------------------------------
	//	�����̃R���e�i�����g�ɘA��������
	//
	// parameter: (in)IRenderableComponent* pComponent �c �A��������R���e�i
	//
	// attrib: override
	//----------------------------------------------------------
	void Connect(gift::Renderable::IRenderableComponent* pComponent)
	{
	};

	//----------------------------------------------------------
	//	���g�̘A�����Ă��鎟�̃R���e�i�I�u�W�F�N�g���Q��
	//
	// return: IRenderableComponent* �c ���̃I�u�W�F�N�g
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* GetNext(void)
	{
		return _pNext;
	};

	//----------------------------------------------------------
	//	���g�̘A�����鎟�̃R���e�i�I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableComponent* pComponent �c �o�^����R���e�i
	//
	// attrib: override
	//----------------------------------------------------------
	void SetNext(gift::Renderable::IRenderableComponent* pComponent)
	{
		_pNext = pComponent;
	};

	//----------------------------------------------------------
	//	���g�̘A�����Ă���O�̃R���e�i�I�u�W�F�N�g���Q��
	//
	// return: IRenderableComponent* �c �O�̃I�u�W�F�N�g
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* GetBack(void)
	{
		return _pBack;
	};

	//----------------------------------------------------------
	//	���g�̘A������O�̃R���e�i�I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableComponent* pComponent �c �o�^����R���e�i
	//
	// attrib: override
	//----------------------------------------------------------
	void SetBack(gift::Renderable::IRenderableComponent* pComponent)
	{
		_pBack = pComponent;
	};

	//----------------------------------------------------------
	//	�R���e�i�����s���ꂽ��Ԃɖ߂�
	//
	// attrib: override
	//----------------------------------------------------------
	void Initialize(void)
	{
		_pBack = NULL;
		_pNext = NULL;
	};

	//----------------------------------------------------------
	//	���g�����g���A������I�u�W�F�N�g�Q����A��������
	//
	// attrib: override
	//----------------------------------------------------------
	void Disconnect(void)
	{
	};

	//----------------------------------------------------------
	//	�i�[���Ă���`��I�u�W�F�N�g�����s����
	//
	// return: IRenderableComponent* �c ���Ɏ��s����R���e�i�ւ̃|�C���^
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* Execute(void)
	{
		return _pBack;
	};
};


//----------------------------------------------------------
// name: gift::Private::Renderable::RenderableComponent
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableComponent is interface
//
// memo: �`��Ǘ��I�u�W�F�N�g��`�揇�ɘA���Ǘ�����
//----------------------------------------------------------
class	RenderableComponent
	: public gift::Renderable::IRenderableComponent
{
public:
	enum
	{
		BACK = 0,
		MAIN = 1,
		NEXT = 2,
	};

private:
	gift::Renderable::IRenderableContainer*	_pRenderable;	//	�`����s�Ǘ��I�u�W�F�N�g

	bool					_sort;			//	�\�[�g�̗L��
	bool					_used;			//	�V�X�e���Ԋ҂̗L��
	bool					_finish;		//	�A�������̗L��
	bool					_isDisposable;	//	�g���̂ăI�u�W�F�N�g�̗L��
	int						_counter;		//	���ɎQ�Ƃ���A����ԍ�
	gift::Renderable::IRenderableComponent*	_pNext[3];		//	�A�����邽�߂̃|�C���^
	DummyRenderableComponent	_dummyTop;	//	�A���̐擪�p��f�[�^
	DummyRenderableComponent	_dummyLast;	//	�A���̖��[�p��f�[�^

	static ObjectBank<gift::Renderable::IRenderableComponent*>*	s_pBank;

public:
	//----------------------------------------------------------
	//	�`�揇�Ɋi�[����R���|�[�l���g�̍݌ɊǗ��I�u�W�F�N�g�̓o�^
	//
	// parameter: (in)ObjectBank<IRenderableComponent*>* pBank �c �݌ɊǗ�
	//
	// memo: �j���͍s��Ȃ��i�ʂ̃I�u�W�F�N�g���j�����Ǘ����Ă���j
	//----------------------------------------------------------
	static void sRegister(ObjectBank<gift::Renderable::IRenderableComponent*>* pBank)
	{
		s_pBank = pBank;
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	RenderableComponent(void);

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~RenderableComponent(void);

	//----------------------------------------------------------
	//	���g���i�[���Ă���I�u�W�F�N�g�Q�̃\�[�g�̗L��
	//
	// return: bool �c �\�[�g�̗L��
	//�@�@�@�@true �c �\�[�g���s��
	//
	// attrib: override
	//----------------------------------------------------------
	bool IsSort(void)
	{
		return _sort;
	};

	//----------------------------------------------------------
	//	�i�[���Ă���I�u�W�F�N�g�Q���\�[�g�����邩�̗L��
	//
	// parameter: (in)bool enable �c �\�[�g�̗L��
	//
	// memo: true �́A�\�[�g���s���悤�ɂ�����
	//
	// attrib: override
	//----------------------------------------------------------
	void SetSort(bool enable)
	{
		_sort = enable;
	};

	//----------------------------------------------------------
	//	���[�U�[���������Ă��邩�A�V�X�e���ɃR���|�[�l���g��ԋp�̗L��
	//
	// return: bool �c �V�X�e���ɃI�u�W�F�N�g�̕ԋp�̗L��
	//
	// memo: true �́A�R���|�[�l���g�����[�U�[���ێ����Ă��邱�Ƃ��w���A
	//�@�@�@�V�X�e���ɂ́A�ԋp����Ȃ��B
	//
	// attrib: override
	//----------------------------------------------------------
	bool IsUsed(void)
	{
		return _used;
	};

	//----------------------------------------------------------
	//	���[�U�[���������Ă��邩�̗L��
	//
	// parameter: (in)bool UserUses �c ���[�U�[���������Ă��邩�̗L��
	//
	// memo: false �́A���[�U�[���������Ă��Ȃ����Ƃ��w���A
	//�@�@�@�g���Ȃ��Ȃ����Ƃ��ɁA�V�X�e���ɕԋp���ꗘ�p�ł��Ȃ��Ȃ�
	//
	// attrib: override
	//----------------------------------------------------------
	void SetUsed(bool UserUses)
	{
		_used = UserUses;
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̘A����Ԃ��ێ������邩�̗L��
	//
	// return: bool �c �A����Ԉێ��̗L��
	//
	// memo: true �́A�A����Ԃ�j������B�j����A�V�X�e���ɕԋp���ꗘ�p�s��
	//
	// attrib: override
	//----------------------------------------------------------
	bool Finish(void)
	{
		return _finish;
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̘A����Ԃ��ێ����邩�̗L����ݒ�
	//
	// parameter: (in)bool enable �c �`��I�����ɘA����Ԃ��ǂ����邩
	//
	// memo: true �̂Ƃ��A�`��I�����ɘA����Ԃ�j�����A�V�X�e���ɕԋp���܂�
	//
	// attrib: override
	//----------------------------------------------------------
	void SetFinish(bool enable)
	{
		_finish = enable;
	};

	//----------------------------------------------------------
	//	�`��Ǘ��I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableContainer* pContainer �c ���s����I�u�W�F�N�g
	// parameter: (in)bool isDisposable = false �c �o�^�I�u�W�F�N�g�j���̗L��
	//
	// memo: isDisposable �� true �ɂ���ƁA�`�揈���I����� pContainer
	//�@�@�@��j�����܂��B
	//
	// attrib: override
	//----------------------------------------------------------
	void Register(gift::Renderable::IRenderableContainer* pContainer,
		bool isDisposable = false)
	{
		_pRenderable = pContainer;
		_isDisposable = isDisposable;
	};

	//----------------------------------------------------------
	//	�i�[���Ă���`��Ǘ��I�u�W�F�N�g���Q��
	//
	// return: IRenderableContainer* �c �`����s�Ǘ��I�u�W�F�N�g�ւ̃|�C���^
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableContainer* GetRenderable(void)
	{
		return _pRenderable;
	};

	//----------------------------------------------------------
	//	�����̃R���e�i�����g�ɘA��������
	//
	// parameter: (in)IRenderableComponent* pComponent �c �A��������R���e�i
	//
	// attrib: override
	//----------------------------------------------------------
	void Connect(gift::Renderable::IRenderableComponent* pComponent);

	//----------------------------------------------------------
	//	���g�̘A�����Ă��鎟�̃R���e�i�I�u�W�F�N�g���Q��
	//
	// return: IRenderableComponent* �c ���̃I�u�W�F�N�g
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* GetNext(void)
	{
		return _pNext[NEXT];
	};

	//----------------------------------------------------------
	//	���g�̘A�����鎟�̃R���e�i�I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableComponent* pComponent �c �o�^����R���e�i
	//
	// attrib: override
	//----------------------------------------------------------
	void SetNext(gift::Renderable::IRenderableComponent* pComponent)
	{
		_pNext[NEXT] = pComponent;
	};

	//----------------------------------------------------------
	//	���g�̘A�����Ă���O�̃R���e�i�I�u�W�F�N�g���Q��
	//
	// return: IRenderableComponent* �c �O�̃I�u�W�F�N�g
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* GetBack(void)
	{
		return _pNext[BACK];
	};

	//----------------------------------------------------------
	//	���g�̘A������O�̃R���e�i�I�u�W�F�N�g��o�^����
	//
	// parameter: (in)IRenderableComponent* pComponent �c �o�^����R���e�i
	//
	// attrib: override
	//----------------------------------------------------------
	void SetBack(gift::Renderable::IRenderableComponent* pComponent)
	{
		_pNext[BACK] = pComponent;
	};

	//----------------------------------------------------------
	//	���g�����g���A������I�u�W�F�N�g�Q����A��������
	//
	// attrib: override
	//----------------------------------------------------------
	void Disconnect(void);

	//----------------------------------------------------------
	//	�R���e�i�����s���ꂽ��Ԃɖ߂�
	//
	// attrib: override
	//----------------------------------------------------------
	void Initialize(void);

	//----------------------------------------------------------
	//	�i�[���Ă���`��I�u�W�F�N�g�����s����
	//
	// return: IRenderableComponent* �c ���Ɏ��s����R���e�i�ւ̃|�C���^
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* Execute(void);
};

};//namespace Renderable
};//namespace Private
};//namespace gift

#endif
