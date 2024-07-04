//----------------------------------------------------------
// file name: RenderableCollection.cpp
//
// memo: 描画呼び出し管理オブジェクトや、それらを格納管理するクラス
//----------------------------------------------------------

#include "RenderableCollection.h"
#include "RenderableComponent.h"

#include "NewDelManager.h"

using namespace gift;
using namespace gift::Renderable;
using namespace gift::Private;
using namespace gift::Private::Renderable;

//----------------------------------------------------------
//	コンストラクタ
//----------------------------------------------------------
RenderableCollection::RenderableCollection(void)
{
	//	描画実行管理オブジェクト格納連結用オブジェクトの生成、破棄方法の登録
	_pComponentBank = new ObjectBank<IRenderableComponent*>(
		NewDelManager<IRenderableComponent*>(
			RenderableFactory(), RenderableFactory::Create,
			RenderableFactory(), RenderableFactory::Delete));

	//	描画実行管理オブジェクトの生成、破棄方法を登録
	_pRenderableBank = new ObjectBank<RenderableContainer*>(
		NewDelManager<RenderableContainer*>(
			RenderableFactory(), RenderableFactory::Create,
			RenderableFactory(), RenderableFactory::Delete));

	//	レンダーステートを保持した描画実行管理オブジェクトの生成、破棄方法の登録
	_pStandardBank = new ObjectBank<StandardRenderableContainer*>(
		NewDelManager<StandardRenderableContainer*>(
			RenderableFactory(), RenderableFactory::Create,
			RenderableFactory(), RenderableFactory::Delete));

	//	描画実行管理オブジェクトの連結用オブジェクトに、在庫管理オブジェクトを登録
	RenderableComponent::sRegister(_pComponentBank);
}

//----------------------------------------------------------
//	デストラクタ
//----------------------------------------------------------
RenderableCollection::~RenderableCollection(void)
{
	delete _pComponentBank;
	delete _pRenderableBank;
	delete _pStandardBank;
}

//----------------------------------------------------------
//	描画呼び出し制御格納コンテナを連結するコンポーネントを取得
//
// return: IRenderableComponent* … コンテナ格納コンポーネント
//
// attrib: override
//----------------------------------------------------------
IRenderableComponent* RenderableCollection::OrderComponent(void)
{
	//	オブジェクトを発注する
	return _pComponentBank->Order();
}

//----------------------------------------------------------
//	描画呼び出し管理オブジェクトを取得
//
// return: IRenderableContainer* … 描画呼び出し管理オブジェクト
//
// attrib: override
//----------------------------------------------------------
IRenderableContainer* RenderableCollection::OrderContainer(void)
{
	//	オブジェクトを発注する
	return _pRenderableBank->Order();
}

//----------------------------------------------------------
//	レンダーステートを独自に保持する、描画呼び出し管理オブジェクトを取得
//
// parameter: (in)RenderStates& state … レンダーステートコピー元への参照
// parameter: (in)bool isMyStates … 描画時に自身のステート利用の有無
//
// return: IRenderableContainer* … 描画呼び出し管理オブジェクト
//
// attrib: override
//----------------------------------------------------------
IRenderableContainer* RenderableCollection::OrderContainer(RenderStates& state,
														   bool isMyStates)
{
	//	オブジェクトを発注する
	StandardRenderableContainer* pTemp = _pStandardBank->Order();

	//	レンダーステートの初期化を行う
	pTemp->SetRenderStates(state);
	pTemp->Enable(isMyStates);

	return pTemp;
}

//----------------------------------------------------------
//	描画制御格納コンテナ連結コンポーネントを返却する
//
// parameter: (in)IRenderableComponent pComponent* … 返却するオブジェクトへのポインタ
//
// attrib: override
//----------------------------------------------------------
void RenderableCollection::ReturnComponent(IRenderableComponent* pComponent)
{
	//	リストを返却する
	_pComponentBank->Return(pComponent);
}

//----------------------------------------------------------
//	描画呼び出し管理オブジェクトを返却する
//
// parameter: (in)IRenderableContainer* pContainer … 返却するオブジェクトへのポインタ
//
// attrib: override
//----------------------------------------------------------
void RenderableCollection::ReturnContainer(IRenderableContainer* pContainer)
{
	//	返却先を識別する
	RenderableContainer* pTemp = dynamic_cast<RenderableContainer*>(pContainer);

	if (pTemp)
	{
		//	リストを返却する
		_pRenderableBank->Return(pTemp);
	}
	else
	{
		//	リストを返却する
		StandardRenderableContainer* p = (StandardRenderableContainer*)(pContainer);
		_pStandardBank->Return(p);
	}
}
