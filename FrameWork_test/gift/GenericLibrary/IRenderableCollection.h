//----------------------------------------------------------
// file name: IRenderableCollection.h
//
// memo: 描画の実行制御に関する各オブジェクト取得用インターフェース
//----------------------------------------------------------

#ifndef	__IRENDERABLE_COLLECTION_H
#define	__IRENDERABLE_COLLECTION_H

#include "IRenderableContainer.h"
#include "RenderableComponent.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::IRenderableCollection
//
// attrib: interface
//
// memo: 描画実行管理に関する各オブジェクト群の生成管理
//----------------------------------------------------------
class	IRenderableCollection
{
public:
	//----------------------------------------------------------
	//	描画呼び出し制御格納コンテナを連結するコンポーネントを取得
	//
	// return: IRenderableComponent* … コンテナ格納コンポーネント
	//----------------------------------------------------------
	virtual IRenderableComponent* OrderComponent(void) = 0;

	//----------------------------------------------------------
	//	描画呼び出し管理オブジェクトを取得
	//
	// return: IRenderableContainer* … 描画呼び出し管理オブジェクト
	//----------------------------------------------------------
	virtual IRenderableContainer* OrderContainer(void) = 0;

	//----------------------------------------------------------
	//	レンダーステートを独自に保持する、描画呼び出し管理オブジェクトを取得
	//
	// parameter: (in)RenderStates& state … レンダーステートコピー元への参照
	// parameter: (in)bool isMyStates … 描画時に自身のステート利用の有無
	//
	// return: IRenderableContainer* … 描画呼び出し管理オブジェクト
	//----------------------------------------------------------
	virtual IRenderableContainer* OrderContainer(RenderStates& state, bool isMyStates) = 0;

	//----------------------------------------------------------
	//	描画制御格納コンテナ連結コンポーネントを返却する
	//
	// parameter: (in)IRenderableComponent pComponent* … 返却するオブジェクトへのポインタ
	//----------------------------------------------------------
	virtual void ReturnComponent(IRenderableComponent* pComponent) = 0;

	//----------------------------------------------------------
	//	描画呼び出し管理オブジェクトを返却する
	//
	// parameter: (in)IRenderableContainer* pContainer … 返却するオブジェクトへのポインタ
	//----------------------------------------------------------
	virtual void ReturnContainer(IRenderableContainer* pContainer) = 0;

protected:
	virtual ~IRenderableCollection(void) {};
};

	};//namespace Renderable
};//namespace gift

#endif
