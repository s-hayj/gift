//----------------------------------------------------------
//	@file	ObjectBank.h
//
//	@memo	オブジェクトのストックを管理
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__OBJECT_BANK_H
#define	__OBJECT_BANK_H

#include "NewDelManager.h"
#include "IComponent.h"

	
//----------------------------------------------------------
//	@name	ObjectBank
//
//	@memo	オブジェクトの生成ストック管理
//
//	@attrib	public template final class
//
//	@type	T	生成管理するオブジェクトの型
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
template<class T>
class	ObjectBank
{
private:
	//----------------------------------------------------------
	//	@name	ObjectBank::List
	//
	//	@memo	生成したオブジェクトの管理用単方向リスト
	//
	//	@attrib	private template final class
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template<class U>
	class	List
	{
	private:
		U			m_obj;		//	格納するオブジェクト

		List<U>*	m_pNext;	//	次の連結先へのポインタ

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	ObjectBank::List::List
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		List(void)
			: m_pNext( NULL )
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	ObjectBank::List::~List
		//
		//	@attrib	public
		//----------------------------------------------------------
		~List(void)
		{
		};

		//----------------------------------------------------------
		//	格納オブジェクトを転送
		//
		//	@name	ObjectBank::List::Set
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	(in)obj	格納させるオブジェクトへの参照
		//
		//	@return	none
		//----------------------------------------------------------
		void Set( U& obj )
		{
			m_obj = obj;
		};

		//----------------------------------------------------------
		//	格納オブジェクトを取得
		//
		//	@name	ObjectBank::List::Get
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	U&	格納オブジェクトへの参照
		//----------------------------------------------------------
		U& Get(void)
		{
			return m_obj;
		};

		//----------------------------------------------------------
		//	次の連結先を取得
		//
		//	@name	ObjectBank::List::Next
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	List<U>*	連結先のコンポーネント
		//----------------------------------------------------------
		List<U>* Next(void)
		{
			return m_pNext;
		};

		//----------------------------------------------------------
		//	コンポーネントを連結させる
		//
		//	@name	ObjectBank::List::Connect
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	(in)pComponent	連結させるコンポーネント
		//
		//	@return	none
		//----------------------------------------------------------
		void Connect( List<U>* pComponent )
		{
			m_pNext = pComponent;
		};
	};

private:
	List<T>			m_ObjectStock;	//	オブジェクトの在庫
	List<T>			m_ListStock;	//	オブジェクトを管理するリストの在庫

	NewDelManager<T>	m_ObjectManager;	//	格納オブジェクトの生成、破棄管理

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	ObjectBank::ObjectBank
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	ObjectBank(void)
	{
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	ObjectBank::ObjectBank
	//
	//	@attrib	public
	//
	//	@param	(in)manager	オブジェクトの生成、破棄方法
	//----------------------------------------------------------
	ObjectBank( NewDelManager<T>& manager )
		: m_ObjectManager( manager )
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	ObjectBank::~ObjectBank
	//
	//	@attrib	public
	//----------------------------------------------------------
	~ObjectBank(void)
	{
		//	在庫のリストならびに、オブジェクトを破棄する
		this->Release();
	};

	//----------------------------------------------------------
	//	オブジェクトの注文を受ける
	//
	//	@name	ObjectBank::Order
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	T&	発行されたオブジェクトへの参照
	//----------------------------------------------------------
	T& Order(void)
	{
		//	オブジェクトを出荷する
		return this->ObjectOrder();
	};

	//----------------------------------------------------------
	//	返却されたオブジェクトを受け取る
	//
	//	@name	ObjectBank::Restore
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)value	返却されたオブジェクトへの参照
	//
	//	@return	none
	//----------------------------------------------------------
	void Restore(T& value)
	{
		//	オブジェクトを返却する
		this->ObjectRestore( value );
	};

	//----------------------------------------------------------
	//	在庫管理しているオブジェクトの生成、破棄管理方法を登録する
	//
	//	@name	ObjectBank::Register
	//
	//	@memo	登録元（引数のオブジェクト）は、生成破棄処理が行えなくなる
	//
	//	@attrib	public
	//
	//	@param	(in)manager	生成、破棄方法管理オブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	void Register( NewDelManager<T>& manager )
	{
		m_ObjectManager = manager;
	};

	//----------------------------------------------------------
	//	リストならびに、在庫のオブジェクトを破棄する
	//
	//	@name	ObjectBank::Release
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Release(void)
	{
		List<T>* pTemp = NULL;

		//	在庫オブジェクトを破棄する
		pTemp = m_ObjectStock.Next();

		//	在庫が無くなるまで
		while	( pTemp != NULL )
		{
			m_ObjectStock.Connect( pTemp->Next() );

			//	在庫の破棄処理実行
			m_ObjectManager.Release( pTemp->Get() );

			//	格納していたリストの破棄
			delete pTemp;

			//	次の在庫を破棄する
			pTemp = m_ObjectStock.Next();
		}

		//	在庫のリストを破棄する
		pTemp = m_ListStock.Next();

		//	在庫が無くなるまで
		while	( pTemp != NULL )
		{
			m_ListStock.Connect( pTemp->Next() );

			//	リストの破棄
			delete pTemp;

			//	次の在庫を破棄する
			pTemp = m_ListStock.Next();
		}
	};

private:
	//----------------------------------------------------------
	//	コピーコンストラクタ
	//
	//	@name	ObjectBank::ObjectBank
	//
	//	@memo	コピーコンストラクタの禁止
	//
	//	@attrib	private
	//
	//	@param	(in)bank	コピーするオブジェクトへの参照
	//----------------------------------------------------------
	ObjectBank( ObjectBank& bank )
	{
	};

	//----------------------------------------------------------
	//	コピーコンストラクタ
	//
	//	@name	ObjectBank::ObjectBank
	//
	//	@memo	コピーコンストラクタの禁止
	//
	//	@attrib	private
	//
	//	@param	(in)pBank	コピーするオブジェクトへのポインタ
	//----------------------------------------------------------
	ObjectBank( ObjectBank* pBank )
	{
	};

	//----------------------------------------------------------
	//	オブジェクトの発注を受ける
	//
	//	@name	ObjectBank::ObjectOrder
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	none
	//
	//	@return	T&	発行するオブジェクトへの参照
	//----------------------------------------------------------
	T& ObjectOrder(void)
	{
		List<T>* pTemp = m_ObjectStock.Next();

		//	在庫を確かめる
		if ( pTemp )
		{
			//	在庫リストから分離させる
			m_ObjectStock.Connect( pTemp->Next() );

			//	オブジェクトを格納していたリストを返却する
			this->ListRestore( pTemp );

			//	オブジェクトを出荷する
			return pTemp->Get();
		}
		//	在庫が無い
		else
		{
			//	新しいリストを発注する
			pTemp = this->ListOrder();

			//	リストを返却する
			this->ListRestore( pTemp );

			//	オブジェクトを初期化後、出荷
			return m_ObjectManager.Initialize( pTemp->Get() );
		}
	};

	//----------------------------------------------------------
	//	オブジェクトの返却を受ける
	//
	//	@name	ObjectBnak::ObjectRestore
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	(in)obj	返却されたオブジェクトへの参照
	//
	//	@return	none
	//----------------------------------------------------------
	void ObjectReturn(T& obj)
	{
		//	オブジェクトを格納するリストを発注する
		List<T>* pTemp = this->ListOrder();

		//	オブジェクトを格納する
		pTemp->Set( obj );

		//	オブジェクトの在庫として格納する
		pTemp->Connect( m_ObjectStock.Next() );
		m_ObjectStock.Connect( pTemp );
	};

	//----------------------------------------------------------
	//	リストの発注を受ける
	//
	//	@name	ObjectBank::ListOrder
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	none
	//
	//	@return	List<T>*	発行するリストへのポインタ
	//----------------------------------------------------------
	List<T>* ListOrder(void)
	{
		List<T>* pTemp = m_ListStock.Next();

		//	在庫を確かめる
		if ( pTemp )
		{
			//	在庫リストから分離させる
			m_ListStock.Connect( pTemp->Next() );
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
	//	@name	ObjectBank::ListRestore
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	(in)pList	返却されたリストへのポインタ
	//
	//	@return	none
	//----------------------------------------------------------
	void ListRestore( List<T>* pList )
	{
		//	リストの在庫リストに連結
		pList->Connect( m_ListStock.Next() );
		m_ListStock.Connect( pList );
	};
};

#endif
