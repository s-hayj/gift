//----------------------------------------------------------
// file name: DrawDelegate.h
//
// memo: 描画メソッドを委譲するための、各インターフェースとクラス
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
// memo: 描画時の各呼び出し代行人
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
	// typename: bool … true のとき、格納オブジェクトの破棄機能を追加する
	// typename: T … 呼び出し元の型
	//
	// memo: 描画の各呼び出しメソッドを格納、実行する
	//　　　格納オブジェクトの破棄方法を登録し、それを破棄する
	//----------------------------------------------------------
	template<bool isDisposable, class T>
	class DrawFunction
		: public IDrawCommand
	{
	public:
		//	格納するメンバ関数の型
		typedef typename void (T::*Method)(RenderStates* pStates);

	private:
		T*			_pObj;		//	呼び出し元へのポインタ
		Method		_begin;		//	描画開始時のメソッド
		Method		_end;		//	描画の後処理メソッド
		ICommand*	_pReleaser;	//	格納オブジェクトの破棄方法

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		// parameter: (in)T* pObj … 呼び出し元へのポインタ
		// parameter: (in)Method begin … 描画開始時のメソッド
		// parameter: (in)Method end … 描画の後処理メソッド
		// parameter: (in)ICommand* pReleaser … 格納オブジェクトの破棄方法
		//----------------------------------------------------------
		DrawFunction(T* pObj, Method begin, Method end, ICommand* pReleaser)
			: _pObj(pObj), _begin(begin), _end(end), _pReleaser(pReleaser)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//----------------------------------------------------------
		~DrawFunction(void)
		{
			_pObj = NULL;

			//	破棄方法が登録されている
			if (_pReleaser)
			{
				delete _pReleaser;
				_pReleaser = NULL;
			}
		};

		//----------------------------------------------------------
		//	描画開始時のメソッドを呼び出す
		//
		// parameter: (in)RenderStates* pStates … レンダーステート
		//
		// attrib: override
		//----------------------------------------------------------
		void DrawBegin(RenderStates* pStates)
		{
			//	描画開始メソッドが登録されている
			if (_begin)
			{
				(_pObj->*_begin)(pStates);
			}
		};

		//----------------------------------------------------------
		//	描画の後処理メソッドを呼び出す
		//
		// parameter: (in)RenderStates* pStates … レンダーステート
		//
		// attrib: override
		//----------------------------------------------------------
		void DrawEnd(RenderStates* pStates)
		{
			//	後処理メソッドが登録されている
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
	// typename: T … 呼び出し元オブジェクトの型
	//
	// memo: 描画の各呼び出しメソッドを格納、実行する
	//----------------------------------------------------------
	template<class T>
	class DrawFunction<false, T>
		: public IDrawCommand
	{
	public:
		//	格納するメンバ関数の型
		typedef typename void (T::*Method)(RenderStates* pStates);

	private:
		T*		_pObj;	//	呼び出し元へのポインタ
		Method	_begin;	//	描画開始時のメソッド
		Method	_end;	//	描画の後処理メソッド

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		// parameter: (in)T* pObj … 呼び出し元へのポインタ
		// parameter: (in)Method begin … 描画開始時のメソッド
		// parameter: (in)Method end … 描画の後処理メソッド
		//----------------------------------------------------------
		DrawFunction(T* pObj, Method begin, Method end = 0)
			: _pObj(pObj), _begin(begin), _end(end)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//----------------------------------------------------------
		~DrawFunction(void)
		{
		};

		//----------------------------------------------------------
		//	描画開始時のメソッドを呼び出す
		//
		// parameter: (in)RenderStates* pStates … レンダーステート
		//
		// attrib: override
		//----------------------------------------------------------
		void DrawBegin(RenderStates* pStates)
		{
			//	描画開始メソッドが登録されている
			if (_begin)
			{
				(_pObj->*_begin)(pStates);
			}
		};

		//----------------------------------------------------------
		//	描画の後処理メソッドを呼び出す
		//
		// parameter: (in)RenderStates* pStates … レンダーステート
		//
		// attrib: override
		//----------------------------------------------------------
		void DrawEnd(RenderStates* pStates)
		{
			//	メソッドが登録されている
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
	// typename: T … 格納する呼び出し元オブジェクトの型
	//
	// memo: 登録メソッドを null で初期化するためのオブジェクト
	//----------------------------------------------------------
	template<class T>
	struct Null
	{
		//	格納するメンバ関数の型
		typedef typename void (T::*Method)(RenderStates*);

		//----------------------------------------------------------
		//	& 演算子オーバーロード
		//
		// return: void (T::*)(RenderStates*) … null を返す
		//----------------------------------------------------------
		Method operator & (void)
		{
			return 0;
		};
	};

private:
	bool			_auto;		//	オブジェクト破棄責任の有無
	IDrawCommand*	_pCommand;	//	各描画メソッド呼び出しオブジェクト

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	DrawDelegate(void)
		: _auto(true), _pCommand(NULL)
	{
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)T& obj … 呼び出し元オブジェクトへの参照
	// parameter: (in)void (T::*begin)(RenderStates*) … 描画開始メソッド
	// parameter: (in)void (T::*end)(RenderStates*) … 描画の後処理メソッド
	//----------------------------------------------------------
	template<class T>
		DrawDelegate(T& obj, typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*))
			: _auto(true)
	{
		//	呼び出し元オブジェクトを破棄しない、描画呼び出しオブジェクトの作成
		_pCommand = new DrawFunction<false, T>(&obj, begin, end);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)T* pObj … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)void (T::*begin)(RenderStates*) … 描画開始メソッド
	// parameter: (in)void (T::*end)(RenderStates*) … 描画の後処理メソッド
	// parameter: (in)ICommand* pDeleteHelper … 破棄方法へのポインタ
	//----------------------------------------------------------
	template<class T>
		DrawDelegate(T* pObj, typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*), ICommand* pDeleteHelper)
			: _auto(true)
	{
		//	呼び出し元オブジェクトを破棄する、描画呼び出しオブジェクトを作成
		_pCommand =
			new DrawFunction<true, T>(pObj, begin, end, pDeleteHelper);
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)T* pObj … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)void (T::*begin)(RenderStates*) … 描画開始メソッド
	// parameter: (in)void (T::*end)(RenderStates*) … 描画の後処理メソッド
	//----------------------------------------------------------
	template<class T>
		DrawDelegate(T* pObj, typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*))
			: _auto(true)
	{
		//	呼び出し元オブジェクトを破棄しない、描画呼び出しオブジェクトを作成
		_pCommand =
			new DrawFunction<false, T>(pObj, begin, end);
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~DrawDelegate(void)
	{
		//	オブジェクトの破棄責任を持っている
		if (_auto)
		{
			this->Release();
		}
	};

	//----------------------------------------------------------
	//	描画の各呼び出しメソッドを登録する
	//
	// parameter: (in)WriteMode::MODE mode … 登録オプション
	// parameter: (in)T& obj … 呼び出し元オブジェクトへの参照
	// parameter: (in)void (T::*begin)(RenderStates*) … 描画開始メソッド
	// parameter: (in)void (T::*end)(RenderStates*) … 描画の後処理メソッド
	//
	// return: bool … 登録処理結果
	//			true… 登録成功（以前の登録情報は破棄される）
	//			false…登録失敗（上書きが禁止状態で、すでに登録が完了している）
	//----------------------------------------------------------
	template<class T>
		bool Register(WriteMode::MODE mode, T& obj,
			typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*))
	{
		//	一度だけの登録
		if (mode == WriteMode::Once)
		{
			//	すでに登録されている
			if (_pCommand)
			{
				return false;
			}
		}

		//	すでに登録されていたら破棄
		if (_auto)
		{
			if (_pCommand)
			{
				delete _pCommand;
			}
		}

		//	呼び出し元オブジェクトを破棄しない、描画呼び出しオブジェクトを生成
		_pCommand = new DrawFunction<false, T>(&obj, begin, end);

		return true;
	};

	//----------------------------------------------------------
	//	描画の各呼び出しメソッドを、格納オブジェクトの破棄方法と共に登録する
	//
	// parameter: (in)WriteMode::MODE mode … 登録オプション
	// parameter: (in)T* pObj … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)void (T::*begin)(RenderStates*) … 描画開始メソッド
	// parameter: (in)void (T::*end)(RenderStates*) … 描画の後処理メソッド
	// parameter: (in)ICommand* pDeleteHelper … オブジェクトの破棄方法
	//
	// return: bool … 登録処理結果
	//　　　　true … 登録成功（以前の登録情報は破棄されています
	//　　　　false … 登録失敗（上書きが禁止状態で、すでに登録が完了している）
	//----------------------------------------------------------
	template<class T>
		bool Register(WriteMode::MODE mode, T* pObj,
			typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*), ICommand* pDeleteHelper)
	{
		//	一度だけの登録
		if (mode == WriteMode::Once)
		{
			//	すでに登録されている
			if (_pCommand)
			{
				return false;
			}
		}

		//	すでに登録されていたら破棄する
		if (_auto)
		{
			if (_pCommand)
			{
				delete _pCommand;
			}
		}

		//	呼び出し元のオブジェクトを破棄する、描画呼び出しオブジェクトを生成
		_pCommand =
			new DrawFunction<true, T>(pObj, begin, end, pDeleteHelper);

		return true;
	};

	//----------------------------------------------------------
	//	描画の各呼び出しメソッドを登録する
	//
	// parameter: (in)WriteMode::MODE mode … 登録オプション
	// parameter: (in)T* pObj … 呼び出し元オブジェクトへのポインタ
	// parameter: (in)void (T::*begin)(RenderStates*) … 描画開始メソッド
	// parameter: (in)void (T::*end)(RenderStates*) … 描画の後処理メソッド
	//
	// return: bool … 登録処理結果
	//　　　　true … 登録成功（以前の登録情報は破棄されています）
	//　　　　false … 登録失敗（上書きが禁止状態で、すでに登録が完了している）
	//----------------------------------------------------------
	template<class T>
		bool Register(WriteMode::MODE mode, T* pObj,
			typename void (T::*begin)(RenderStates*),
			typename void (T::*end)(RenderStates*))
	{
		//	一度だけの登録
		if (mode == WriteMode::Once)
		{
			//	すでに登録されている
			if (_pCommand)
			{
				return false;
			}
		}

		//	すでに登録されていたら破棄する
		if (_auto)
		{
			if (_pCommand)
			{
				delete _pCommand;
			}
		}

		//	呼び出し元オブジェクトを破棄しない、描画呼び出しオブジェクトを生成
		_pCommand = new DrawFunction<false, T>(pObj, begin, end);

		return true;
	};

	//----------------------------------------------------------
	//	描画の各呼び出しオブジェクト、ならびに破棄責任を委譲する
	//
	// return: IDrawCommand* … 描画の各呼び出しオブジェクトへのポインタ
	//
	// memo: 描画の各呼び出しオブジェクトは、破棄を保障されなくなるので、
	//　　　必ず Release() メソッドか、委譲先で破棄するようにする
	//----------------------------------------------------------
	operator IDrawCommand* (void)
	{
		//	デストラクタでの破棄を行わない
		_auto = false;

		return _pCommand;
	};

	//----------------------------------------------------------
	//	描画の各呼び出しオブジェクトを破棄する
	//----------------------------------------------------------
	void Release(void)
	{
		//	まだ破棄されていない
		if (_pCommand)
		{
			delete _pCommand;
			_pCommand = NULL;
		}
	};
};

//	描画の各呼び出しメソッド登録時に、何も動作を行わない null を指定する
#define DRAWDELEGATE_NULL(type) (void (type::*)(RenderStates*))0

};//namespace Renderable
};//namespace gift

#endif
