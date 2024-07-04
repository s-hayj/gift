//----------------------------------------------------------
//	@file	NewDelManager.h
//
//	@memo	�I�u�W�F�N�g�̏������Ɣj�����Ǘ�����
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__NEW_DEL_MANAGER_H
#define	__NEW_DEL_MANAGER_H

#include <stdio.h>


//----------------------------------------------------------
//	@name	NewDelManager
//
//	@memo	�I�u�W�F�N�g�̏������Ɣj���������Ϗ����邽�߂̃N���X
//
//	@attrib	public final template class
//
//	@type	T	�������Ȃ�тɔj������I�u�W�F�N�g�̌^
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
template<class T>
class	NewDelManager
{
private:
	//----------------------------------------------------------
	//	@name	NewDelManager::ICommand
	//
	//	@memo	�������������͔j�����\�b�h�����s���邽�߂̃C���^�[�t�F�[�X
	//
	//	@attrib	private nested template interface
	//
	//	@type	I	�������Ȃ�тɔj������I�u�W�F�N�g�̌^
	//
	//	@author	sano-y
	//	@data	2008-05-13
	//----------------------------------------------------------
	template<class I>
	class	ICommand
	{
	public:
		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	NewDelManager::ICommand::~ICommand
		//
		//	@attrib	public virtual
		//----------------------------------------------------------
		virtual ~ICommand(void) {};

		//----------------------------------------------------------
		//	�������������͔j�����\�b�h�����s����
		//
		//	@name	NewDelManager::ICommand::Execute
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	(in/out)value	�������{���I�u�W�F�N�g�ւ̎Q��
		//
		//	@return	I&	�������{���ꂽ�I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		virtual I& Execute( I& value ) = 0;
	};


	//----------------------------------------------------------
	//	@name	NewDelManager::FunctionObject
	//
	//	@memo	��Ɋ֐��I�u�W�F�N�g�̃����o�֐��i�[�p�N���X
	//
	//	@attrib	private nested template final sub class
	//
	//	@base	public NewDelManager::ICommand<T>
	//
	//	@type	T	�������Ȃ�тɔj������I�u�W�F�N�g�̌^
	//	@type	U	�o�^����֐��̃I�u�W�F�N�g�^
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template<class T, class U>
	class	FunctionObject
		: public NewDelManager::ICommand<T>
	{
	public:
		//	�֐��I�u�W�F�N�g�̊֐��|�C���^�^
		typedef typename T& (U::*Method)(T&);

	private:
		U		m_obj;	//	�Ăяo���I�u�W�F�N�g
		Method	m_fun;	//	�Ăяo�����\�b�h

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	NewDelManager::FunctionObject::FunctionObject
		//
		//	@attrib	public
		//
		//	@param	(in)fun	�Ăяo���֐��I�u�W�F�N�g�̃��\�b�h
		//----------------------------------------------------------
		FunctionObject( Method fun )
			: _fun( fun )
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	NewDelManager::FunctionObject::~FunctionObject
		//
		//	@attrib	public
		//----------------------------------------------------------
		~FunctionObject(void)
		{
		};

		//----------------------------------------------------------
		//	�w�肳�ꂽ�I�u�W�F�N�g���Ăяo��
		//
		//	@name	NewDelManager::FunctionObject::Execute
		//
		//	@memo
		//
		//	@attrib	public override
		//
		//	@base	NewDelManager::ICommand<T>::Execute
		//
		//	@param	(in/out)value	�������{���I�u�W�F�N�g�ւ̎Q��
		//
		//	@return	T&	�������{���ꂽ�I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		T& Execute( T& value )
		{
			return (_obj.*_fun)( value );
		};
	};


	//----------------------------------------------------------
	//	@name	NewDelManager::Function
	//
	//	@memo	�ÓI�Ȋ֐����i�[����N���X
	//
	//	@attrib	private nested template final sub class
	//
	//	@base	public NewDelManager::ICommand<T>
	//
	//	@type	T	�������Ȃ�тɔj������I�u�W�F�N�g�̌^
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template<class T>
	class	Function
		: public NewDelManager::ICommand<T>
	{
	public:
		//	�o�^����֐��|�C���^�^
		typedef typename T& (*Method)(T&);

	private:
		Method m_fun;	//	�Ăяo���֐�

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	NewDelManager::Function::Function
		//
		//	@attrib	public
		//
		//	@poaram	(in)fun	�Ăяo���ւ��|�C���^
		//----------------------------------------------------------
		Function( Method fun )
			: _fun(fun)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	NewDelManager::Function::~Function
		//
		//	@attrib	public
		//----------------------------------------------------------
		~Function(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[���Ă���֐����Ăяo��
		//
		//	@name	NewDelManager::Function::Execute
		//
		//	@memo
		//
		//	@attrib	public override
		//
		//	@base	NewDelManager::ICommand<T>::Execute
		//
		//	@param	(in/out)value	�������{���I�u�W�F�N�g�ւ̎Q��
		//
		//	@return	T&	�������{�����I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		T& Execute( T& value )
		{
			return (*_fun)( value );
		};
	};

	//----------------------------------------------------------
	//	@name	NewDelManager::ObjectMethod
	//
	//	@memo	�I�u�W�F�N�g�̃����o�֐����i�[����
	//
	//	@attrib	private nested template final sub class
	//
	//	@base	public NewDelManager::ICommnad<T>
	//
	//	@type	T	�������Ȃ�тɔj������I�u�W�F�N�g�̌^
	//	@type	U	�o�^���郁���o�֐��̃I�u�W�F�N�g�^
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template<class T, class U>
	class	ObjectMethod
		: public NewDelManager::ICommand<T>
	{
	public:
		//	�o�^����I�u�W�F�N�g�����o�֐��|�C���^�^
		typedef T& (U::*Method)(T&);

	private:
		U*		m_pObj;	//	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
		Method	m_fun;	//	�Ăяo�����\�b�h

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	NewDelManager::ObjectMethod::ObjectMethod
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	(in)pObj	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
		//	@param	(in)fun		�Ăяo�������o�֐�
		//----------------------------------------------------------
		ObjectMethod( U* pObj, Method fun )
			: m_pObj(pObj), m_fun(fun)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	NewDelManager::ObjectMethod::~ObjectMethod
		//
		//	@attrib	public
		//----------------------------------------------------------
		~ObjectMethod(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[�����o�֐����Ăяo��
		//
		//	@name	NewDelManager::ObjectMethod::Execute
		//
		//	@memo
		//
		//	@attrib	public override
		//
		//	@base	NewDelManager::ICommand<T>::Execute
		//
		//	@param	(in/out)value	�������{���I�u�W�F�N�g�ւ̎Q��
		//
		//	@return	T&	�������{�����I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		T& Execute( T& value )
		{
			return (_pObj->*_fun)( value );
		};
	};

private:
	ICommand<T>* m_pNewCommand;	//	���������̌Ăяo���I�u�W�F�N�g
	ICommand<T>* m_pDelCommand;	//	�j�����̌Ăяo���I�u�W�F�N�g

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	U	�o�^���鏉�����p�����o�֐��̃I�u�W�F�N�g�^
	//	@type	I	�o�^����j���p�����o�֐��̃I�u�W�F�N�g�^
	//
	//	@param	(in)New		�֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	//	@param	(in)NewFun	���������ɌĂяo�������o�֐�
	//	@param	(in)Del		�֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	//	@param	(in)DelFun	�j�����ɌĂяo�������o�֐�
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager( U& New, typename T& (U::*NewFun)(T&),
		I& Del, typename T& (I::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::FunctionObject<T, U>( NewFun );
		m_pDelCommand = new NewDelManager::FunctionObject<T, I>( DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	U	�o�^���鏉�����p�����o�֐��̃I�u�W�F�N�g�^
	//
	//	@param	(in)New		�֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	//	@param	(in)NewFun	���������ɌĂяo�������o�֐�
	//	@param	(in)DelFun	�j�����ɌĂяo�����֐��ւ̃|�C���^
	//----------------------------------------------------------
	template<class U>
		NewDelManager( U& New, typename T& (U::*NewFun)(T&), T& (*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::FunctionObject<T, U>( NewFun );
		m_pDelCommand = new NewDelManager::Function<T>( DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@author	public template
	//
	//	@type	U	�o�^���鏉�����p�����o�֐��̃I�u�W�F�N�g�^
	//	@type	I	�o�^����j���p�����o�֐��̃I�u�W�F�N�g�^
	//
	//	@param	(in)New		�֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	//	@param	(in)NewFun	���������ɌĂяo����郁���o�֐�
	//	@param	(in)pDel	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	//	@param	(in)DelFun	�j�����ɌĂяo����郁���o�֐�
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager( U& New, typename T& (U::*NewFun)(T&),
		I* pDel, typename T& (I::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::FunctionObject<T, U>( NewFun );
		m_pDelCommand = new NewDelManager::ObjectMethod<T, I>( pDel, DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public
	//
	//	@param	(in)NewFun	���������ɌĂяo�����֐��ւ̃|�C���^
	//	@param	(in)DelFun	�j�����ɌĂяo�����֐��ւ̃|�C���^
	//----------------------------------------------------------
	NewDelManager( T& (*NewFun)(T&), T& (*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::Function<T>( NewFun );
		m_pDelCommand = new NewDelManager::Function<T>( DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public template
	//
	//	@type	U	�o�^����j���p�����o�֐��̃I�u�W�F�N�g�^
	//
	//	@param	(in)NewFun	���������ɌĂяo�����֐��ւ̃|�C���^
	//	@param	(in)Del		�֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	//	@param	(in)DelFun	�j�����ɌĂяo����郁���o�֐�
	//----------------------------------------------------------
	template<class U>
		NewDelManager( T& (*NewFun)(T&), U& Del, typename T& (U::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::Function<T>( NewFun );
		m_pDelCommand = new NewDelManager::FunctionObject<T, U>( DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public template
	//
	//	@type	U	�o�^����j���p�����o�֐��̃I�u�W�F�N�g�^
	//
	//	@param	(in)NewFun	���������ɌĂяo�����֐��ւ̃|�C���^
	//	@param	(in)pDel	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	//	@param	(in)DelFun	�j�����ɌĂяo����郁���o�֐�
	//----------------------------------------------------------
	template<class U>
		NewDelManager( T& (*NewFun)(T&), U* pDel, typename T& (U::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::Function<T>( NewFun );
		m_pDelCommand = new NewDelManager::ObjectMethod<T, U>( pDel, DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public template
	//
	//	@type	U	�o�^���鏉�����p�����o�֐��̃I�u�W�F�N�g�^
	//	@type	I	�o�^����j���p�����o�֐��̃I�u�W�F�N�g�^
	//
	//	@param	(in)pNew	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	//	@param	(in)NewFun	���������ɌĂяo����郁���o�֐�
	//	@param	(in)pDel	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	//	@param	(int)DelFun	�j�����ɌĂяo����郁���o�֐�
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager( U* pNew, typename T& (U::*NewFun)(T&),
		I* pDel, typename T& (I::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::ObjectMethod<T, U>( pNew, NewFun );
		m_pDelCommand = new NewDelManager::ObjectMethod<T, I>( pDel, DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public template
	//
	//	@type	U	�o�^���鏉�����p�����o�֐��̃I�u�W�F�N�g�^
	//	@type	I	�o�^����j���p�����o�֐��̃I�u�W�F�N�g�^
	//
	//	@param	(in)pNew	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	//	@param	(in)NewFun	���������ɌĂяo�������o�֐�
	//	@param	(in)Del		�֐��I�u�W�F�N�g���ʂ̂��߂̌^�ւ̎Q��
	//	@param	(in)DelFun	�j�����ɌĂяo����郁���o�֐�
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager( U* pNew, typename T& (U::*NewFun)(T&),
		I& Del, typename T& (I::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::ObjectMethod<T, U>( pNew, NewFun );
		m_pDelCommand = new NewDelManager::FunctionObject<T, I>( DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@author	public template
	//
	//	@type	U	�������Ȃ�тɔj�����s���I�u�W�F�N�g�̌^
	//
	//	@param	(in)pNew	�Ăяo�����I�u�W�F�N�g�ւ̃|�C���^
	//	@param	(in)NewFun	���������ɌĂяo�������o�֐�
	//	@param	(in)DelFun	�j�����ɌĂяo�������o�֐��ւ̃|�C���^
	//----------------------------------------------------------
	template<class U>
		NewDelManager( U* pNew, typename T& (U::*NewFun)(T&), T& (*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::ObjectMethod<T, U>( pNew, NewFun );
		m_pDelCommand = new NewDelManager::Function<T>( DelFun );
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@author	public
	//
	//	@param	none
	//----------------------------------------------------------
	NewDelManager(void)
		: m_pNewCommand( NULL ), m_pDelCommand( NULL )
	{
	};

	//----------------------------------------------------------
	//	�R�s�[�R���X�g���N�^
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@memo	�I�u�W�F�N�g�̔j���ӔC��C�����B�R�s�[���͑��삪�s�\�ɂȂ�
	//
	//	@attrib	public
	//
	//	@param	(in)obj	�R�s�[���ւ̎Q��
	//----------------------------------------------------------
	NewDelManager( NewDelManager<T>& obj )
	{
		//	�I�u�W�F�N�g�̔j���ӔC���R�s�[��ֈڏ�����
		m_pNewCommand = obj.m_pNewCommand;
		m_pDelCommand = obj.m_pDelCommand;

		//	�R�s�[���̓I�u�W�F�N�g�̑��삪�s�\�ɂȂ�
		obj.m_pNewCommand = NULL;
		obj.m_pDelCommand = NULL;
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	NewDelManager::~NewDelManager
	//
	//	@attrib	public
	//----------------------------------------------------------
	~NewDelManager(void)
	{
		//	�Ăяo���I�u�W�F�N�g��j������
		this->Destroy();
	};

	//----------------------------------------------------------
	//	������Z�q�̃I�[�o�[���[�h
	//
	//	@name	NewDelManager::operator =
	//
	//	@memo	�Ăяo���I�u�W�F�N�g�̔j���ӔC��C�����B�R�s�[���͑��삪�s�\
	//
	//	@attrib	public
	//
	//	@param	(in)obj	�Ăяo�����\�b�h�̃R�s�[���ւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	void operator = ( NewDelManager<T>& obj )
	{
		//	�Ăяo�����\�b�h��j������
		this->Destroy();

		//	�I�u�W�F�N�g�̔j�����R�s�[��ֈϏ�����
		m_pNewCommand = obj.m_pNewCommand;
		m_pDelCommand = obj.m_pDelCommand;

		//	�R�s�[���̓I�u�W�F�N�g�̑��삪�s�\�ɂȂ�
		obj.m_pNewCommand = NULL;
		obj.m_pDelCommand = NULL;
	};

	//----------------------------------------------------------
	//	���������ɓo�^�������\�b�h���Ăяo��
	//
	//	@name	NewDelManager::Initialize
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in/out)value	�������{���I�u�W�F�N�g�ւ̎Q��
	//
	//	@return	T&	�������{�����I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	T& Initialize( T& value )
	{
		//	�������������\�b�h���o�^����Ă���
		if ( m_pNewCommand )
		{
			//	�o�^���ꂽ���\�b�h�ŏ��������������s
			return m_pNewCommand->Execute( value );
		}

		return value;
	};

	//----------------------------------------------------------
	//	�j�����ɓo�^�������\�b�h���Ăяo��
	//
	//	@name	NewDelManager::Release
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in/out)value	�������{���I�u�W�F�N�g�ւ̎Q��
	//
	//	@return	T&	�������{�����I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	T& Release( T& value )
	{
		//	�j���������\�b�h���o�^����Ă���
		if ( m_pDelCommand )
		{
			//	�o�^���ꂽ���\�b�h�Ŕj�����������s
			return m_pDelCommand->Execute( value );
		}

		return value;
	};

private:
	//----------------------------------------------------------
	//	�e�������\�b�h�Ăяo���I�u�W�F�N�g�̔j��
	//
	//	@name	NewDelManager::Destroy
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Destroy(void)
	{
		//	�������Ăяo���I�u�W�F�N�g���j������Ă��Ȃ�
		if ( m_pNewCommand )
		{
			delete m_pNewCommand;
			m_pNewCommand = NULL;
		}

		//	�j���Ăяo���I�u�W�F�N�g���j������Ă��Ȃ�
		if ( m_pDelCommand )
		{
			delete m_pDelCommand;
			m_pDelCommand = NULL;
		}
	};
};

#endif
