//----------------------------------------------------------
// file name: RenderableContainer.h
//
// memo: 描画メソッド呼び出しオブジェクト、格納管理クラス
//----------------------------------------------------------

#ifndef	__RENDERABLE_CONTAINER_H
#define	__RENDERABLE_CONTAINER_H

#include <stdio.h>
#include "IRenderableContainer.h"

namespace gift
{

	namespace Private
	{

		namespace Renderable
		{

//----------------------------------------------------------
// name: gift::Private::Renderable::RenderableContainer
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableContainer is interface
//
// memo: 子として連結させる際に格納、制御するコンテナ
//----------------------------------------------------------
class	RenderableContainer
	: public gift::Renderable::IRenderableContainer
{
private:
	bool			_isDisposable;	//	破棄の有無
	float			_priority;		//	実行優先度
	gift::Renderable::IDrawCommand*	_pCommand;		//	描画呼び出し

	//	呼び出し実行時の振る舞い
	RenderStates* (RenderableContainer::*_strategy)(RenderStates*);

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	RenderableContainer(void)
		: _isDisposable(false), _priority(0.0f),
		_pCommand(NULL), _strategy(RenderableContainer::Begin)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~RenderableContainer(void)
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
	//	描画開始時のメソッド呼び出しを実行させる
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 次に使うレンダーステートへのポインタ
	//----------------------------------------------------------
	RenderStates* Begin(RenderStates* pStates);

	//----------------------------------------------------------
	//	描画の後処理メソッドの呼び出しを実行させる
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 次に使うレンダーステートへのポインタ
	//----------------------------------------------------------
	RenderStates* End(RenderStates* pStates);

	//----------------------------------------------------------
	//	空回し用のメソッド
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 引数のレンダーステート
	//----------------------------------------------------------
	RenderStates* Null(RenderStates* pStates)
	{
		_strategy = RenderableContainer::Begin;

		return pStates;
	};
};

};//namespace Renderable
};//namespace Private
};//namespace gift

#endif
