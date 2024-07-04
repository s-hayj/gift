//----------------------------------------------------------
// file name: IRenderableContainer.h
//
// memo: 描画メソッド呼び出しようオブジェクトと、制御情報格納用インターフェース
//----------------------------------------------------------

#ifndef	__IRENDERABLE_CONTAINER_H
#define	__IRENDERABLE_CONTAINER_H

#include "IDrawCommand.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::IRenderableContainer
//
// attrib: interface
//
// memo: 描画呼び出しオブジェクトを、優先度と共に格納用インターフェース
//----------------------------------------------------------
class	IRenderableContainer
{
public:
	virtual ~IRenderableContainer(void) {};

	//----------------------------------------------------------
	//	描画優先度を取得
	//
	// return: float … 優先度
	//----------------------------------------------------------
	virtual float GetPriority(void) = 0;

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
	virtual bool Load(IDrawCommand* pCommand,
		float priority, bool isDisposable) = 0;

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
	virtual bool Load(IDrawCommand* pCommand, float priority) = 0;

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
	virtual bool Load(IDrawCommand* pCommand, bool isDisposable) = 0;

	//----------------------------------------------------------
	//	描画呼び出しオブジェクトを登録する
	//
	// paramter: (in)IDrawCommand* pCommand … 描画呼び出しへのポインタ
	//
	// return: bool … 実行結果
	//　　　　true … 登録成功
	//　　　　false … すでに登録されているため失敗
	//----------------------------------------------------------
	virtual bool Load(IDrawCommand* pCommand) = 0;

	//----------------------------------------------------------
	//	描画の呼び出しを順次実行させる
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//
	// return: RenderStates* … 次の呼び出しで使われるレンダーステート
	//----------------------------------------------------------
	virtual RenderStates* Execute(RenderStates* pStates) = 0;

	//----------------------------------------------------------
	//	描画呼び出しオブジェクトなどを格納し直す準備
	//----------------------------------------------------------
	virtual void Reload(void) = 0;
};

	};//namespace Renderable
};//namespace gift

#endif
