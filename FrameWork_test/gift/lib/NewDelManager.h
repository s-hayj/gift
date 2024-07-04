//----------------------------------------------------------
//	@file	NewDelManager.h
//
//	@memo	オブジェクトの初期化と破棄を管理する
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
//	@memo	オブジェクトの初期化と破棄処理を委譲するためのクラス
//
//	@attrib	public final template class
//
//	@type	T	初期化ならびに破棄するオブジェクトの型
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
	//	@memo	初期化もしくは破棄メソッドを実行するためのインターフェース
	//
	//	@attrib	private nested template interface
	//
	//	@type	I	初期化ならびに破棄するオブジェクトの型
	//
	//	@author	sano-y
	//	@data	2008-05-13
	//----------------------------------------------------------
	template<class I>
	class	ICommand
	{
	public:
		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	NewDelManager::ICommand::~ICommand
		//
		//	@attrib	public virtual
		//----------------------------------------------------------
		virtual ~ICommand(void) {};

		//----------------------------------------------------------
		//	初期化もしくは破棄メソッドを実行する
		//
		//	@name	NewDelManager::ICommand::Execute
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	(in/out)value	処理を施すオブジェクトへの参照
		//
		//	@return	I&	処理が施されたオブジェクトへの参照
		//----------------------------------------------------------
		virtual I& Execute( I& value ) = 0;
	};


	//----------------------------------------------------------
	//	@name	NewDelManager::FunctionObject
	//
	//	@memo	主に関数オブジェクトのメンバ関数格納用クラス
	//
	//	@attrib	private nested template final sub class
	//
	//	@base	public NewDelManager::ICommand<T>
	//
	//	@type	T	初期化ならびに破棄するオブジェクトの型
	//	@type	U	登録する関数のオブジェクト型
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template<class T, class U>
	class	FunctionObject
		: public NewDelManager::ICommand<T>
	{
	public:
		//	関数オブジェクトの関数ポインタ型
		typedef typename T& (U::*Method)(T&);

	private:
		U		m_obj;	//	呼び出すオブジェクト
		Method	m_fun;	//	呼び出すメソッド

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	NewDelManager::FunctionObject::FunctionObject
		//
		//	@attrib	public
		//
		//	@param	(in)fun	呼び出す関数オブジェクトのメソッド
		//----------------------------------------------------------
		FunctionObject( Method fun )
			: _fun( fun )
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	NewDelManager::FunctionObject::~FunctionObject
		//
		//	@attrib	public
		//----------------------------------------------------------
		~FunctionObject(void)
		{
		};

		//----------------------------------------------------------
		//	指定されたオブジェクトを呼び出す
		//
		//	@name	NewDelManager::FunctionObject::Execute
		//
		//	@memo
		//
		//	@attrib	public override
		//
		//	@base	NewDelManager::ICommand<T>::Execute
		//
		//	@param	(in/out)value	処理を施すオブジェクトへの参照
		//
		//	@return	T&	処理が施されたオブジェクトへの参照
		//----------------------------------------------------------
		T& Execute( T& value )
		{
			return (_obj.*_fun)( value );
		};
	};


	//----------------------------------------------------------
	//	@name	NewDelManager::Function
	//
	//	@memo	静的な関数を格納するクラス
	//
	//	@attrib	private nested template final sub class
	//
	//	@base	public NewDelManager::ICommand<T>
	//
	//	@type	T	初期化ならびに破棄するオブジェクトの型
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template<class T>
	class	Function
		: public NewDelManager::ICommand<T>
	{
	public:
		//	登録する関数ポインタ型
		typedef typename T& (*Method)(T&);

	private:
		Method m_fun;	//	呼び出す関数

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	NewDelManager::Function::Function
		//
		//	@attrib	public
		//
		//	@poaram	(in)fun	呼び出す関すポインタ
		//----------------------------------------------------------
		Function( Method fun )
			: _fun(fun)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	NewDelManager::Function::~Function
		//
		//	@attrib	public
		//----------------------------------------------------------
		~Function(void)
		{
		};

		//----------------------------------------------------------
		//	格納している関数を呼び出す
		//
		//	@name	NewDelManager::Function::Execute
		//
		//	@memo
		//
		//	@attrib	public override
		//
		//	@base	NewDelManager::ICommand<T>::Execute
		//
		//	@param	(in/out)value	処理を施すオブジェクトへの参照
		//
		//	@return	T&	処理を施したオブジェクトへの参照
		//----------------------------------------------------------
		T& Execute( T& value )
		{
			return (*_fun)( value );
		};
	};

	//----------------------------------------------------------
	//	@name	NewDelManager::ObjectMethod
	//
	//	@memo	オブジェクトのメンバ関数を格納する
	//
	//	@attrib	private nested template final sub class
	//
	//	@base	public NewDelManager::ICommnad<T>
	//
	//	@type	T	初期化ならびに破棄するオブジェクトの型
	//	@type	U	登録するメンバ関数のオブジェクト型
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template<class T, class U>
	class	ObjectMethod
		: public NewDelManager::ICommand<T>
	{
	public:
		//	登録するオブジェクトメンバ関数ポインタ型
		typedef T& (U::*Method)(T&);

	private:
		U*		m_pObj;	//	呼び出し元オブジェクトへのポインタ
		Method	m_fun;	//	呼び出しメソッド

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	NewDelManager::ObjectMethod::ObjectMethod
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	(in)pObj	呼び出す元オブジェクトへのポインタ
		//	@param	(in)fun		呼び出すメンバ関数
		//----------------------------------------------------------
		ObjectMethod( U* pObj, Method fun )
			: m_pObj(pObj), m_fun(fun)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	NewDelManager::ObjectMethod::~ObjectMethod
		//
		//	@attrib	public
		//----------------------------------------------------------
		~ObjectMethod(void)
		{
		};

		//----------------------------------------------------------
		//	格納メンバ関数を呼び出す
		//
		//	@name	NewDelManager::ObjectMethod::Execute
		//
		//	@memo
		//
		//	@attrib	public override
		//
		//	@base	NewDelManager::ICommand<T>::Execute
		//
		//	@param	(in/out)value	処理を施すオブジェクトへの参照
		//
		//	@return	T&	処理を施したオブジェクトへの参照
		//----------------------------------------------------------
		T& Execute( T& value )
		{
			return (_pObj->*_fun)( value );
		};
	};

private:
	ICommand<T>* m_pNewCommand;	//	初期化時の呼び出しオブジェクト
	ICommand<T>* m_pDelCommand;	//	破棄時の呼び出しオブジェクト

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	U	登録する初期化用メンバ関数のオブジェクト型
	//	@type	I	登録する破棄用メンバ関数のオブジェクト型
	//
	//	@param	(in)New		関数オブジェクト識別のための型への参照
	//	@param	(in)NewFun	初期化時に呼び出すメンバ関数
	//	@param	(in)Del		関数オブジェクト識別のための型への参照
	//	@param	(in)DelFun	破棄時に呼び出すメンバ関数
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager( U& New, typename T& (U::*NewFun)(T&),
		I& Del, typename T& (I::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::FunctionObject<T, U>( NewFun );
		m_pDelCommand = new NewDelManager::FunctionObject<T, I>( DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	U	登録する初期化用メンバ関数のオブジェクト型
	//
	//	@param	(in)New		関数オブジェクト識別のための型への参照
	//	@param	(in)NewFun	初期化時に呼び出すメンバ関数
	//	@param	(in)DelFun	破棄時に呼び出される関数へのポインタ
	//----------------------------------------------------------
	template<class U>
		NewDelManager( U& New, typename T& (U::*NewFun)(T&), T& (*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::FunctionObject<T, U>( NewFun );
		m_pDelCommand = new NewDelManager::Function<T>( DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@author	public template
	//
	//	@type	U	登録する初期化用メンバ関数のオブジェクト型
	//	@type	I	登録する破棄用メンバ関数のオブジェクト型
	//
	//	@param	(in)New		関数オブジェクト識別のための型への参照
	//	@param	(in)NewFun	初期化時に呼び出されるメンバ関数
	//	@param	(in)pDel	呼び出し元オブジェクトへのポインタ
	//	@param	(in)DelFun	破棄時に呼び出されるメンバ関数
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager( U& New, typename T& (U::*NewFun)(T&),
		I* pDel, typename T& (I::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::FunctionObject<T, U>( NewFun );
		m_pDelCommand = new NewDelManager::ObjectMethod<T, I>( pDel, DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public
	//
	//	@param	(in)NewFun	初期化時に呼び出される関数へのポインタ
	//	@param	(in)DelFun	破棄時に呼び出される関数へのポインタ
	//----------------------------------------------------------
	NewDelManager( T& (*NewFun)(T&), T& (*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::Function<T>( NewFun );
		m_pDelCommand = new NewDelManager::Function<T>( DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public template
	//
	//	@type	U	登録する破棄用メンバ関数のオブジェクト型
	//
	//	@param	(in)NewFun	初期化時に呼び出される関数へのポインタ
	//	@param	(in)Del		関数オブジェクト識別のための型への参照
	//	@param	(in)DelFun	破棄時に呼び出されるメンバ関数
	//----------------------------------------------------------
	template<class U>
		NewDelManager( T& (*NewFun)(T&), U& Del, typename T& (U::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::Function<T>( NewFun );
		m_pDelCommand = new NewDelManager::FunctionObject<T, U>( DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public template
	//
	//	@type	U	登録する破棄用メンバ関数のオブジェクト型
	//
	//	@param	(in)NewFun	初期化時に呼び出される関数へのポインタ
	//	@param	(in)pDel	呼び出し元オブジェクトへのポインタ
	//	@param	(in)DelFun	破棄時に呼び出されるメンバ関数
	//----------------------------------------------------------
	template<class U>
		NewDelManager( T& (*NewFun)(T&), U* pDel, typename T& (U::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::Function<T>( NewFun );
		m_pDelCommand = new NewDelManager::ObjectMethod<T, U>( pDel, DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public template
	//
	//	@type	U	登録する初期化用メンバ関数のオブジェクト型
	//	@type	I	登録する破棄用メンバ関数のオブジェクト型
	//
	//	@param	(in)pNew	呼び出し元オブジェクトへのポインタ
	//	@param	(in)NewFun	初期化時に呼び出されるメンバ関数
	//	@param	(in)pDel	呼び出し元オブジェクトへのポインタ
	//	@param	(int)DelFun	破棄時に呼び出されるメンバ関数
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager( U* pNew, typename T& (U::*NewFun)(T&),
		I* pDel, typename T& (I::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::ObjectMethod<T, U>( pNew, NewFun );
		m_pDelCommand = new NewDelManager::ObjectMethod<T, I>( pDel, DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@attrib	public template
	//
	//	@type	U	登録する初期化用メンバ関数のオブジェクト型
	//	@type	I	登録する破棄用メンバ関数のオブジェクト型
	//
	//	@param	(in)pNew	呼び出し元オブジェクトへのポインタ
	//	@param	(in)NewFun	初期化時に呼び出すメンバ関数
	//	@param	(in)Del		関数オブジェクト識別のための型への参照
	//	@param	(in)DelFun	破棄時に呼び出されるメンバ関数
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager( U* pNew, typename T& (U::*NewFun)(T&),
		I& Del, typename T& (I::*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::ObjectMethod<T, U>( pNew, NewFun );
		m_pDelCommand = new NewDelManager::FunctionObject<T, I>( DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@author	public template
	//
	//	@type	U	初期化ならびに破棄を行うオブジェクトの型
	//
	//	@param	(in)pNew	呼び出し元オブジェクトへのポインタ
	//	@param	(in)NewFun	初期化時に呼び出すメンバ関数
	//	@param	(in)DelFun	破棄時に呼び出すメンバ関数へのポインタ
	//----------------------------------------------------------
	template<class U>
		NewDelManager( U* pNew, typename T& (U::*NewFun)(T&), T& (*DelFun)(T&) )
	{
		m_pNewCommand = new NewDelManager::ObjectMethod<T, U>( pNew, NewFun );
		m_pDelCommand = new NewDelManager::Function<T>( DelFun );
	};

	//----------------------------------------------------------
	//	コンストラクタ
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
	//	コピーコンストラクタ
	//
	//	@name	NewDelManager::NewDelManager
	//
	//	@memo	オブジェクトの破棄責任を任される。コピー元は操作が不可能になる
	//
	//	@attrib	public
	//
	//	@param	(in)obj	コピー元への参照
	//----------------------------------------------------------
	NewDelManager( NewDelManager<T>& obj )
	{
		//	オブジェクトの破棄責任をコピー先へ移譲する
		m_pNewCommand = obj.m_pNewCommand;
		m_pDelCommand = obj.m_pDelCommand;

		//	コピー元はオブジェクトの操作が不可能になる
		obj.m_pNewCommand = NULL;
		obj.m_pDelCommand = NULL;
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	NewDelManager::~NewDelManager
	//
	//	@attrib	public
	//----------------------------------------------------------
	~NewDelManager(void)
	{
		//	呼び出しオブジェクトを破棄する
		this->Destroy();
	};

	//----------------------------------------------------------
	//	代入演算子のオーバーロード
	//
	//	@name	NewDelManager::operator =
	//
	//	@memo	呼び出しオブジェクトの破棄責任を任される。コピー元は操作が不可能
	//
	//	@attrib	public
	//
	//	@param	(in)obj	呼び出しメソッドのコピー元への参照
	//
	//	@return	none
	//----------------------------------------------------------
	void operator = ( NewDelManager<T>& obj )
	{
		//	呼び出しメソッドを破棄する
		this->Destroy();

		//	オブジェクトの破棄をコピー先へ委譲する
		m_pNewCommand = obj.m_pNewCommand;
		m_pDelCommand = obj.m_pDelCommand;

		//	コピー元はオブジェクトの操作が不可能になる
		obj.m_pNewCommand = NULL;
		obj.m_pDelCommand = NULL;
	};

	//----------------------------------------------------------
	//	初期化時に登録したメソッドを呼び出す
	//
	//	@name	NewDelManager::Initialize
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in/out)value	処理を施すオブジェクトへの参照
	//
	//	@return	T&	処理を施したオブジェクトへの参照
	//----------------------------------------------------------
	T& Initialize( T& value )
	{
		//	初期化処理メソッドが登録されている
		if ( m_pNewCommand )
		{
			//	登録されたメソッドで初期化処理を実行
			return m_pNewCommand->Execute( value );
		}

		return value;
	};

	//----------------------------------------------------------
	//	破棄時に登録したメソッドを呼び出す
	//
	//	@name	NewDelManager::Release
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in/out)value	処理を施すオブジェクトへの参照
	//
	//	@return	T&	処理を施したオブジェクトへの参照
	//----------------------------------------------------------
	T& Release( T& value )
	{
		//	破棄処理メソッドが登録されている
		if ( m_pDelCommand )
		{
			//	登録されたメソッドで破棄処理を実行
			return m_pDelCommand->Execute( value );
		}

		return value;
	};

private:
	//----------------------------------------------------------
	//	各処理メソッド呼び出しオブジェクトの破棄
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
		//	初期化呼び出しオブジェクトが破棄されていない
		if ( m_pNewCommand )
		{
			delete m_pNewCommand;
			m_pNewCommand = NULL;
		}

		//	破棄呼び出しオブジェクトが破棄されていない
		if ( m_pDelCommand )
		{
			delete m_pDelCommand;
			m_pDelCommand = NULL;
		}
	};
};

#endif
