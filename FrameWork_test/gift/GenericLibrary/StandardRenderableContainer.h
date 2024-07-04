//----------------------------------------------------------
// file name: StandardRenderableContainer.h
//
// memo: レンダーステートと描画呼び出しオブジェクトを格納、制御する
//----------------------------------------------------------

#ifndef	__STANDARD_RENDERABLE_CONTAINER_H
#define	__STANDARD_RENDERABLE_CONTAINER_H

#include <stdio.h>
#include "IRenderableContainer.h"


namespace gift
{

	namespace Private
	{

		namespace Renderable
		{

//----------------------------------------------------------
// name: gift::Private::Renderable::StandardRenderableContainer
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableContainer is interface
//
// memo: 描画基準の親として、データ格納、制御するコンテナ
//----------------------------------------------------------
class	StandardRenderableContainer
	: public gift::Renderable::IRenderableContainer
{
private:
	bool			_isDisposable;	//	破棄の有無
	bool			_ChangeState;	//	データ交換の有無
	float			_priority;		//	実行優先度
	gift::Renderable::IDrawCommand*	_pCommand;		//	描画呼び出し
	RenderStates	_myState;		//	所持している描画データ
	RenderStates*	_pAnyState;		//	転送されてきたデータ記憶用

	//	呼び出し実行時の振る舞い
	RenderStates* (StandardRenderableContainer::*_strategy)(RenderStates*);

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	StandardRenderableContainer(void)
		: _isDisposable(false), _ChangeState(false), _pCommand(NULL), _myState(),
		_pAnyState(NULL), _strategy(StandardRenderableContainer::BeginAnyState)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~StandardRenderableContainer(void)
	{
		//	破棄を任されている
		if (_isDisposable)
		{
			//	破棄されていない
			if (_pCommand)
			{
				delete _pCommand;
			}
		}
	};

	//----------------------------------------------------------
	//	描画時に自身のレンダーステートを利用するかの有無
	//
	// parameter: (in)bool value … レンダーステート切り替えの有無
	//
	// memo: true なら、自身のレンダーステートを以後使うようにする
	//　　　false なら、転送されてきたレンダーステートを利用する
	//----------------------------------------------------------
	void Enable(bool value)
	{
		_ChangeState = value;

		//	自身のレンダーステートを使う
		if (_ChangeState)
		{
			_strategy = StandardRenderableContainer::BeginMyState;
		}
		//	転送されて来たレンダーステートを使う
		else
		{
			_strategy = StandardRenderableContainer::BeginAnyState;
		}
	};

	//----------------------------------------------------------
	//	自身を含めた今後の描画時に利用するレンダーステートを設定する
	//
	// parameter: (in)const RenderStates& states … コピー元への参照
	//----------------------------------------------------------
	void SetRenderStates(const RenderStates& states)
	{
		_myState = states;
	};

	//----------------------------------------------------------
	//	描画優先度を取得
	//
	// return: float … 優先度
	//
	// attrib: override
	//----------------------------------------------------------
	float GetPriority(void)
	{
		return _priority;
	};

	//----------------------------------------------------------
	//	描画呼び出しオブジェクト、実行優先度、破棄処理を登録する
	//
	// parameter: (in)IDrawCommand* pCommand … 描画呼び出しへのポインタ
	// parameter: (in)float priority … 実行優先度
	// parameter: (in)bool isDisposable … 破棄処理の有無
	//
	// return: bool … 実行結果
	//　　　　true … 登録成功
	//　　　　false … すでに登録されているため失敗
	//
	// attrib: override
	//----------------------------------------------------------
	bool Load(gift::Renderable::IDrawCommand* pCommand, float priority, bool isDisposable);

	//----------------------------------------------------------
	//	描画呼び出しオブジェクト、実行優先度を登録する
	//
	// parameter: (in)IDrawCommand* pCommand … 描画呼び出しへのポインタ
	// parameter: (in)float priority … 実行優先度
	//
	// return: bool … 実行結果
	//　　　　true … 登録成功
	//　　　　false … すでに登録されているため失敗
	//
	// attrib: override
	//----------------------------------------------------------
	bool Load(gift::Renderable::IDrawCommand* pCommand, float priority);

	//----------------------------------------------------------
	//	描画呼び出しオブジェクト、破棄処理を登録する
	//
	// paramter: (in)IDrawCommand* pCommand … 描画呼び出しへのポインタ
	// paramter: (in)bool isDisposable … 破棄処理の有無
	//
	// return: bool … 実行結果
	//　　　　true … 登録成功
	//　　　　false … すでに登録されているため失敗
	//
	// attrib: override
	//----------------------------------------------------------
	bool Load(gift::Renderable::IDrawCommand* pCommand, bool isDisposable);

	//----------------------------------------------------------
	//	描画呼び出しオブジェクトを登録する
	//
	// paramter: (in)IDrawCommand* pCommand … 描画呼び出しへのポインタ
	//
	// return: bool … 実行結果
	//　　　　true … 登録成功
	//　　　　false … すでに登録されているため失敗
	//
	// attrib: override
	//----------------------------------------------------------
	bool Load(gift::Renderable::IDrawCommand* pCommand);

	//----------------------------------------------------------
	//	描画の呼び出しを順次実行させる
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 次の呼び出しで使われるレンダーステート
	//
	// attrib: override
	//----------------------------------------------------------
	RenderStates* Execute(RenderStates* pStates);

	//----------------------------------------------------------
	//	描画呼び出しオブジェクトなどを格納し直す準備
	//
	// attrib: override
	//----------------------------------------------------------
	void Reload(void);

private:
	//----------------------------------------------------------
	//	自身のレンダーステートで描画開始時のメソッド呼び出しを実行させる
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 自身のレンダーステートへのポインタ
	//----------------------------------------------------------
	RenderStates* BeginMyState(RenderStates* pStates);

	//----------------------------------------------------------
	//	自身のレンダーステートで描画の後処理メソッドの呼び出しを実行さえる
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 元のレンダーステートへのポインタ
	//----------------------------------------------------------
	RenderStates* EndMyState(RenderStates* pStates);

	//----------------------------------------------------------
	//	空回し用のメソッド
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 引数のレンダーステート
	//----------------------------------------------------------
	RenderStates* NullMyState(RenderStates* pStates)
	{
		_strategy = StandardRenderableContainer::BeginMyState;

		return pStates;
	};

	//----------------------------------------------------------
	//	描画開始時のメソッド呼び出しを実行させる
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 今後使うレンダーステートへのポインタ
	//----------------------------------------------------------
	RenderStates* BeginAnyState(RenderStates* pStates);

	//----------------------------------------------------------
	//	描画の後処理メソッドの呼び出しを実行さえる
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 今後使うレンダーステートへのポインタ
	//----------------------------------------------------------
	RenderStates* EndAnyState(RenderStates* pStates);

	//----------------------------------------------------------
	//	空回し用のメソッド
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 引数のレンダーステート
	//----------------------------------------------------------
	RenderStates* NullAnyState(RenderStates* pStates)
	{
		_strategy = StandardRenderableContainer::BeginAnyState;

		return pStates;
	};
};

};//namespace Renderable
};//namespace Private
};//namespace gift

#endif
