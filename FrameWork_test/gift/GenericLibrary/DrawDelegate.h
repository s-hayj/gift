//----------------------------------------------------------
// file name: DrawDelegate.h
//
// memo: �`�惁�\�b�h���Ϗ����邽�߂́A�e�C���^�[�t�F�[�X�ƃN���X
//----------------------------------------------------------

#ifndef	__DRAW_DELEGATE_H
#define	__DRAW_DELEGATE_H

#include <stdio.h>
#include "ICommand.h"
#include "IDrawCommand.h"
#include "GenericLibrary.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::DrawDelegate
//
// attrib: final class
//
// memo: �`�掞�̊e�Ăяo����s�l
//----------------------------------------------------------
class	DrawDelegate
{
private:
	//----------------------------------------------------------
	// name: gift::Renderable::DrawDelegate::DrawFunction
	//
	// attrib: private template sub class
	//
	// base: gift::Renderable::IDrawCommand is interface
	//
	// typename: bool �c true �̂Ƃ��A�i�[�I�u�W�F�N�g�̔j���@�\��ǉ�����
	// typename: T �c �Ăяo�����̌^
	//
	// memo: �`��̊e�Ăяo�����\�b�h���i�[�A���s����
	//�@�@�@�i�[�I�u�W�F�N�g�̔j�����@��o�^���A�����j������
	//----------------------------------------------------------
	template<bool isDisposable, class T>
	class DrawFunction
		: public IDrawCommand
	{
	public:
		//	�i�[���郁���o�֐��̌^
		typedef typename void (T::*Method)(RenderStates* pStates);

	private:
		T*			_pObj;		//	�Ăяo�����ւ̃|�C���^
		Method		_begin;		//	�`��J�n���̃��\�b�h
		Method		_end;		//	�`��̌㏈�����\�b�h
		ICommand*	_pReleaser;	//	�i�[�I�u�W�F�N�g�̔j�����@

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		// parameter: (in)T* pObj �c �Ăяo�����ւ̃|�C���^
		// parameter: (in)Method begin �c �`��J�n���̃��\�b�h
		// parameter: (in)Method end �c �`��̌㏈�����\�b�h
		// parameter: (in)ICommand* pReleaser �c �i�[�I�u�W�F�N�g�̔j�����@
		//----------------------------------------------------------
		DrawFunction(T* pObj, Method begin, Method end, ICommand* pReleaser)
			: _pObj(pObj), _begin(begin), _end(end), _pReleaser(pReleaser)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//----------------------------------------------------------
		~DrawFunction(void)
		{
			_pObj = NULL;

			//	�j�����@���o�^����Ă���
			if (_pReleaser)
			{
				delete _pReleaser;
				_pReleaser = NULL;
			}
		};

		//----------------------------------------------------------
		//	�`��J�n���̃��\�b�h���Ăяo��
		//
		// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
		//
		// attrib: override
		//----------------------------------------------------------
		void DrawBegin(RenderStates* pStates)
		{
			//	�`��J�n���\�b�h���o�^����Ă���
			if (_begin)
			{
				(_pObj->*_begin)(pStates);
			}
		};

		//----------------------------------------------------------
		//	�`��̌㏈�����\�b�h���Ăяo��
		//
		// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
		//
		// attrib: override
		//----------------------------------------------------------
		void DrawEnd(RenderStates* pStates)
		{
			//	�㏈�����\�b�h���o�^����Ă���
			if (_end)
			{
				(_pObj->*_end)(pStates);
			}
		};
	};

	//----------------------------------------------------------
	// name: gift::Renderable::DrawDelegate::DrawFunction
	//
	// attrib: private template sub class
	//
	// base: gift::Renderable::IDrawCommand is interface
	//
	// typename: T �c �Ăяo�����I�u�W�F�N�g�̌^
	//
	// memo: �`��̊e�Ăяo�����\�b�h���i�[�A���s����
	//----------------------------------------------------------
	template<class T>
	class DrawFunction<false, T>
		: public IDrawCommand
	{
	public:
		//	�i�[���郁���o�֐��̌^
		typedef typename void (T::*Method)(RenderStates* pStates);

	private:
		T*		_pObj;	//	�Ăяo�����ւ̃|�C���^
		Method	_begin;	//	�`��J�n���̃��\�b�h
		Method	_end;	//	�`��̌㏈�����\�b�h

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		// parameter: (in)T* pObj �c �Ăяo�����ւ̃|�C���^
		// parameter: (in)Method begin �c �`��J�n���̃��\�b�h
		// parameter: (in)Method end �c �`��̌㏈�����\�b�h
		//----------------------------------------------------------
		DrawFunction(T* pObj, Method begin, Method end = 0)
			: _pObj(pObj), _begin(begin), _end(end)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//----------------------------------------------------------
		~DrawFunction(void)
		{
		};

		//----------------------------------------------------------
		//	�`��J�n���̃��\�b�h���Ăяo��
		//
		// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
		//
		// attrib: override
		//----------------------------------------------------------
		void DrawBegin(RenderStates* pStates)
		{
			//	�`��J�n���\�b�h���o�^����Ă���
			if (_begin)
			{
				(_pObj->*_begin)(pStates);
			}
		};

		//----------------------------------------------------------
		//	�`��̌㏈�����\�b�h���Ăяo��
		//
		// parameter: (in)RenderStates* pStates �c �����_�[�X�e�[�g
		//
		// attrib: override
		//----------------------------------------------------------
		void DrawEnd(RenderStates* pStates)
		{
			//	���\�b�h���o�^����Ă���
			if (_end)
			{
				(_pObj->*_end)(pStates);
			}
		};
	};

public:
	//----------------------------------------------------------
	// name: gift::Renderable::DrawDelegate::Null
	//
	// attrib: public template final struct
	//
	// typename: T �c �i�[����Ăяo�����I�u�W�F�N�g�̌^
	//
	// memo: �o�^���\�b�h�� null �ŏ��������邽�߂̃I�u�W�F�N�g
	//----------------------------------------------------------
	template<class T>
	struct Null
	{
		//	�i�[���郁���o�֐��̌^
		typedef typename void (T::*Method)(RenderStates*);

		//----------------------------------------------------------
		//	& ���Z�q�I�[�o�[���[�h
		//
		// return: void (T::*)(RenderStates*) �c null ��Ԃ�
		//----------------------------------------------------------
		Method operator & (void)
		{
			return 0;
		};
	};

private:
	bool			_auto;		//	�I�u�W�F�N�g�j���ӔC�̗L��
	IDrawCommand*	_pCommand;	//	�e�`�惁�\�b�h�Ăяo���I�u�W�F�N�g

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	DrawDelegate(void)
		: _auto(true), _pCommand(NULL)
	{
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)T& obj �c �Ăяo�����I�u�W�F�N�g�ւ̎Q��
	// parameter: (in)void (T::*begin)(RenderStates*) �c �`��J�n���\�b�h
	// parameter: (in)void (T::*end)(RenderStates*) �c �`��̌㏈�����\�b�h
	//----------------------------------------------------------
	template<class T>
		DrawDelegate(T& obj, typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*))
			: _auto(true)
	{
		//	�Ăяo�����I�u�W�F�N�g��j�����Ȃ��A�`��Ăяo���I�u�W�F�N�g�̍쐬
		_pCommand = new DrawFunction<false, T>(&obj, begin, end);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)T* pObj �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)void (T::*begin)(RenderStates*) �c �`��J�n���\�b�h
	// parameter: (in)void (T::*end)(RenderStates*) �c �`��̌㏈�����\�b�h
	// parameter: (in)ICommand* pDeleteHelper �c �j�����@�ւ̃|�C���^
	//----------------------------------------------------------
	template<class T>
		DrawDelegate(T* pObj, typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*), ICommand* pDeleteHelper)
			: _auto(true)
	{
		//	�Ăяo�����I�u�W�F�N�g��j������A�`��Ăяo���I�u�W�F�N�g���쐬
		_pCommand =
			new DrawFunction<true, T>(pObj, begin, end, pDeleteHelper);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)T* pObj �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)void (T::*begin)(RenderStates*) �c �`��J�n���\�b�h
	// parameter: (in)void (T::*end)(RenderStates*) �c �`��̌㏈�����\�b�h
	//----------------------------------------------------------
	template<class T>
		DrawDelegate(T* pObj, typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*))
			: _auto(true)
	{
		//	�Ăяo�����I�u�W�F�N�g��j�����Ȃ��A�`��Ăяo���I�u�W�F�N�g���쐬
		_pCommand =
			new DrawFunction<false, T>(pObj, begin, end);
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~DrawDelegate(void)
	{
		//	�I�u�W�F�N�g�̔j���ӔC�������Ă���
		if (_auto)
		{
			this->Release();
		}
	};

	//----------------------------------------------------------
	//	�`��̊e�Ăяo�����\�b�h��o�^����
	//
	// parameter: (in)WriteMode::MODE mode �c �o�^�I�v�V����
	// parameter: (in)T& obj �c �Ăяo�����I�u�W�F�N�g�ւ̎Q��
	// parameter: (in)void (T::*begin)(RenderStates*) �c �`��J�n���\�b�h
	// parameter: (in)void (T::*end)(RenderStates*) �c �`��̌㏈�����\�b�h
	//
	// return: bool �c �o�^��������
	//			true�c �o�^�����i�ȑO�̓o�^���͔j�������j
	//			false�c�o�^���s�i�㏑�����֎~��ԂŁA���łɓo�^���������Ă���j
	//----------------------------------------------------------
	template<class T>
		bool Register(WriteMode::MODE mode, T& obj,
			typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*))
	{
		//	��x�����̓o�^
		if (mode == WriteMode::Once)
		{
			//	���łɓo�^����Ă���
			if (_pCommand)
			{
				return false;
			}
		}

		//	���łɓo�^����Ă�����j��
		if (_auto)
		{
			if (_pCommand)
			{
				delete _pCommand;
			}
		}

		//	�Ăяo�����I�u�W�F�N�g��j�����Ȃ��A�`��Ăяo���I�u�W�F�N�g�𐶐�
		_pCommand = new DrawFunction<false, T>(&obj, begin, end);

		return true;
	};

	//----------------------------------------------------------
	//	�`��̊e�Ăяo�����\�b�h���A�i�[�I�u�W�F�N�g�̔j�����@�Ƌ��ɓo�^����
	//
	// parameter: (in)WriteMode::MODE mode �c �o�^�I�v�V����
	// parameter: (in)T* pObj �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)void (T::*begin)(RenderStates*) �c �`��J�n���\�b�h
	// parameter: (in)void (T::*end)(RenderStates*) �c �`��̌㏈�����\�b�h
	// parameter: (in)ICommand* pDeleteHelper �c �I�u�W�F�N�g�̔j�����@
	//
	// return: bool �c �o�^��������
	//�@�@�@�@true �c �o�^�����i�ȑO�̓o�^���͔j������Ă��܂�
	//�@�@�@�@false �c �o�^���s�i�㏑�����֎~��ԂŁA���łɓo�^���������Ă���j
	//----------------------------------------------------------
	template<class T>
		bool Register(WriteMode::MODE mode, T* pObj,
			typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*), ICommand* pDeleteHelper)
	{
		//	��x�����̓o�^
		if (mode == WriteMode::Once)
		{
			//	���łɓo�^����Ă���
			if (_pCommand)
			{
				return false;
			}
		}

		//	���łɓo�^����Ă�����j������
		if (_auto)
		{
			if (_pCommand)
			{
				delete _pCommand;
			}
		}

		//	�Ăяo�����̃I�u�W�F�N�g��j������A�`��Ăяo���I�u�W�F�N�g�𐶐�
		_pCommand =
			new DrawFunction<true, T>(pObj, begin, end, pDeleteHelper);

		return true;
	};

	//----------------------------------------------------------
	//	�`��̊e�Ăяo�����\�b�h��o�^����
	//
	// parameter: (in)WriteMode::MODE mode �c �o�^�I�v�V����
	// parameter: (in)T* pObj �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)void (T::*begin)(RenderStates*) �c �`��J�n���\�b�h
	// parameter: (in)void (T::*end)(RenderStates*) �c �`��̌㏈�����\�b�h
	//
	// return: bool �c �o�^��������
	//�@�@�@�@true �c �o�^�����i�ȑO�̓o�^���͔j������Ă��܂��j
	//�@�@�@�@false �c �o�^���s�i�㏑�����֎~��ԂŁA���łɓo�^���������Ă���j
	//----------------------------------------------------------
	template<class T>
		bool Register(WriteMode::MODE mode, T* pObj,
			typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*))
	{
		//	��x�����̓o�^
		if (mode == WriteMode::Once)
		{
			//	���łɓo�^����Ă���
			if (_pCommand)
			{
				return false;
			}
		}

		//	���łɓo�^����Ă�����j������
		if (_auto)
		{
			if (_pCommand)
			{
				delete _pCommand;
			}
		}

		//	�Ăяo�����I�u�W�F�N�g��j�����Ȃ��A�`��Ăяo���I�u�W�F�N�g�𐶐�
		_pCommand = new DrawFunction<false, T>(pObj, begin, end);

		return true;
	};

	//----------------------------------------------------------
	//	�`��̊e�Ăяo���I�u�W�F�N�g�A�Ȃ�тɔj���ӔC���Ϗ�����
	//
	// return: IDrawCommand* �c �`��̊e�Ăяo���I�u�W�F�N�g�ւ̃|�C���^
	//
	// memo: �`��̊e�Ăяo���I�u�W�F�N�g�́A�j����ۏႳ��Ȃ��Ȃ�̂ŁA
	//�@�@�@�K�� Release() ���\�b�h���A�Ϗ���Ŕj������悤�ɂ���
	//----------------------------------------------------------
	operator IDrawCommand* (void)
	{
		//	�f�X�g���N�^�ł̔j�����s��Ȃ�
		_auto = false;

		return _pCommand;
	};

	//----------------------------------------------------------
	//	�`��̊e�Ăяo���I�u�W�F�N�g��j������
	//----------------------------------------------------------
	void Release(void)
	{
		//	�܂��j������Ă��Ȃ�
		if (_pCommand)
		{
			delete _pCommand;
			_pCommand = NULL;
		}
	};
};

//	�`��̊e�Ăяo�����\�b�h�o�^���ɁA����������s��Ȃ� null ���w�肷��
#define DRAWDELEGATE_NULL(type) (void (type::*)(RenderStates*))0

};//namespace Renderable
};//namespace gift

#endif
