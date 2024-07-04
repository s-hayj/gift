//----------------------------------------------------------
// file name: ObjectBank.h
//
// memo: オブジェクトのストックを管理
//----------------------------------------------------------

#ifndef	__OBJECT_BANK_H
#define	__OBJECT_BANK_H

#include "NewDelManager.h"
#include "IComponent.h"

namespace gift
{
	
//----------------------------------------------------------
// name: gift::ObjectBank
//
// attrib: template final class
//
// typename: T … 生成管理するオブジェクトの型
//
// memo: オブジェクトの生成ストック管理
//----------------------------------------------------------
template<class T>
class	ObjectBank
{
private:
	//----------------------------------------------------------
	// name: gift::ObjectBank::List
	//
	// attrib: private template final class
	//
	// memo: 生成したオブジェクトの管理用単方向リスト
	//----------------------------------------------------------
	template<class U>
	class	List
	{
	private:
		U	_obj;			//	格納するオブジェクト

		List<U>*	_pNext;	//	次の連結先へのポインタ

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//----------------------------------------------------------
		List(void)
			: _pNext(NULL)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//----------------------------------------------------------
		~List(void)
		{
		};

		//----------------------------------------------------------
		//	格納オブジェクトを転送
		//
		// parameter: (in)U& obj … 格納させるオブジェクトへの参照
		//----------------------------------------------------------
		void Set(U& obj)
		{
			_obj = obj;
		};

		//----------------------------------------------------------
		//	格納オブジェクトを取得
		//
		// return: U& … 格納オブジェクトへの参照
		//----------------------------------------------------------
		U& Get(void)
		{
			return _obj;
		};

		//----------------------------------------------------------
		//	次の連結先を取得
		//
		// return: List<U>* … 連結先のコンポーネント
		//----------------------------------------------------------
		List<U>* Next(void)
		{
			return _pNext;
		};

		//----------------------------------------------------------
		//	コンポーネントを連結させる
		//
		// parameter: (in)List<U>* pComponent … 連結させるコンポーネント
		//----------------------------------------------------------
		void Connect(List<U>* pComponent)
		{
			_pNext = pComponent;
		};
	};

private:
	List<T>	_ObjectStock;	//	オブジェクトの在庫
	List<T>	_ListStock;		//	オブジェクトを管理するリストの在庫

	NewDelManager<T>	_ObjectManager;	//	格納オブジェクトの生成、破棄管理

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	ObjectBank(void)
	{
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)NewDelManager<T>& manager … オブジェクトの生成、破棄方法
	//----------------------------------------------------------
	ObjectBank(NewDelManager<T>& manager)
		: _ObjectManager(manager)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~ObjectBank(void)
	{
		//	在庫のリストならびに、オブジェクトを破棄する
		this->Release();
	};

	//----------------------------------------------------------
	//	オブジェクトの注文を受ける
	//
	// return: T& … 発行されたオブジェクトへの参照
	//----------------------------------------------------------
	T& Order(void)
	{
		//	オブジェクトを出荷する
		return this->ObjectOrder();
	};

	//----------------------------------------------------------
	//	返却されたオブジェクトを受け取る
	//
	// parameter: (in)T& value … 返却されたオブジェクトへの参照
	//----------------------------------------------------------
	void Return(T& value)
	{
		//	オブジェクトを返却する
		this->ObjectReturn(value);
	};

	//----------------------------------------------------------
	//	在庫管理しているオブジェクトの生成、破棄管理方法を登録する
	//
	// parameter: (in)NewDelManager<T>& manager … 生成破棄管理オブジェクト
	//----------------------------------------------------------
	void Register(NewDelManager<T>& manager)
	{
		_ObjectManager = manager;
	};

	//----------------------------------------------------------
	//	リストならびに、在庫のオブジェクトを破棄する
	//----------------------------------------------------------
	void Release(void)
	{
		List<T>* pTemp = NULL;

		//	在庫オブジェクトを破棄する
		pTemp = _ObjectStock.Next();

		//	在庫が無くなるまで
		while	(pTemp != NULL)
		{
			_ObjectStock.Connect(pTemp->Next());

			//	在庫の破棄処理実行
			_ObjectManager.Release(pTemp->Get());

			//	格納していたリストの破棄
			delete pTemp;

			//	次の在庫を破棄する
			pTemp = _ObjectStock.Next();
		}

		//	在庫のリストを破棄する
		pTemp = _ListStock.Next();

		//	在庫が無くなるまで
		while	(pTemp != NULL)
		{
			_ListStock.Connect(pTemp->Next());

			//	リストの破棄
			delete pTemp;

			//	次の在庫を破棄する
			pTemp = _ListStock.Next();
		}
	};

private:
	//----------------------------------------------------------
	//	コピーコンストラクタの禁止
	//----------------------------------------------------------
	ObjectBank(ObjectBank& bank)
	{
	};

	ObjectBank(ObjectBank* pBank)
	{
	};

	//----------------------------------------------------------
	//	オブジェクトの発注を受ける
	//
	// return: T& … 発行するオブジェクトへの参照
	//----------------------------------------------------------
	T& ObjectOrder(void)
	{
		List<T>* pTemp = _ObjectStock.Next();

		//	在庫を確かめる
		if (pTemp)
		{
			//	在庫リストから分離させる
			_ObjectStock.Connect(pTemp->Next());

			//	オブジェクトを格納していたリストを返却する
			this->ListReturn(pTemp);

			//	オブジェクトを出荷する
			return pTemp->Get();
		}
		//	在庫が無い
		else
		{
			//	新しいリストを発注する
			pTemp = this->ListOrder();

			//	リストを返却する
			this->ListReturn(pTemp);

			//	オブジェクトを初期化後、出荷
			return _ObjectManager.Initialize(pTemp->Get());
		}
	};

	//----------------------------------------------------------
	//	オブジェクトの返却を受ける
	//
	// parameter: (in)T& obj … 返却されたオブジェクトへの参照
	//----------------------------------------------------------
	void ObjectReturn(T& obj)
	{
		//	オブジェクトを格納するリストを発注する
		List<T>* pTemp = this->ListOrder();

		//	オブジェクトを格納する
		pTemp->Set(obj);

		//	オブジェクトの在庫として格納する
		pTemp->Connect(_ObjectStock.Next());
		_ObjectStock.Connect(pTemp);
	};

	//----------------------------------------------------------
	//	リストの発注を受ける
	//
	// return: List<T>* … 発行するリストへのポインタ
	//----------------------------------------------------------
	List<T>* ListOrder(void)
	{
		List<T>* pTemp = _ListStock.Next();

		//	在庫を確かめる
		if (pTemp)
		{
			//	在庫リストから分離させる
			_ListStock.Connect(pTemp->Next());
		}
		//	在庫が無い
		else
		{
			//	リストを新たに生成する
			pTemp = new ObjectBank<T>::List<T>();
		}

		//	リストを発行する
		return pTemp;
	};

	//----------------------------------------------------------
	//	リストの返却を受ける
	//
	// parameter: (in)List<T>* pList … 返却されたリストへのポインタ
	//----------------------------------------------------------
	void ListReturn(List<T>* pList)
	{
		//	リストの在庫リストに連結
		pList->Connect(_ListStock.Next());
		_ListStock.Connect(pList);
	};
};

};//namespace gift

#endif
