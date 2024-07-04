//----------------------------------------------------------
// file name: IDrawCommand.h
//
// memo: 描画時の各実行メソッドを委譲するためのインターフェース
//----------------------------------------------------------

#ifndef	__IDRAW_COMMAND_H
#define	__IDRAW_COMMAND_H

#include "RenderStates.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::IDrawCommand
//
// attrib: interface
//
// memo: 描画実行時の各呼び出し用インターフェース
//----------------------------------------------------------
class	IDrawCommand
{
public:
	virtual ~IDrawCommand(void) {};

	//----------------------------------------------------------
	//	描画を実行する
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//----------------------------------------------------------
	virtual void DrawBegin(RenderStates* pStates) = 0;

	//----------------------------------------------------------
	//	描画の後処理を実行する
	//
	// parameter: (in)RenderStates* pStates … レンダーステート
	//----------------------------------------------------------
	virtual void DrawEnd(RenderStates* pStates) = 0;
};

	};//namespace Renderable
};//namespace gift

#endif
