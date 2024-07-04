//----------------------------------------------------------
// file name: RenderableCollection.h
//
// memo: 描画実行オブジェクト群の格納、制御管理
//----------------------------------------------------------

#ifndef	__RENDERABLE_COLLECTION_H
#define	__RENDERABLE_COLLECTION_H

#include "IRenderableCollection.h"
#include "RenderableContainer.h"
#include "StandardRenderableContainer.h"

namespace gift
{

	namespace Private
	{

		namespace Renderable
		{

//----------------------------------------------------------
// name: gift::Private::Renderable::RenderableCollection
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableCollection is interface
//
// memo: 描画実行に関する登録オブジェクト群の生成管理
//----------------------------------------------------------
class	RenderableCollection
	: public gift::Renderable::IRenderableCollection
{
private:
	//----------------------------------------------------------
	// name: gift::Private::Renderable::RenderableCollection::RenderableFactory
	//
	// attrib: private nested function object
	//
	// memo: 描画実行に関する各オブジェクト生成方法
	//----------------------------------------------------------
	class	RenderableFactory
	{
	public:
		//----------------------------------------------------------
		//	描画実行管理オブジェクト格納連結用オブジェクトの生成
		//
		// parameter: (in)(out)IRenderableComponent*& pValue … 生成結果格納先
		//
		// return: IRenderableComponent*& … 生成結果への参照
		//----------------------------------------------------------
		gift::Renderable::IRenderableComponent*& Create(gift::Renderable::IRenderableComponent*& pValue)
		{
			pValue = new RenderableComponent();

			return pValue;
		};

		//----------------------------------------------------------
		//	描画実行管理オブジェクトの生成
		//
		// parameter: (in)(out)RenderableContainer*& pValue … 生成結果格納先
		//
		// return: RenderableContainer*& … 生成結果への参照
		//----------------------------------------------------------
		RenderableContainer*& Create(RenderableContainer*& pValue)
		{
			pValue = new RenderableContainer();

			return pValue;
		};

		//----------------------------------------------------------
		//	レンダーステートを保持した描画実行管理オブジェクトの生成
		//
		// parameter: (in)(out)RenderableContainer*& pValue … 生成結果格納先
		//
		// return: RenderableContainer*& … 生成結果への参照
		//----------------------------------------------------------
		StandardRenderableContainer*& Create(StandardRenderableContainer*& pValue)
		{
			pValue = new StandardRenderableContainer();

			return pValue;
		}

		//----------------------------------------------------------
		//	描画実行管理オブジェクト格納連結用オブジェクトの破棄
		//
		// parameter: (in)(out)IRenderableComponent*& pValue … 破棄するデータ
		//
		// return: IRenderableComponent*& … 破棄結果への参照
		//----------------------------------------------------------
		gift::Renderable::IRenderableComponent*& Delete(gift::Renderable::IRenderableComponent*& pValue)
		{
			delete pValue;

			pValue = NULL;

			return pValue;
		};

		//----------------------------------------------------------
		//	描画実行結果オブジェクトの破棄
		//
		// parameter: (in)(out)RenderableContainer*& pValue … 破棄するデータ
		//
		// return: RenderableContainer*& … 破棄結果への参照
		//----------------------------------------------------------
		RenderableContainer*& Delete(RenderableContainer*& pValue)
		{
			delete pValue;

			pValue = NULL;

			return pValue;
		};

		//----------------------------------------------------------
		//	レンダーステートを保持した描画実行管理オブジェクトの破棄
		//
		// parameter: (in)(out)StandardRenderableContainer*& pValue … 破棄するデータ
		//
		// return: StandardRenderableContainer*& … 破棄結果への参照
		//----------------------------------------------------------
		StandardRenderableContainer*& Delete(StandardRenderableContainer*& pValue)
		{
			delete pValue;

			pValue = NULL;

			return pValue;
		};
	};

private:
	ObjectBank<gift::Renderable::IRenderableComponent*>*	_pComponentBank;
	ObjectBank<RenderableContainer*>*	_pRenderableBank;
	ObjectBank<StandardRenderableContainer*>*	_pStandardBank;

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	RenderableCollection(void);

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~RenderableCollection(void);

	//----------------------------------------------------------
	//	描画呼び出し制御格納コンテナを連結するコンポーネントを取得
	//
	// return: IRenderableComponent* … コンテナ格納コンポーネント
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* OrderComponent(void);

	//----------------------------------------------------------
	//	描画呼び出し管理オブジェクトを取得
	//
	// return: IRenderableContainer* … 描画呼び出し管理オブジェクト
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableContainer* OrderContainer(void);

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
	gift::Renderable::IRenderableContainer* OrderContainer(RenderStates& state, bool isMyStates);

	//----------------------------------------------------------
	//	描画制御格納コンテナ連結コンポーネントを返却する
	//
	// parameter: (in)IRenderableComponent pComponent* … 返却するオブジェクトへのポインタ
	//
	// attrib: override
	//----------------------------------------------------------
	void ReturnComponent(gift::Renderable::IRenderableComponent* pComponent);

	//----------------------------------------------------------
	//	描画呼び出し管理オブジェクトを返却する
	//
	// parameter: (in)IRenderableContainer* pContainer … 返却するオブジェクトへのポインタ
	//
	// attrib: override
	//----------------------------------------------------------
	void ReturnContainer(gift::Renderable::IRenderableContainer* pContainer);
};

};//namespace Renderable
};//namespace Private
};//namespace gift

#endif
