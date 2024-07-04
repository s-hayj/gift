//----------------------------------------------------------
//	@file	IResourceCollection.h
//
//	@memo	検索可能な各リソース集合を管理するためのオペレーションを提供
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__IRESOURCE_COLLECTION_H
#define	__IRESOURCE_COLLECTION_H

#include <stdio.h>
#include <assert.h>

//----------------------------------------------------------
//	@name	IResourceCollection
//
//	@memo	各リソースの集合を管理し、検索参照可能にする
//
//	@attrib	public template abstract class
//
//	@type	T	管理するリソースの型
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
template< class T >
class	IResourceCollection
{
public:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IResourceCollection::~IResourceCollection
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~ResourceCollection(void) {};

	//----------------------------------------------------------
	//	リソースを検索IDと共に管理下に追加する
	//
	//	@name	IResourceCollection::Add
	//
	//	@memo	登録IDは重複することができないので、エラー
	//
	//	@attrib	public abstract
	//
	//	@param	(in)id			検索する際のキー
	//	@param	(in)resource	格納するリソースデータへの参照
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	virtual int Add( int id, T& resource ) = 0;

	//----------------------------------------------------------
	//	指定リソースを検索後取得する
	//
	//	@name	IResourceCollection::Get
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)id			登録したときの検索キー
	//	@param	(out)resource	指定リソース格納先への参照
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	virtual int Get( int id, T& resource ) = 0;

	//----------------------------------------------------------
	//	指定したリソースを管理下から外す
	//
	//	@name	IResourceCollection::Remove
	//
	//	@memo	リソース集合から外すのみで、リソース破棄は行わない
	//
	//	@attrib	public abstract
	//
	//	@param	(in)id			登録したときの検索キー
	//	@param	(out)resource	管理下から外されたリソース格納先への参照
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	virtual int Remove( int id, T& resource ) = 0;

	//----------------------------------------------------------
	//	格納している全てのリソースをリソースデータと共に破棄する
	//
	//	@name	IResourceCollection::Clear
	//
	//	@memo	格納している全てのリソースを破棄する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Clear(void) = 0;
};

#endif