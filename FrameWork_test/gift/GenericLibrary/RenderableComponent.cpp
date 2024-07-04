//----------------------------------------------------------
// file name: RenderableComponent.cpp
//
// memo: 描画実行管理オブジェクトを描画順番に連結管理、実行する
//----------------------------------------------------------

#include <stdio.h>
#include "RenderableComponent.h"

using namespace gift;
using namespace gift::Renderable;
using namespace gift::Private;
using namespace gift::Private::Renderable;

//----------------------------------------------------------
//	RenderableComponent の静的メンバ変数の初期化
//----------------------------------------------------------
ObjectBank<IRenderableComponent*>* RenderableComponent::s_pBank = NULL;

//----------------------------------------------------------
//	コンストラクタ
//----------------------------------------------------------
RenderableComponent::RenderableComponent(void)
: _pRenderable(NULL), _sort(false), _used(false),
	_finish(true), _isDisposable(false), _counter(0)
{
	_pNext[BACK] = NULL;
	_pNext[MAIN] = &_dummyTop;
	_pNext[NEXT] = NULL;

	_dummyTop.SetNext(&_dummyLast);
	_dummyLast.SetBack(&_dummyTop);
}

//----------------------------------------------------------
//	デストラクタ
//----------------------------------------------------------
RenderableComponent::~RenderableComponent(void)
{
	this->Initialize();
}

//----------------------------------------------------------
//	引数のコンテナを自身に連結させる
//
// parameter: (in)IRenderableComponent* pComponent … 連結さえるコンテナ
//----------------------------------------------------------
void RenderableComponent::Connect(IRenderableComponent* pComponent)
{
	IRenderableComponent* pTemp = _dummyLast.GetBack();

	//	末端（ダミーの手前）に相互連結
	pComponent->SetNext(&_dummyLast);
	_dummyLast.SetBack(pComponent);

	//	新しいコンテナを本線の末端に相互連結
	pComponent->SetBack(pTemp);
	pTemp->SetNext(pComponent);
}

//----------------------------------------------------------
//	自身を自身が連結するオブジェクト群から、分離する
//----------------------------------------------------------
void RenderableComponent::Disconnect(void)
{
	//	自身が誰かの後ろに連結されている
	if (_pNext[BACK])
	{
		//	自身の前のコンテナを後ろのコンテナと連結させる
		_pNext[BACK]->SetNext(_pNext[NEXT]);
	}

	//	自身が誰かを後ろに連結させている
	if (_pNext[NEXT])
	{
		//	自身の後ろのコンテナを前のコンテナと連結させる
		_pNext[NEXT]->SetBack(_pNext[BACK]);
	}

	_pNext[BACK] = NULL;
	_pNext[NEXT] = NULL;


	//	自身が管理していた描画オブジェクト群を破棄する
	IRenderableComponent* pTemp = _pNext[MAIN]->GetNext();

	//	末端まで走査
	while (pTemp != (&_dummyLast))
	{
		//	連結オブジェクト群から分離させる
		pTemp->Disconnect();

		//	ユーザーが管理していない
		if (!pTemp->IsUsed())
		{
			//	生成時の状態に戻す
			pTemp->Initialize();

			//	コンテナ倉庫にコンテナを返却する
			RenderableComponent::s_pBank->Return(pTemp);
		}

		//	次のコンテナを走査
		pTemp = _pNext[MAIN]->GetNext();
	}

	_dummyTop.SetNext(&_dummyLast);
	_dummyLast.SetBack(&_dummyTop);
}

//----------------------------------------------------------
//	コンテナが発行された状態に戻す
//----------------------------------------------------------
void RenderableComponent::Initialize(void)
{
	_sort = false;
	_used = false;
	_finish = true;
	_counter = 0;

	//	破棄を任されている
	if (_isDisposable)
	{
		//	破棄されていない
		if (_pRenderable)
		{
			delete _pRenderable;
		}
	}

	//	各連結状態を破棄する
	this->Disconnect();
}

//----------------------------------------------------------
//	格納している描画オブジェクトを実行する
//
// return: IRenderableComponent* … 次に実行するコンテナへのポインタ
//----------------------------------------------------------
IRenderableComponent* RenderableComponent::Execute(void)
{
	IRenderableComponent* pTemp = NULL;

	switch	(_counter)
	{
	//	はじめの実行
	case 0:
		//	自身の格納する描画リストを転送
		pTemp = _pNext[MAIN]->GetNext();
		break;

	//	二回目の実行
	case 1:
		//	自身が連結する次のコンテナを転送
		pTemp = _pNext[NEXT];
		break;

	//	三回目の実行
	case 2:
		//	自身が連結する前のコンテナを転送
		pTemp = _pNext[BACK];
		break;

	default:
		break;
	}

	_counter = (_counter + 1) % 3;

	return pTemp;
}
