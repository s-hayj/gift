//----------------------------------------------------------
// file name: StandardRenderableContainer.cpp
//
// memo: レンダーステートと描画呼び出しオブジェクトを格納、制御する
//----------------------------------------------------------

#include <assert.h>
#include "StandardRenderableContainer.h"

using namespace gift;
using namespace gift::Renderable;
using namespace gift::Private;
using namespace gift::Private::Renderable;

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
//----------------------------------------------------------
bool StandardRenderableContainer::Load(IDrawCommand* pCommand,
									   float priority, bool isDisposable)
{
	//	すでに登録されている
	if (_pCommand)
	{
		return false;
	}

	_isDisposable = isDisposable;
	_priority = priority;
	_pCommand = pCommand;

	return true;
}

//----------------------------------------------------------
//	描画呼び出しオブジェクト、実行優先度を登録する
//
// parameter: (in)IDrawCommand* pCommand … 描画呼び出しへのポインタ
// parameter: (in)float priority … 実行優先度
//
// return: bool … 実行結果
//　　　　true … 登録成功
//　　　　false … すでに登録されているため失敗
//----------------------------------------------------------
bool StandardRenderableContainer::Load(IDrawCommand* pCommand, float priority)
{
	//	破棄処理を行わせないで、登録開始
	return this->Load(pCommand, priority, false);
}

//----------------------------------------------------------
//	描画呼び出しオブジェクト、破棄処理を登録する
//
// paramter: (in)IDrawCommand* pCommand … 描画呼び出しへのポインタ
// paramter: (in)bool isDisposable … 破棄処理の有無
//
// return: bool … 実行結果
//　　　　true … 登録成功
//　　　　false … すでに登録されているため失敗
//----------------------------------------------------------
bool StandardRenderableContainer::Load(IDrawCommand* pCommand,
									   bool isDisposable)
{
	//	デフォルトの優先度で、登録開始
	return this->Load(pCommand, 0.0f, isDisposable);
}

//----------------------------------------------------------
//	描画呼び出しオブジェクトを登録する
//
// paramter: (in)IDrawCommand* pCommand … 描画呼び出しへのポインタ
//
// return: bool … 実行結果
//　　　　true … 登録成功
//　　　　false … すでに登録されているため失敗
//----------------------------------------------------------
bool StandardRenderableContainer::Load(IDrawCommand* pCommand)
{
	//	破棄処理を行わず、デフォルトの優先度で登録開始
	return this->Load(pCommand, 0.0f, false);
}

//----------------------------------------------------------
//	描画の呼び出しを順次実行させる
//
// parameter: (in)RenderStates* pStates … レンダーステート
//
// return: RenderStates* … 次の呼び出しで使われるレンダーステート
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::Execute(RenderStates* pStates)
{
	assert(_pCommand != NULL);

	//	描画呼び出し処理を実行させる
	return (this->*_strategy)(pStates);
}

//----------------------------------------------------------
//	描画呼び出しオブジェクトなどを格納し直す準備
//----------------------------------------------------------
void StandardRenderableContainer::Reload(void)
{
	//	使い捨てオブジェクト
	if (_isDisposable)
	{
		assert(_pCommand != NULL);
		delete _pCommand;
	}

	_isDisposable	= false;
	_priority		= 0.0f;
	_pCommand		= NULL;

	//	描画呼び出しメソッドを選択する
	this->Enable(_ChangeState);
}

//----------------------------------------------------------
//	自身のレンダーステートで描画開始時のメソッド呼び出しを実行させる
//
// parameter: (in)RenderStates* pStates … レンダーステート
//
// return: RenderStates* … 自身のレンダーステートへのポインタ
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::BeginMyState(RenderStates* pStates)
{
	//	元のレンダーステートへのポインタを記憶
	_pAnyState = pStates;

	//	自身のレンダーステートを渡して描画開始の呼び出し
	_pCommand->DrawBegin(&_myState);

	//	次は描画の後処理を呼び出させる
	_strategy = StandardRenderableContainer::EndMyState;

	return &_myState;
}

//----------------------------------------------------------
//	自身のレンダーステートで描画の後処理メソッドの呼び出しを実行さえる
//
// parameter: (in)RenderStates* pStates … レンダーステート
//
// return: RenderStates* … 元のレンダーステートへのポインタ
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::EndMyState(RenderStates* pStates)
{
	//	描画の後処理を呼び出す
	_pCommand->DrawEnd(&_myState);

	//	次は描画開始処理を呼び出させる
	_strategy = StandardRenderableContainer::NullMyState;

	return _pAnyState;
}

//----------------------------------------------------------
//	描画開始時のメソッド呼び出しを実行させる
//
// parameter: (in)RenderStates* pStates … レンダーステート
//
// return: RenderStates* … 今後使うレンダーステートへのポインタ
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::BeginAnyState(RenderStates* pStates)
{
	//	描画開始の呼び出し
	_pCommand->DrawBegin(pStates);

	//	次は描画の後処理を呼び出させる
	_strategy = StandardRenderableContainer::EndAnyState;

	return pStates;
}

//----------------------------------------------------------
//	描画の後処理メソッドの呼び出しを実行さえる
//
// parameter: (in)RenderStates* pStates … レンダーステート
//
// return: RenderStates* … 今後使うレンダーステートへのポインタ
//----------------------------------------------------------
RenderStates* StandardRenderableContainer::EndAnyState(RenderStates* pStates)
{
	//	描画の後処理を呼び出す
	_pCommand->DrawEnd(pStates);

	//	次は描画開始処理を呼び出させる
	_strategy = StandardRenderableContainer::NullAnyState;

	return pStates;
}
