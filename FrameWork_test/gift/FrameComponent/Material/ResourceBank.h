//----------------------------------------------------------
//	@file	ResourceBank.h
//
//	@memo	リソース操作オブジェクトのインスタンス管理
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__RESOURCE_BANK_H
#define	__RESOURCE_BANK_H

#include "Mesh.h"
#include "Texture.h"
#include "../../lib/ObjectBank.h"
#include "IResourceCollection.h"

//----------------------------------------------------------
//	@name	ResourceBank
//
//	@memo	リソースならびにリソースアダプターの在庫管理
//
//	@attrib	public class
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------
class	ResourceBank
{
private:
	ObjectBank< Mesh* >		m_MeshBank;		//	メッシュのアダプター管理
	ObjectBank< Texture* >	m_TextureBank;	//	テクスチャのアダプター管理

	IResourceCollection< Mesh* >*		m_pMeshCollection;		//	メッシュの集合
	IResourceCollection< Texture* >*	m_pTextureCollection;	//	テクスチャの集合

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	ResourceBank::ResourceBank
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	ResourceBank(void);

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	ResourceBank::~ResourceBank
	//
	//	@attrib	public
	//----------------------------------------------------------
	~ResourceBank(void);

	//----------------------------------------------------------
	//	メッシュの集合管理方法を登録する
	//
	//	@name	ResourceBank::RegisterCollection
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pCollection	メッシュの集合管理オブジェクト
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int RegisterCollection( IResourceCollection< Mesh* >* pCollection );

	//----------------------------------------------------------
	//	テクスチャの集合管理方法を登録する
	//
	//	@name	ResourceBank::RegisterCollection
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pCollection	テクスチャの集合管理オブジェクト
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int RegisterCollection( IResourceCollection< Texture* >* pCollection );

	//----------------------------------------------------------
	//	メッシュの格納領域の生成、破棄方法を登録する
	//
	//	@name	ResourceBank::RegisterNewDelManager
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)manager	メッシュの格納オブジェクトの生成、破棄方法
	//
	//	@return	none
	//----------------------------------------------------------
	void RegisterNewDelManager( NewDelManager< Mesh* >& manager );

	//----------------------------------------------------------
	//	テクスチャの格納領域の生成、破棄方法を登録する
	//
	//	@name	ResourceBank::RegisterNewDelManager
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)manager	テクスチャの格納オブジェクトの生成、破棄方法
	//
	//	@return	none
	//----------------------------------------------------------
	void RegisterNewDelManager( NewDelManager< Texture* >& manager );

	//----------------------------------------------------------
	//	メッシュデータを検索IDと共に管理させる
	//
	//	@name	ResourceBank::Add
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id		検索する際のキー
	//	@param	(in)pMesh	格納するメッシュデータ
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int Add( int id, Mesh* pMesh );

	//----------------------------------------------------------
	//	テクスチャデータを検索IDと共に管理させる
	//
	//	@name	ResourceBank::Add
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id			検索する際のキー
	//	@param	(in)pTexture	格納するテクスチャデータ
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int Add( int id, Texture* pTexture );

	//----------------------------------------------------------
	//	指定メッシュデータを検索し参照する
	//
	//	@name	ResourceBank::Get
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id		検索する際のキー
	//	@param	(out)pMesh	検索結果を格納する
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int Get( int id, Mesh*& pMesh );

	//----------------------------------------------------------
	//	指定テクスチャデータを検索し参照する
	//
	//	@name	ResourceBank::Get
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id			検索する際のキー
	//	@param	(out)pTexture	検索結果を格納する
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int Get( int id, Texture*& pTexture );

	//----------------------------------------------------------
	//	指定メッシュを検索対象から外す
	//
	//	@name	ResourceBank::Remove
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id		登録時に指定した検索キー
	//	@param	(out)pMesh	外されたメッシュへのポインタ
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int Remove( int id, Mesh*& pMesh );

	//----------------------------------------------------------
	//	指定テクスチャを検索対象から外す
	//
	//	@name	ResourceBank::Remove
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id			登録時に指定した検索キー
	//	@param	(out)pTexture	外されたテクスチャへのポインタ
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int Remove( int id, Texture*& pTexture );

	//----------------------------------------------------------
	//	管理している全てのメッシュデータを破棄する
	//
	//	@name	ResourceBank::Clear
	//
	//	@memo	オーバーロードするためにわざわざ引数がある
	//
	//	@attrib	public
	//
	//	@param	(in)pMesh	破棄するリソース型識別用
	//
	//	@return	none
	//----------------------------------------------------------
	void Clear( Mesh* pMesh );

	//----------------------------------------------------------
	//	管理している全てのテクスチャデータを破棄する
	//
	//	@name	ResourceBank::Clear
	//
	//	@memo	オーバーロードするためにわざわざ引数がある
	//
	//	@attrib	public
	//
	//	@param	(in)pTexture	破棄するリソース型識別用
	//
	//	@return	none
	//----------------------------------------------------------
	void Clear( Texture* pTexture );

	//----------------------------------------------------------
	//	メッシュデータ用のリソースアダプターを取得する
	//
	//	@name	ResourceBank::Order
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(out)pMesh	メッシュアダプターの格納先ポインタへの参照
	//
	//	@return	none
	//----------------------------------------------------------
	void Order( Mesh*& pMesh );

	//----------------------------------------------------------
	//	テクスチャデータ用のリソースアダプターを取得する
	//
	//	@name	ResourceBank::Order
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(out)pTexture	テクスチャアダプターの格納先ポインタへの参照
	//
	//	@return	none
	//----------------------------------------------------------
	void Order( Texture*& pTexture );

	//----------------------------------------------------------
	//	指定メッシュを倉庫へ返却する
	//
	//	@name	ResourceBank::Restore
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pMesh	返却されるメッシュへのポインタ
	//
	//	@return	none
	//----------------------------------------------------------
	void Restore( Mesh* pMesh );

	//----------------------------------------------------------
	//	指定テクスチャを倉庫へ返却する
	//
	//	@name	ResourceBank::Restore
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pTexture	返却されるテクスチャへのポインタ
	//
	//	@return	none
	//----------------------------------------------------------
	void Restore( Texture* pTexture );
};

#endif