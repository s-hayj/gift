//----------------------------------------------------------
// file name: NewDelManager.h
//
// memo: �I�u�W�F�N�g�̏������Ɣj�����Ǘ�����
//----------------------------------------------------------

#ifndef	__NEW_DEL_MANAGER_H
#define	__NEW_DEL_MANAGER_H

#include <stdio.h>

namespace gift
{

//----------------------------------------------------------
// name: gift::NewDelManager
//
// attrib: final template class
//
// typename: T �c �������Ȃ�тɔj������I�u�W�F�N�g�̌^
//
// memo: �I�u�W�F�N�g�̏������Ɣj���������Ϗ����邽�߂̃N���X
//----------------------------------------------------------
template<class T>
class	NewDelManager
{
private:
	//----------------------------------------------------------
	// name: gift::NewDelManager::ICommand
	//
	// attrib: private nested template interface
	//
	// typename: I �c �������Ȃ�тɔj������I�u�W�F�N�g�̌^
	//
	// memo: �������������͔j�����\�b�h�����s���邽�߂̃C���^�[�t�F�[�X
	//----------------------------------------------------------
	template<class I>
	class	ICommand
	{
	public:
		virtual ~ICommand(void) {};

		//----------------------------------------------------------
		//	�������������͔j�����\�b�h�����s����
		//
		// parameter: (in)(out)I& value �c �������{���I�u�W�F�N�g�ւ̎Q��
		//
		// return: I& �c �������{���ꂽ�I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		virtual I& Execute(I& value) = 0;
	};


	//----------------------------------------------------------
	// name: gift::NewDelManager::FunctionObject
	//
	// attrib: private nested template sub class
	//
	// base: gift::NewDelManager::ICommand is template interface
	//
	// memo: ��Ɋ֐��I�u�W�F�N�g�̃����o�֐��i�[�p�N���X
	//----------------------------------------------------------
	template<class T, class U>
	class	FunctionObject
		: public NewDelManager::ICommand<T>
	{
	public:
		typedef typename T& (U::*Method)(T&);

	private:
		U		_obj;	//	�Ăяo���I�u�W�F�N�g
		Method	_fun;	//	�Ăяo�����\�b�h

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		// parameter: (in)Method fun �c �Ăяo���֐��I�u�W�F�N�g�̃��\�b�h
		//----------------------------------------------------------
		FunctionObject(Method fun)
			: _fun(fun)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//----------------------------------------------------------
		~FunctionObject(void)
		{
		};

		//----------------------------------------------------------
		//	�w�肳�ꂽ�I�u�W�F�N�g���Ăяo��
		//
		// parameter: (in)(out)T& value �c �������{���I�u�W�F�N�g�ւ̎Q��
		//
		// return: T& �c �������{���ꂽ�I�u�W�F�N�g�ւ̎Q��
		//
		// attrib: override
		//----------------------------------------------------------
		T& Execute(T& value)
		{
			return (_obj.*_fun)(value);
		};
	};


	//----------------------------------------------------------
	// name: gift::NewDelManager::Function
	//
	// attrib: private nested template sub class
	//
	// base: gift::NewDelManager::ICommand is template interface
	//
	// memo: �ÓI�Ȋ֐����i�[����N���X
	//----------------------------------------------------------
	template<class T>
	class	Function
		: public NewDelManager::ICommand<T>
	{
	public:
		typedef typename T& (*Method)(T&);

	private:
		Method _fun;	//	�Ăяo���֐�

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		// parameter: (in)Method fun �c �Ăяo���֐��|�C���^
		//----------------------------------------------------------
		Function(Method fun)
			: _fun(fun)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//----------------------------------------------------------
		~Function(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[���Ă���֐����Ăяo��
		//
		// parameter: (in)(out)T& value �c �������{���I�u�W�F�N�g�ւ̎Q��
		//
		// attrib: override
		//
		// return: T& �c �������{�����I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		T& Execute(T& value)
		{
			return (*_fun)(value);
		};
	};

	//----------------------------------------------------------
	// name: gift::NewDelManager::ObjectMethod
	//
	// attrib: private nested template sub class
	//
	// base: gift::NewDelManager::ICommand is template interface
	//
	// memo: �I�u�W�F�N�g�̃����o�֐����i�[����
	//�@�@�@�I�u�W�F�N�g�̓|�C���^�Ō��΂�Ă��邽�߁A
	//�@�@�@�Ăяo���O�ɔj�����Ȃ��悤�ɗ��ӂ���
	//----------------------------------------------------------
	template<class T, class U>
	class	ObjectMethod
		: public NewDelManager::ICommand<T>
	{
	public:
		typedef T& (U::*Method)(T&);

	private:
		U*		_pObj;	//	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
		Method	_fun;	//	�Ăяo�����\�b�h

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		// parameter: (in)U* pObj �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
		// parameter: (in)Method fun �c �Ăяo�������o�֐�
		//----------------------------------------------------------
		ObjectMethod(U* pObj, Method fun)
			: _pObj(pObj), _fun(fun)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//----------------------------------------------------------
		~ObjectMethod(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[�����o�֐����Ăяo��
		//
		// parameter: (in)(out)T& value �c �������{���I�u�W�F�N�g�ւ̎Q��
		//
		// return: T& �c �������{�����I�u�W�F�N�g�ւ̎Q��
		//
		// attrib: override
		//----------------------------------------------------------
		T& Execute(T& value)
		{
			return (_pObj->*_fun)(value);
		};
	};

private:
	ICommand<T>* _pNewCommand;	//	���������̌Ăяo���I�u�W�F�N�g
	ICommand<T>* _pDelCommand;	//	�j�����̌Ăяo���I�u�W�F�N�g

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)U& New �c �֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	// parameter: (in)T& (U::*NewFun)(T&) �c ���������ɌĂяo�������o�֐�
	// parameter: (in)I& Del �c �֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	// parameter: (in)T& (I::*DelFun)(T&) �c �j�����ɌĂяo�������o�֐�
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager(U& New, typename T& (U::*NewFun)(T&),
		I& Del, typename T& (I::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::FunctionObject<T, U>(NewFun);
		_pDelCommand = new NewDelManager::FunctionObject<T, I>(DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)U& New �c �֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	// parameter: (in)T& (U::*NewFun)(T&) �c ���������ɌĂяo�������o�֐�
	// parameter: (in)T& (*DelFun)(T&) �c �j�����ɌĂяo�����֐��ւ̃|�C���^
	//----------------------------------------------------------
	template<class U>
		NewDelManager(U& New, typename T& (U::*NewFun)(T&), T& (*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::FunctionObject<T, U>(NewFun);
		_pDelCommand = new NewDelManager::Function<T>(DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)U& New �c �֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	// parameter: (in)T& (U::*NewFun)(T&) �c ���������ɌĂяo�������o�֐�
	// parameter: (in)I* pDel �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)T& (I::*DelFun)(T&) �c �j�����ɌĂяo�������o�֐�
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager(U& New, typename T& (U::*NewFun)(T&),
		I* pDel, typename T& (I::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::FunctionObject<T, U>(NewFun);
		_pDelCommand = new NewDelManager::ObjectMethod<T, I>(pDel, DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)T& (*NewFun)(T&) �c ���������ɌĂяo���֐��ւ̃|�C���^
	// parameter: (in)T& (*DelFun)(T&) �c �j�����ɌĂяo���֐��ւ̃|�C���^
	//----------------------------------------------------------
	NewDelManager(T& (*NewFun)(T&), T& (*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::Function<T>(NewFun);
		_pDelCommand = new NewDelManager::Function<T>(DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)T& (*NewFun)(T&) �c ���������ɌĂяo���֐��ւ̃|�C���^
	// parameter: (in)U& Del �c �֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	// parameter: (in)T& (U::*DelFun)(T&) �c �j�����ɌĂяo�������o�֐�
	//----------------------------------------------------------
	template<class U>
		NewDelManager(T& (*NewFun)(T&), U& Del, typename T& (U::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::Function<T>(NewFun);
		_pDelCommand = new NewDelManager::FunctionObject<T, U>(DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)T& (*NewFun)(T&) �c ���������ɌĂяo���֐��ւ̃|�C���^
	// parameter: (in)U* pDel �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)T& (U::*DelFun)(T&) �c �j�����ɌĂяo�������o�֐�
	//----------------------------------------------------------
	template<class U>
		NewDelManager(T& (*NewFun)(T&), U* pDel, typename T& (U::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::Function<T>(NewFun);
		_pDelCommand = new NewDelManager::ObjectMethod<T, U>(pDel, DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)U* pNew �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)T& (U::*NewFun)(T&) �c ���������ɌĂяo�������o�֐�
	// parameter: (in)I* pDel �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)T& (I::*DelFun)(T&) �c �j�����ɌĂяo�������o�֐�
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager(U* pNew, typename T& (U::*NewFun)(T&),
		I* pDel, typename T& (I::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::ObjectMethod<T, U>(pNew, NewFun);
		_pDelCommand = new NewDelManager::ObjectMethod<T, I>(pDel, DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)U* pNew �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)T& (U::*NewFun)(T&) �c ���������ɌĂяo�������o�֐�
	// parameter: (in)I& Del �c �֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	// parameter: (in)T& (I::*DelFun)(T&) �c �j�����ɌĂяo�������o�֐�
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager(U* pNew, typename T& (U::*NewFun)(T&),
		I& Del, typename T& (I::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::ObjectMethod<T, U>(pNew, NewFun);
		_pDelCommand = new NewDelManager::FunctionObject<T, I>(DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)U* pNew �c �Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	// parameter: (in)T& (U::*NewFun)(T&) �c ���������ɌĂяo�������o�֐�
	// parameter: (in)T& (*DelFun)(T&) �c �j�����ɌĂяo���֐��ւ̃|�C���^
	//----------------------------------------------------------
	template<class U>
		NewDelManager(U* pNew, typename T& (U::*NewFun)(T&), T& (*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::ObjectMethod<T, U>(pNew, NewFun);
		_pDelCommand = new NewDelManager::Function<T>(DelFun);
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	NewDelManager(void)
		: _pNewCommand(NULL), _pDelCommand(NULL)
	{
	};

	//----------------------------------------------------------
	//	�R�s�[�R���X�g���N�^
	//
	// parameter: (in)NewDelManager<T>& obj �c �R�s�[���ւ̎Q��
	//
	// return: �R�s�[��A�R�s�[���͌Ăяo���I�u�W�F�N�g�𑀍�ł��Ȃ��Ȃ�
	//�@�@�@�@�R�s�[��́A�V���ɌĂяo���I�u�W�F�N�g�j���̐ӔC���Ϗ����ꂽ
	//----------------------------------------------------------
	NewDelManager(NewDelManager<T>& obj)
	{
		_pNewCommand = obj._pNewCommand;
		obj._pNewCommand = NULL;

		_pDelCommand = obj._pDelCommand;
		obj._pDelCommand = NULL;
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~NewDelManager(void)
	{
		//	�Ăяo���I�u�W�F�N�g��j������
		this->Destroy();
	};

	//----------------------------------------------------------
	//	������Z�q�̃I�[�o�[���[�h
	//
	// parameter: (in)NewDelManager<T>& obj �c �Ăяo�����\�b�h�̃R�s�[���ւ̎Q��
	//
	// memo: �R�s�[��A�R�s�[���͌Ăяo���I�u�W�F�N�g�𑀍�ł��Ȃ��Ȃ�
	//�@�@�@�R�s�[��́A�V���ɌĂяo���I�u�W�F�N�g�j���̐ӔC���Ϗ����ꂽ
	//----------------------------------------------------------
	void operator = (NewDelManager<T>& obj)
	{
		//	�Ăяo�����\�b�h��j������
		this->Destroy();

		_pNewCommand = obj._pNewCommand;
		obj._pNewCommand = NULL;

		_pDelCommand = obj._pDelCommand;
		obj._pDelCommand = NULL;
	};

	//----------------------------------------------------------
	//	���������ɓo�^�������\�b�h���Ăяo��
	//
	// parameter: (in)(out)T& value �c �������{���I�u�W�F�N�g�ւ̎Q��
	//
	// return: T& �c �������{�����I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	T& Initialize(T& value)
	{
		if (_pNewCommand)
		{
			return _pNewCommand->Execute(value);
		}

		return value;
	};

	//----------------------------------------------------------
	//	�j�����ɓo�^�������\�b�h���Ăяo��
	//
	// parameter: (in)(out)T& value �c �������{���I�u�W�F�N�g�ւ̎Q��
	//
	// return: T& �c �������{�����I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	T& Release(T& value)
	{
		if (_pDelCommand)
		{
			return _pDelCommand->Execute(value);
		}

		return value;
	};

private:
	//----------------------------------------------------------
	//	�e�������\�b�h�Ăяo���I�u�W�F�N�g�̔j��
	//----------------------------------------------------------
	void Destroy(void)
	{
		//	�������Ăяo���I�u�W�F�N�g���j������Ă��Ȃ�
		if (_pNewCommand)
		{
			delete _pNewCommand;
			_pNewCommand = NULL;
		}

		//	�j���Ăяo���I�u�W�F�N�g���j������Ă��Ȃ�
		if (_pDelCommand)
		{
			delete _pDelCommand;
			_pDelCommand = NULL;
		}
	};
};

};

#endif
