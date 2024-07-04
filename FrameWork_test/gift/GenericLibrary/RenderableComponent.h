//----------------------------------------------------------
// file name: RenderableComponent.h
//
// memo: 描画呼び出しコンテナ連結用クラス
//----------------------------------------------------------

#ifndef	__RENDERABLE_COMPONENT_H
#define	__RENDERABLE_COMPONENT_H

#include "IComponent.h"
#include "IRenderableContainer.h"
#include "ObjectBank.h"

namespace gift
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Renderable::IRenderableComponent
//
// attrib: interface
//
// memo: 描画管理オブジェクトを描画順に連結管理するためのインターフェース
//----------------------------------------------------------
class	IRenderableComponent
{
public:
	virtual ~IRenderableComponent(void) {};

	//----------------------------------------------------------
	//	自身が格納しているオブジェクト群のソートの有無
	//
	// return: bool … ソートの有無
	//　　　　true … ソートを行う
	//----------------------------------------------------------
	virtual bool IsSort(void) = 0;

	//----------------------------------------------------------
	//	格納しているオブジェクト群をソートさせるかの有無
	//
	// parameter: (in)bool enable … ソートの有無
	//
	// memo: true は、ソートを行うようにさせる
	//----------------------------------------------------------
	virtual void SetSort(bool enable) = 0;

	//----------------------------------------------------------
	//	ユーザーが所持しているか、システムにコンポーネントを返却の有無
	//
	// return: bool … システムにオブジェクトの返却の有無
	//
	// memo: true は、コンポーネントをユーザーが保持していることを指し、
	//　　　システムには、返却されない。
	//----------------------------------------------------------
	virtual bool IsUsed(void) = 0;

	//----------------------------------------------------------
	//	ユーザーが所持しているかの有無
	//
	// parameter: (in)bool UserUses … ユーザーが所持しているかの有無
	//
	// memo: false は、ユーザーが所持していないことを指し、
	//　　　使われなくなったときに、システムに返却され利用できなくなる
	//----------------------------------------------------------
	virtual void SetUsed(bool UserUses) = 0;

	//----------------------------------------------------------
	//	オブジェクトの連結状態を維持させるかの有無
	//
	// return: bool … 連結状態維持の有無
	//
	// memo: true は、連結状態を破棄する。破棄後、システムに返却され利用不可
	//----------------------------------------------------------
	virtual bool Finish(void) = 0;

	//----------------------------------------------------------
	//	オブジェクトの連結状態を維持するかの有無を設定
	//
	// parameter: (in)bool enable … 描画終了時に連結状態をどうするか
	//
	// memo: true のとき、描画終了時に連結状態を破棄し、システムに返却します
	//----------------------------------------------------------
	virtual void SetFinish(bool enable) = 0;

	//----------------------------------------------------------
	//	描画管理オブジェクトを登録する
	//
	// parameter: (in)IRenderableContainer* pContainer … 実行するオブジェクト
	// parameter: (in)bool isDisposable = false … 登録オブジェクト破棄の有無
	//
	// memo: isDisposable を true にすると、描画処理終了後に pContainer
	//　　　を破棄します。
	//----------------------------------------------------------
	virtual void Register(IRenderableContainer* pContainer,
		bool isDisposable = false) = 0;

	//----------------------------------------------------------
	//	格納している描画管理オブジェクトを参照
	//
	// return: IRenderableContainer* … 描画実行管理オブジェクトへのポインタ
	//----------------------------------------------------------
	virtual IRenderableContainer* GetRenderable(void) = 0;

	//----------------------------------------------------------
	//	引数のコンテナを自身に連結させる
	//
	// parameter: (in)IRenderableComponent* pComponent … 連結さえるコンテナ
	//----------------------------------------------------------
	virtual void Connect(IRenderableComponent* pComponent) = 0;

	//----------------------------------------------------------
	//	自身の連結している次のコンテナオブジェクトを参照
	//
	// return: IRenderableComponent* … 次のオブジェクト
	//----------------------------------------------------------
	virtual IRenderableComponent* GetNext(void) = 0;

	//----------------------------------------------------------
	//	自身の連結する次のコンテナオブジェクトを登録する
	//
	// parameter: (in)IRenderableComponent* pComponent … 登録するコンテナ
	//----------------------------------------------------------
	virtual void SetNext(IRenderableComponent* pComponent) = 0;

	//----------------------------------------------------------
	//	自身の連結している前のコンテナオブジェクトを参照
	//
	// return: IRenderableComponent* … 前のオブジェクト
	//----------------------------------------------------------
	virtual IRenderableComponent* GetBack(void) = 0;

	//----------------------------------------------------------
	//	自身の連結する前のコンテナオブジェクトを登録する
	//
	// parameter: (in)IRenderableComponent* pComponent … 登録するコンテナ
	//----------------------------------------------------------
	virtual void SetBack(IRenderableComponent* pComponent) = 0;

	//----------------------------------------------------------
	//	自身を自身が連結するオブジェクト群から、分離する
	//----------------------------------------------------------
	virtual void Disconnect(void) = 0;

	//----------------------------------------------------------
	//	コンテナが発行された状態に戻す
	//----------------------------------------------------------
	virtual void Initialize(void) = 0;

	//----------------------------------------------------------
	//	格納している描画オブジェクトを実行する
	//
	// return: IRenderableComponent* … 次に実行するコンテナへのポインタ
	//----------------------------------------------------------
	virtual IRenderableComponent* Execute(void) = 0;
};

};//namespace Renderable

namespace Private
{

	namespace Renderable
	{

//----------------------------------------------------------
// name: gift::Private::Renderable::DummyRenderableComponent
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableComponent is interface
//
// memo: 描画管理オブジェクトを連結管理するための末端ダミーオブジェクト
//----------------------------------------------------------
class	DummyRenderableComponent
	: public gift::Renderable::IRenderableComponent
{
private:
	gift::Renderable::IRenderableComponent*	_pNext;
	gift::Renderable::IRenderableComponent*	_pBack;

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	DummyRenderableComponent(void)
		: _pNext(NULL), _pBack(NULL)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~DummyRenderableComponent(void)
	{
	};

	//----------------------------------------------------------
	//	自身が格納しているオブジェクト群のソートの有無
	//
	// return: bool … ソートの有無
	//　　　　true … ソートを行う
	//
	// attrib: override
	//----------------------------------------------------------
	bool IsSort(void)
	{
		return false;
	};

	//----------------------------------------------------------
	//	格納しているオブジェクト群をソートさせるかの有無
	//
	// parameter: (in)bool enable … ソートの有無
	//
	// memo: true は、ソートを行うようにさせる
	//
	// attrib: override
	//----------------------------------------------------------
	void SetSort(bool enable)
	{
	};

	//----------------------------------------------------------
	//	ユーザーが所持しているか、システムにコンポーネントを返却の有無
	//
	// return: bool … システムにオブジェクトの返却の有無
	//
	// memo: true は、コンポーネントをユーザーが保持していることを指し、
	//　　　システムには、返却されない。
	//
	// attrib: override
	//----------------------------------------------------------
	bool IsUsed(void)
	{
		return true;
	};

	//----------------------------------------------------------
	//	ユーザーが所持しているかの有無
	//
	// parameter: (in)bool UserUses … ユーザーが所持しているかの有無
	//
	// memo: false は、ユーザーが所持していないことを指し、
	//　　　使われなくなったときに、システムに返却され利用できなくなる
	//
	// attrib: override
	//----------------------------------------------------------
	void SetUsed(bool UserUses)
	{
	};

	//----------------------------------------------------------
	//	オブジェクトの連結状態を維持させるかの有無
	//
	// return: bool … 連結状態維持の有無
	//
	// memo: true は、連結状態を破棄する。破棄後、システムに返却され利用不可
	//
	// attrib: override
	//----------------------------------------------------------
	bool Finish(void)
	{
		return false;
	};

	//----------------------------------------------------------
	//	オブジェクトの連結状態を維持するかの有無を設定
	//
	// parameter: (in)bool enable … 描画終了時に連結状態をどうするか
	//
	// memo: true のとき、描画終了時に連結状態を破棄し、システムに返却します
	//
	// attrib: override
	//----------------------------------------------------------
	void SetFinish(bool enable)
	{
	};

	//----------------------------------------------------------
	//	描画管理オブジェクトを登録する
	//
	// parameter: (in)IRenderableContainer* pContainer … 実行するオブジェクト
	// parameter: (in)bool isDisposable = false … 登録オブジェクト破棄の有無
	//
	// memo: isDisposable を true にすると、描画処理終了後に pContainer
	//　　　を破棄します。
	//----------------------------------------------------------
	void Register(gift::Renderable::IRenderableContainer* pContainer,
		bool isDisposable = false)
	{
	};

	//----------------------------------------------------------
	//	格納している描画管理オブジェクトを参照
	//
	// return: IRenderableContainer* … 描画実行管理オブジェクトへのポインタ
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableContainer* GetRenderable(void)
	{
		return NULL;
	};

	//----------------------------------------------------------
	//	引数のコンテナを自身に連結させる
	//
	// parameter: (in)IRenderableComponent* pComponent … 連結さえるコンテナ
	//
	// attrib: override
	//----------------------------------------------------------
	void Connect(gift::Renderable::IRenderableComponent* pComponent)
	{
	};

	//----------------------------------------------------------
	//	自身の連結している次のコンテナオブジェクトを参照
	//
	// return: IRenderableComponent* … 次のオブジェクト
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* GetNext(void)
	{
		return _pNext;
	};

	//----------------------------------------------------------
	//	自身の連結する次のコンテナオブジェクトを登録する
	//
	// parameter: (in)IRenderableComponent* pComponent … 登録するコンテナ
	//
	// attrib: override
	//----------------------------------------------------------
	void SetNext(gift::Renderable::IRenderableComponent* pComponent)
	{
		_pNext = pComponent;
	};

	//----------------------------------------------------------
	//	自身の連結している前のコンテナオブジェクトを参照
	//
	// return: IRenderableComponent* … 前のオブジェクト
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* GetBack(void)
	{
		return _pBack;
	};

	//----------------------------------------------------------
	//	自身の連結する前のコンテナオブジェクトを登録する
	//
	// parameter: (in)IRenderableComponent* pComponent … 登録するコンテナ
	//
	// attrib: override
	//----------------------------------------------------------
	void SetBack(gift::Renderable::IRenderableComponent* pComponent)
	{
		_pBack = pComponent;
	};

	//----------------------------------------------------------
	//	コンテナが発行された状態に戻す
	//
	// attrib: override
	//----------------------------------------------------------
	void Initialize(void)
	{
		_pBack = NULL;
		_pNext = NULL;
	};

	//----------------------------------------------------------
	//	自身を自身が連結するオブジェクト群から、分離する
	//
	// attrib: override
	//----------------------------------------------------------
	void Disconnect(void)
	{
	};

	//----------------------------------------------------------
	//	格納している描画オブジェクトを実行する
	//
	// return: IRenderableComponent* … 次に実行するコンテナへのポインタ
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* Execute(void)
	{
		return _pBack;
	};
};


//----------------------------------------------------------
// name: gift::Private::Renderable::RenderableComponent
//
// attrib: sub class
//
// base: gift::Renderable::IRenderableComponent is interface
//
// memo: 描画管理オブジェクトを描画順に連結管理する
//----------------------------------------------------------
class	RenderableComponent
	: public gift::Renderable::IRenderableComponent
{
public:
	enum
	{
		BACK = 0,
		MAIN = 1,
		NEXT = 2,
	};

private:
	gift::Renderable::IRenderableContainer*	_pRenderable;	//	描画実行管理オブジェクト

	bool					_sort;			//	ソートの有無
	bool					_used;			//	システム返還の有無
	bool					_finish;		//	連結解除の有無
	bool					_isDisposable;	//	使い捨てオブジェクトの有無
	int						_counter;		//	次に参照する連結先番号
	gift::Renderable::IRenderableComponent*	_pNext[3];		//	連結するためのポインタ
	DummyRenderableComponent	_dummyTop;	//	連結の先頭用空データ
	DummyRenderableComponent	_dummyLast;	//	連結の末端用空データ

	static ObjectBank<gift::Renderable::IRenderableComponent*>*	s_pBank;

public:
	//----------------------------------------------------------
	//	描画順に格納するコンポーネントの在庫管理オブジェクトの登録
	//
	// parameter: (in)ObjectBank<IRenderableComponent*>* pBank … 在庫管理
	//
	// memo: 破棄は行わない（別のオブジェクトが破棄を管理している）
	//----------------------------------------------------------
	static void sRegister(ObjectBank<gift::Renderable::IRenderableComponent*>* pBank)
	{
		s_pBank = pBank;
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	RenderableComponent(void);

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~RenderableComponent(void);

	//----------------------------------------------------------
	//	自身が格納しているオブジェクト群のソートの有無
	//
	// return: bool … ソートの有無
	//　　　　true … ソートを行う
	//
	// attrib: override
	//----------------------------------------------------------
	bool IsSort(void)
	{
		return _sort;
	};

	//----------------------------------------------------------
	//	格納しているオブジェクト群をソートさせるかの有無
	//
	// parameter: (in)bool enable … ソートの有無
	//
	// memo: true は、ソートを行うようにさせる
	//
	// attrib: override
	//----------------------------------------------------------
	void SetSort(bool enable)
	{
		_sort = enable;
	};

	//----------------------------------------------------------
	//	ユーザーが所持しているか、システムにコンポーネントを返却の有無
	//
	// return: bool … システムにオブジェクトの返却の有無
	//
	// memo: true は、コンポーネントをユーザーが保持していることを指し、
	//　　　システムには、返却されない。
	//
	// attrib: override
	//----------------------------------------------------------
	bool IsUsed(void)
	{
		return _used;
	};

	//----------------------------------------------------------
	//	ユーザーが所持しているかの有無
	//
	// parameter: (in)bool UserUses … ユーザーが所持しているかの有無
	//
	// memo: false は、ユーザーが所持していないことを指し、
	//　　　使われなくなったときに、システムに返却され利用できなくなる
	//
	// attrib: override
	//----------------------------------------------------------
	void SetUsed(bool UserUses)
	{
		_used = UserUses;
	};

	//----------------------------------------------------------
	//	オブジェクトの連結状態を維持させるかの有無
	//
	// return: bool … 連結状態維持の有無
	//
	// memo: true は、連結状態を破棄する。破棄後、システムに返却され利用不可
	//
	// attrib: override
	//----------------------------------------------------------
	bool Finish(void)
	{
		return _finish;
	};

	//----------------------------------------------------------
	//	オブジェクトの連結状態を維持するかの有無を設定
	//
	// parameter: (in)bool enable … 描画終了時に連結状態をどうするか
	//
	// memo: true のとき、描画終了時に連結状態を破棄し、システムに返却します
	//
	// attrib: override
	//----------------------------------------------------------
	void SetFinish(bool enable)
	{
		_finish = enable;
	};

	//----------------------------------------------------------
	//	描画管理オブジェクトを登録する
	//
	// parameter: (in)IRenderableContainer* pContainer … 実行するオブジェクト
	// parameter: (in)bool isDisposable = false … 登録オブジェクト破棄の有無
	//
	// memo: isDisposable を true にすると、描画処理終了後に pContainer
	//　　　を破棄します。
	//
	// attrib: override
	//----------------------------------------------------------
	void Register(gift::Renderable::IRenderableContainer* pContainer,
		bool isDisposable = false)
	{
		_pRenderable = pContainer;
		_isDisposable = isDisposable;
	};

	//----------------------------------------------------------
	//	格納している描画管理オブジェクトを参照
	//
	// return: IRenderableContainer* … 描画実行管理オブジェクトへのポインタ
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableContainer* GetRenderable(void)
	{
		return _pRenderable;
	};

	//----------------------------------------------------------
	//	引数のコンテナを自身に連結させる
	//
	// parameter: (in)IRenderableComponent* pComponent … 連結さえるコンテナ
	//
	// attrib: override
	//----------------------------------------------------------
	void Connect(gift::Renderable::IRenderableComponent* pComponent);

	//----------------------------------------------------------
	//	自身の連結している次のコンテナオブジェクトを参照
	//
	// return: IRenderableComponent* … 次のオブジェクト
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* GetNext(void)
	{
		return _pNext[NEXT];
	};

	//----------------------------------------------------------
	//	自身の連結する次のコンテナオブジェクトを登録する
	//
	// parameter: (in)IRenderableComponent* pComponent … 登録するコンテナ
	//
	// attrib: override
	//----------------------------------------------------------
	void SetNext(gift::Renderable::IRenderableComponent* pComponent)
	{
		_pNext[NEXT] = pComponent;
	};

	//----------------------------------------------------------
	//	自身の連結している前のコンテナオブジェクトを参照
	//
	// return: IRenderableComponent* … 前のオブジェクト
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* GetBack(void)
	{
		return _pNext[BACK];
	};

	//----------------------------------------------------------
	//	自身の連結する前のコンテナオブジェクトを登録する
	//
	// parameter: (in)IRenderableComponent* pComponent … 登録するコンテナ
	//
	// attrib: override
	//----------------------------------------------------------
	void SetBack(gift::Renderable::IRenderableComponent* pComponent)
	{
		_pNext[BACK] = pComponent;
	};

	//----------------------------------------------------------
	//	自身を自身が連結するオブジェクト群から、分離する
	//
	// attrib: override
	//----------------------------------------------------------
	void Disconnect(void);

	//----------------------------------------------------------
	//	コンテナが発行された状態に戻す
	//
	// attrib: override
	//----------------------------------------------------------
	void Initialize(void);

	//----------------------------------------------------------
	//	格納している描画オブジェクトを実行する
	//
	// return: IRenderableComponent* … 次に実行するコンテナへのポインタ
	//
	// attrib: override
	//----------------------------------------------------------
	gift::Renderable::IRenderableComponent* Execute(void);
};

};//namespace Renderable
};//namespace Private
};//namespace gift

#endif
