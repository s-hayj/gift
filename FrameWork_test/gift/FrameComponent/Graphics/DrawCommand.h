//----------------------------------------------------------
//	@file	DrawCommand.h
//
//	@memo	描画処理の登録に関する制御
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__DRAW_COMMAND_H
#define	__DRAW_COMMAND_H

#include "IRenderable.h"

//----------------------------------------------------------
//	@name	DrawCommand
//
//	@memo	描画メソッドを格納、登録操作制御
//
//	@attrib	public final class
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	DrawCommand
{
private:
	//----------------------------------------------------------
	//	@name	DrawCommand::FunctionObject
	//
	//	@memo	関数オブジェクトの描画メソッド格納用
	//
	//	@attrib	private nested template final sub class
	//
	//	@type	T	関数オブジェクトの型
	//
	//	@base	public IRenderable
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template< class T >
	class	FunctionObject
		: public IRenderable
	{
	public:
		typedef	typename void (T::*Method)(RenderState*);

	private:
		T		_obj;	//	呼び出すオブジェクト
		Method*	_pFun;	//	呼び出すメソッド

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	DrawCommand::FunctionObject::FunctionObject
		//
		//	@attrib	public
		//
		//	@attrib	(in)pFunction	呼び出す描画メソッドへのポインタ
		//----------------------------------------------------------
		FunctionObject( Method* pFunction )
			: _pFun( pFunction )
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	DrawCommand::FunctionObject::~FunctionObject
		//
		//	@attrib	public
		//----------------------------------------------------------
		~FunctionObject(void)
		{
		};

		//----------------------------------------------------------
		//	登録された描画操作メソッドを呼び出す
		//
		//	@name	DrawCommand::FunctionObject::Draw
		//
		//	@memo	間接的に描画メソッドを呼び出す中継をする
		//
		//	@attrib	public override
		//
		//	@base	IRenderable::Draw
		//
		//	@param	(in/out)pState	描画に関する情報群
		//
		//	@return	none
		//----------------------------------------------------------
		void Draw( RenderState* pState )
		{
			(_obj.*_pFun)( pState );
		};
	};

	//----------------------------------------------------------
	//	@name	Function
	//
	//	@memo	静的な関数を格納する
	//
	//	@attrib	private nested final sub class
	//
	//	@base	public IRenderable
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	class	Function
		: public IRenderable
	{
	public:
		typedef typename void (*Method)(RenderState*);

	private:
		Method*	_pFun;	//	呼び出す関数へのポインタ

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	DrawCommand::Function::Function
		//
		//	@attrib	public
		//
		//	@param	(in)pFunction	呼び出す関数へのポインタ
		//----------------------------------------------------------
		Function( Method* pFunction)
			: _pFun( pFunction )
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	DrawCommand::Function::~Function
		//
		//	@attrib	public
		//----------------------------------------------------------
		~Function(void)
		{
		};

		//----------------------------------------------------------
		//	格納している関数を呼び出す
		//
		//	@name	DrawCommand::Function::Draw
		//
		//	@memo	間接的に描画メソッドを呼び出す
		//
		//	@attrib	public override
		//
		//	@base	IRenderable::Draw
		//
		//	@param	(in/out)pState
		//
		//	@return	none
		//----------------------------------------------------------
		void Draw( RenderState *pState )
		{
			(*_pFun)( pState );
		};
	};

	//----------------------------------------------------------
	//	@name	DrawCommand::ObjectMethod
	//
	//	@memo	オブジェクトのメンバ関数を格納する
	//
	//	@attrib	private nested template final sub class
	//
	//	@type	T	登録するオブジェクトの型
	//
	//	@base	public IRenderable
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template< class T >
	class	ObjectMethod
		: public IRenderable
	{
	public:
		typedef typename void (T::*Method)(RenderState*);

	private:
		T*		_pObj;	//	呼び出しオブジェクトへのポインタ
		Method*	_pFun;	//	呼び出しメソッドへのポインタ

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	DrawCommand::ObjectMethod::ObjectMethod
		//
		//	@attrib	public
		//
		//	@param	(in)pObject		呼び出し元オブジェクトへのポインタ
		//	@param	(in)pFunction	呼び出すメンバ関数へのポインタ
		//----------------------------------------------------------
		ObjectMethod( T* pObject, Method* pFunction )
			: _pObj(pObject), _pFunction(pFunction)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	DrawCommand::ObjectMethod::~ObjectMethod
		//
		//	@attrib	public
		//----------------------------------------------------------
		~ObjectMethod(void)
		{
		};

		//----------------------------------------------------------
		//	格納メンバ関数を呼び出す
		//
		//	@name	DrawCommand::ObjectMethod::Draw
		//
		//	@memo	描画メソッドを間接的に呼び出す
		//
		//	@attrib	public override
		//
		//	@base	IRenderable::Draw
		//
		//	@param	(in/out)pState
		//
		//	@return	none
		//----------------------------------------------------------
		void Draw( RenderState* pState )
		{
			(_pObj->*_pFun)(pState);
		};
	};

private:
	IRenderable*	_pRender;	//	間接描画操作オブジェクト

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	DrawCommand::DrawCommnad
	//
	//	@attrib	public
	//
	//	@param	(in)pFunction	呼び出す関数へのポインタ
	//----------------------------------------------------------
	DrawCommand( void (*pFunction)(RenderState*) )
		: _pRender( NULL )
	{
		//	静的な関数を格納する
		_pRender = new DrawCommand::Function( pFunction );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	DrawCommand::DrawCommand
	//
	//	@attrib	public template
	//
	//	@type	T	呼び出すオブジェクトの型
	//
	//	@param	(in)object		描画呼び出し元のオブジェクト
	//	@param	(in)pFunction	呼び出す描画操作メンバ関数ポインタ
	//----------------------------------------------------------
	template< class T >
		DrawCommand( T& object, typename void (T::*pFunction)(RenderState*) )
		: _pRender( NULL )
	{
		//	関数オブジェクトのメンバ関数を格納する
		_pRender = new DrawCommand::FunctionObject< T >( pFunction );
	}

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	DrawCommand::DrawCommand
	//
	//	@attrib	public template
	//
	//	@type	T	呼び出すオブジェクトの型
	//
	//	@param	(in)pObject		描画呼び出し元へのポインタ
	//	@param	(in)pFunction	呼び出す描画操作メンバ関数ポインタ
	//----------------------------------------------------------
	template< class T >
		DrawCommand( T* pObject, typename void (T::*pFunction)(RenderState*) )
		: _pRender( NULL )
	{
		//	オブジェクトのメンバ関数を格納する
		_pRender = new DrawCommand::ObjectMethod< T >( pObject, pFunction );
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	DrawCommand::DrawCommnad
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	DrawCommnad(void)
		: _pRender( NULL )
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	DrawCommand::~DrawCommand
	//
	//	@attrib	public
	//----------------------------------------------------------
	~DrawCommand(void)
	{
		//	呼び出しオブジェクトを破棄する
		this->Release();
	};

	//----------------------------------------------------------
	//	描画操作の呼び出し先を再登録する
	//
	//	@name	DrawCommand::Register
	//
	//	@memo	関数オブジェクトの描画メソッドを登録する
	//
	//	@attrib	public template
	//
	//	@type	T	呼び出すオブジェクトの型
	//
	//	@param	(in)object		描画呼び出し元のオブジェクト
	//	@param	(in)pFunction	呼び出す描画操作メンバ関数ポインタ
	//
	//	@return	none
	//----------------------------------------------------------
	template< class T >
		void Register( T& object, typename void (T::*pFunction)(RenderState*) )
	{
		//	登録中のメソッドを破棄する
		this->Release();

		//	関数オブジェクトの描画メソッドを登録する
		_pRender = new DrawCommand::FunctionObject< T >( pFunction );
	};

	//----------------------------------------------------------
	//	描画操作の呼び出し先を再登録する
	//
	//	@name	DrawCommand::Register
	//
	//	@memo	静的な関数を登録する
	//
	//	@attrib	public
	//
	//	@param	(in)pFunction	呼び出す描画操作関数ポインタ
	//
	//	@return	none
	//----------------------------------------------------------
	void Register( void (*pFunction)(RenderState*) )
	{
		//	登録中のメソッドを破棄する
		this->Release();

		//	静的な関数ポインタを登録する
		_pRender = new DrawCommand::Function( pFunction );
	};

	//----------------------------------------------------------
	//	描画操作の呼び出し先を再登録する
	//
	//	@name	DrawCommand::Register
	//
	//	@memo	オブジェクトのメンバ関数を登録する
	//
	//	@attrib	public template
	//
	//	@type	T	呼び出すオブジェクトの型
	//
	//	@param	(in)pObject		描画呼び出し元のオブジェクト
	//	@param	(in)pFunction	呼び出す描画操作メンバ関数ポインタ
	//
	//	@return	none
	//----------------------------------------------------------
	template< class T >
		void Register( T* pObject, typename void (T::*pFunction)(pFunction) )
	{
		//	登録中のメソッドを破棄する
		this->Register();

		//	オブジェクトのメンバ関数を登録する
		_pRender = new DrawCommand::ObjectMethod( pObject, pFunction );
	};

	//----------------------------------------------------------
	//	登録メソッドを破棄する
	//
	//	@name	DrawCommand::Release
	//
	//	@memo	再び登録をするまで処理をスルーする
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Release(void)
	{
		//	破棄されていない
		if ( _pRender )
		{
			delete _pRender;
			_pRender = NULL;
		}
	};

	//----------------------------------------------------------
	//	描画呼び出し先のインターフェースを参照する
	//
	//	@name	DrawCommand::GetRenderable
	//
	//	@memo	登録した描画操作を間接的に呼び出すインターフェースを返す
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	IRenderable*	NULL	登録に失敗もしくは、未登録
	//----------------------------------------------------------
	IRenderable* GetRenderable(void)
	{
		return _pRender;
	};

	//----------------------------------------------------------
	//	描画呼び出し先のインターフェースを参照する
	//
	//	@name	DrawCommand::operator IRenderable*
	//
	//	@memo	暗黙的型変換
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	IRenderable*	NULL	登録に失敗もしくは、未登録
	//----------------------------------------------------------
	operator IRenderable* (void)
	{
		return _pRender;
	};

private:
	//----------------------------------------------------------
	//	コピーコンストラクタ
	//
	//	@name	DrawCommand::DrawCommnad
	//
	//	@memo	コピーコンストラクタを禁止する
	//
	//	@attrib	private
	//
	//	@param	(in)object	コピーするデータ対象
	//----------------------------------------------------------
	DrawCommand( DrawCommand& object )
	{
	};

	//----------------------------------------------------------
	//	代入演算子のオーバーロード
	//
	//	@name	DrawCommand::operator =
	//
	//	@memo	代入を禁止する
	//
	//	@attrib	private
	//
	//	@param	(in)object	代入元への参照
	//
	//	@param	none
	//----------------------------------------------------------
	void operator = ( DrawCommand& object )
	{
	};
};

#endif