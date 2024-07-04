//----------------------------------------------------------
// file name: NewDelManager.h
//
// memo: オブジェクトの初期化と破棄を管理する
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
// typename: T … 初期化ならびに破棄するオブジェクトの型
//
// memo: オブジェクトの初期化と破棄処理を委譲するためのクラス
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
	// typename: I … 初期化ならびに破棄するオブジェクトの型
	//
	// memo: 初期化もしくは破棄メソッドを実行するためのインターフェース
	//----------------------------------------------------------
	template<class I>
	class	ICommand
	{
	public:
		virtual ~ICommand(void) {};

		//----------------------------------------------------------
		//	初期化もしくは破棄メソッドを実行する
		//
		// parameter: (in)(out)I& value … 処理を施すオブジェクトへの参照
		//
		// return: I& … 処理が施されたオブジェクトへの参照
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
	// memo: 主に関数オブジェクトのメンバ関数格納用クラス
	//----------------------------------------------------------
	template<class T, class U>
	class	FunctionObject
		: public NewDelManager::ICommand<T>
	{
	public:
		typedef typename T& (U::*Method)(T&);

	private:
		U		_obj;	//	呼び出すオブジェクト
		Method	_fun;	//	呼び出すメソッド

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		// parameter: (in)Method fun … 呼び出す関数オブジェクトのメソッド
		//----------------------------------------------------------
		FunctionObject(Method fun)
			: _fun(fun)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//----------------------------------------------------------
		~FunctionObject(void)
		{
		};

		//----------------------------------------------------------
		//	指定されたオブジェクトを呼び出す
		//
		// parameter: (in)(out)T& value … 処理を施すオブジェクトへの参照
		//
		// return: T& … 処理が施されたオブジェクトへの参照
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
	// memo: 静的な関数を格納するクラス
	//----------------------------------------------------------
	template<class T>
	class	Function
		: public NewDelManager::ICommand<T>
	{
	public:
		typedef typename T& (*Method)(T&);

	private:
		Method _fun;	//	呼び出す関数

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		// parameter: (in)Method fun … 呼び出す関数ポインタ
		//----------------------------------------------------------
		Function(Method fun)
			: _fun(fun)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//----------------------------------------------------------
		~Function(void)
		{
		};

		//----------------------------------------------------------
		//	格納している関数を呼び出す
		//
		// parameter: (in)(out)T& value … 処理を施すオブジェクトへの参照
		//
		// attrib: override
		//
		// return: T& … 処理を施したオブジェクトへの参照
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
	// memo: オブジェクトのメンバ関数を格納する
	//　　　オブジェクトはポインタで結ばれているため、
	//　　　呼び出す前に破棄しないように留意する
	//----------------------------------------------------------
	template<class T, class U>
	class	ObjectMethod
		: public NewDelManager::ICommand<T>
	{
	public:
		typedef T& (U::*Method)(T&);

	private:
		U*		_pObj;	//	呼び出し元オブジェクトへのポインタ
		Method	_fun;	//	呼び出しメソッド

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		// parameter: (in)U* pObj … 呼び出し元オブジェクトへのポインタ
		// parameter: (in)Method fun … 呼び出すメンバ関数
		//----------------------------------------------------------
		ObjectMethod(U* pObj, Method fun)
			: _pObj(pObj), _fun(fun)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//----------------------------------------------------------
		~ObjectMethod(void)
		{
		};

		//----------------------------------------------------------
		//	格納メンバ関数を呼び出す
		//
		// parameter: (in)(out)T& value … 処理を施すオブジェクトへの参照
		//
		// return: T& … 処理を施したオブジェクトへの参照
		//
		// attrib: override
		//----------------------------------------------------------
		T& Execute(T& value)
		{
			return (_pObj->*_fun)(value);
		};
	};

private:
	ICommand<T>* _pNewCommand;	//	初期化時の呼び出しオブジェクト
	ICommand<T>* _pDelCommand;	//	破棄時の呼び出しオブジェクト

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)U& New … 関数オブジェクト識別のための型への参照
	// parameter: (in)T& (U::*NewFun)(T&) … 初期化時に呼び出すメンバ関数
	// parameter: (in)I& Del … 関数オブジェクト識別のための型への参照
	// parameter: (in)T& (I::*DelFun)(T&) … 破棄時に呼び出すメンバ関数
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager(U& New, typename T& (U::*NewFun)(T&),
		I& Del, typename T& (I::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::FunctionObject<T, U>(NewFun);
		_pDelCommand = new NewDelManager::FunctionObject<T, I>(DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)U& New … 関数オブジェクト識別のための型への参照
	// parameter: (in)T& (U::*NewFun)(T&) … 初期化時に呼び出すメンバ関数
	// parameter: (in)T& (*DelFun)(T&) … 破棄時に呼び出される関数へのポインタ
	//----------------------------------------------------------
	template<class U>
		NewDelManager(U& New, typename T& (U::*NewFun)(T&), T& (*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::FunctionObject<T, U>(NewFun);
		_pDelCommand = new NewDelManager::Function<T>(DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)U& New … 関数オブジェクト識別のための型への参照
	// parameter: (in)T& (U::*NewFun)(T&) … 初期化時に呼び出すメンバ関数
	// parameter: (in)I* pDel … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)T& (I::*DelFun)(T&) … 破棄時に呼び出すメンバ関数
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager(U& New, typename T& (U::*NewFun)(T&),
		I* pDel, typename T& (I::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::FunctionObject<T, U>(NewFun);
		_pDelCommand = new NewDelManager::ObjectMethod<T, I>(pDel, DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)T& (*NewFun)(T&) … 初期化時に呼び出す関数へのポインタ
	// parameter: (in)T& (*DelFun)(T&) … 破棄時に呼び出す関数へのポインタ
	//----------------------------------------------------------
	NewDelManager(T& (*NewFun)(T&), T& (*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::Function<T>(NewFun);
		_pDelCommand = new NewDelManager::Function<T>(DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)T& (*NewFun)(T&) … 初期化時に呼び出す関数へのポインタ
	// parameter: (in)U& Del … 関数オブジェクト識別のための型への参照
	// parameter: (in)T& (U::*DelFun)(T&) … 破棄時に呼び出すメンバ関数
	//----------------------------------------------------------
	template<class U>
		NewDelManager(T& (*NewFun)(T&), U& Del, typename T& (U::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::Function<T>(NewFun);
		_pDelCommand = new NewDelManager::FunctionObject<T, U>(DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)T& (*NewFun)(T&) … 初期化時に呼び出す関数へのポインタ
	// parameter: (in)U* pDel … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)T& (U::*DelFun)(T&) … 破棄時に呼び出すメンバ関数
	//----------------------------------------------------------
	template<class U>
		NewDelManager(T& (*NewFun)(T&), U* pDel, typename T& (U::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::Function<T>(NewFun);
		_pDelCommand = new NewDelManager::ObjectMethod<T, U>(pDel, DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)U* pNew … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)T& (U::*NewFun)(T&) … 初期化時に呼び出すメンバ関数
	// parameter: (in)I* pDel … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)T& (I::*DelFun)(T&) … 破棄時に呼び出すメンバ関数
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager(U* pNew, typename T& (U::*NewFun)(T&),
		I* pDel, typename T& (I::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::ObjectMethod<T, U>(pNew, NewFun);
		_pDelCommand = new NewDelManager::ObjectMethod<T, I>(pDel, DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)U* pNew … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)T& (U::*NewFun)(T&) … 初期化時に呼び出すメンバ関数
	// parameter: (in)I& Del … 関数オブジェクト識別のための型への参照
	// parameter: (in)T& (I::*DelFun)(T&) … 破棄時に呼び出すメンバ関数
	//----------------------------------------------------------
	template<class U, class I>
		NewDelManager(U* pNew, typename T& (U::*NewFun)(T&),
		I& Del, typename T& (I::*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::ObjectMethod<T, U>(pNew, NewFun);
		_pDelCommand = new NewDelManager::FunctionObject<T, I>(DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)U* pNew … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)T& (U::*NewFun)(T&) … 初期化時に呼び出すメンバ関数
	// parameter: (in)T& (*DelFun)(T&) … 破棄時に呼び出す関数へのポインタ
	//----------------------------------------------------------
	template<class U>
		NewDelManager(U* pNew, typename T& (U::*NewFun)(T&), T& (*DelFun)(T&))
	{
		_pNewCommand = new NewDelManager::ObjectMethod<T, U>(pNew, NewFun);
		_pDelCommand = new NewDelManager::Function<T>(DelFun);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	NewDelManager(void)
		: _pNewCommand(NULL), _pDelCommand(NULL)
	{
	};

	//----------------------------------------------------------
	//	コピーコンストラクタ
	//
	// parameter: (in)NewDelManager<T>& obj … コピー元への参照
	//
	// return: コピー後、コピー元は呼び出しオブジェクトを操作できなくなる
	//　　　　コピー先は、新たに呼び出しオブジェクト破棄の責任を委譲された
	//----------------------------------------------------------
	NewDelManager(NewDelManager<T>& obj)
	{
		_pNewCommand = obj._pNewCommand;
		obj._pNewCommand = NULL;

		_pDelCommand = obj._pDelCommand;
		obj._pDelCommand = NULL;
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~NewDelManager(void)
	{
		//	呼び出しオブジェクトを破棄する
		this->Destroy();
	};

	//----------------------------------------------------------
	//	代入演算子のオーバーロード
	//
	// parameter: (in)NewDelManager<T>& obj … 呼び出しメソッドのコピー元への参照
	//
	// memo: コピー後、コピー元は呼び出しオブジェクトを操作できなくなる
	//　　　コピー先は、新たに呼び出しオブジェクト破棄の責任を委譲された
	//----------------------------------------------------------
	void operator = (NewDelManager<T>& obj)
	{
		//	呼び出しメソッドを破棄する
		this->Destroy();

		_pNewCommand = obj._pNewCommand;
		obj._pNewCommand = NULL;

		_pDelCommand = obj._pDelCommand;
		obj._pDelCommand = NULL;
	};

	//----------------------------------------------------------
	//	初期化時に登録したメソッドを呼び出す
	//
	// parameter: (in)(out)T& value … 処理を施すオブジェクトへの参照
	//
	// return: T& … 処理を施したオブジェクトへの参照
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
	//	破棄時に登録したメソッドを呼び出す
	//
	// parameter: (in)(out)T& value … 処理を施すオブジェクトへの参照
	//
	// return: T& … 処理を施したオブジェクトへの参照
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
	//	各処理メソッド呼び出しオブジェクトの破棄
	//----------------------------------------------------------
	void Destroy(void)
	{
		//	初期化呼び出しオブジェクトが破棄されていない
		if (_pNewCommand)
		{
			delete _pNewCommand;
			_pNewCommand = NULL;
		}

		//	破棄呼び出しオブジェクトが破棄されていない
		if (_pDelCommand)
		{
			delete _pDelCommand;
			_pDelCommand = NULL;
		}
	};
};

};

#endif
