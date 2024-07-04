//----------------------------------------------------------
// file name: RenderableContainer.cpp
//
// memo: 描画呼び出しオブジェクトの登録と、実行制御
//----------------------------------------------------------

#include <assert.h>
#include "RenderableContainer.h"

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
bool RenderableContainer::Load(IDrawCommand* pCommand,
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
bool RenderableContainer::Load(IDrawCommand* pCommand, float priority)
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
bool RenderableContainer::Load(IDrawCommand* pCommand, bool isDisposable)
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
bool RenderableContainer::Load(IDrawCommand* pCommand)
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
RenderStates* RenderableContainer::Execute(RenderStates* pStates)
{
	assert(_pCommand != NULL);

	//	描画呼び出し処理を実行させる
	return (this->*_strategy)(pStates);
}

//----------------------------------------------------------
//	描画呼び出しオブジェクトなどを格納し直す準備
//----------------------------------------------------------
void RenderableContainer::Reload(void)
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
	_strategy		= RenderableContainer::Begin;
}

//----------------------------------------------------------
//	描画開始時のメソッド呼び出しを実行させる
//
// parameter: (in)RenderStates* pStates … レンダーステート
//
// return: RenderStates* … 次に使うレンダーステートへのポインタ
//----------------------------------------------------------
RenderStates* RenderableContainer::Begin(RenderStates* pStates)
{
	//	描画開始の呼び出し
	_pCommand->DrawBegin(pStates);

	//	次は描画の後処理を呼び出させる
	_strategy = RenderableContainer::End;

	return pStates;
}

//----------------------------------------------------------
//	描画の後処理メソッドの呼び出しを実行させる
//
// parameter: (in)RenderStates* pStates … レンダーステート
//
// return: RenderStates* … 次に使うレンダーステートへのポインタ
//----------------------------------------------------------
RenderStates* RenderableContainer::End(RenderStates* pStates)
{
	//	描画の後処理を呼び出す
	_pCommand->DrawEnd(pStates);

	//	次は描画開始処理を呼び出させる
	_strategy = RenderableContainer::Null;

	return pStates;
}
