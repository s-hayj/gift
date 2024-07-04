//----------------------------------------------------------
//	@file	ResourceManager.h
//
//	@memo	リソースデータの操作を一括して担当する
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__RESOURCE_MANAGER_H
#define	__RESOURCE_MANAGER_H

#include "../Graphics/IResourceFactory.h"
#include "ResourceBank.h"

class	IResourceFactory;
class	Texture;
class	Mesh;
struct	Texture::CreateOption;
struct	Texture::ReadOption;
struct	Mesh::CreateOption;
struct	Mesh::ReadOption;

//----------------------------------------------------------
//	@name	ResourceManager
//
//	@memo	リソースに関する操作を割り振る
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
class	ResourceManager
{
protected:
	int					m_Error;	//	最後に出力されたエラーフラグ
	IResourceFactory*	m_pFactory;	//	リソース生成管理
	ResourceBank*		m_pBank;	//	リソースのインスタンス管理

public:
	//----------------------------------------------------------
	//	リソースファイルから各リソースデータを読み込む
	//
	//	@name	ResourceManager::Load
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	読み込むリソースデータの型
	//
	//	@param	(in/out)option	読み込み時に必要なデータ群
	//
	//	@return	T*	読み込まれたリソースデータへのポインタ
	//----------------------------------------------------------
	template<class T>
		T* Load( typename T::ReadOption& option )
	{
		//	ファイルの読み込み開始
		T*	pTemp = typename T::Loading( m_pFactory, option );

		//	正常に読み込まれた
		if ( option.m_Error == 0 )
		{
			//	検索可能にする
			if ( option.m_Entry )
			{
				option.m_Error |= m_pBank->Add( option.m_Id, pTemp );
			}
		}
		return pTemp;
	};

	//----------------------------------------------------------
	//	リソースデータから各リソースを生成する
	//
	//	@name	ResourceManager::Create
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	書き込むリソースデータの型
	//
	//	@param	(in/out)option	書き込み時に必要なデータ群
	//
	//	@return	T*	書き込まれたリソースデータへのポインタ
	//----------------------------------------------------------
	template<class T>
		T* Create( typename T::CreateOption& option )
	{
		//	データの書き出し開始
		T* pTemp = typename T::Create( m_pFactory, option );

		//	正常に書き出された
		if ( option.m_Error == 0 )
		{
			//	検索可能にする
			if ( option.m_Entry )
			{
				option.m_Error |= m_pBank->Add( option.m_Id, pTemp );
			}
		}
		return pTemp;
	};

	//----------------------------------------------------------
	//	格納させたリソースデータを検索する
	//
	//	@name	ResourceManager::GetResource
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	取得するリソースの型
	//
	//	@param	(in)id	登録時に指定した検索キー
	//
	//	@return	T*	NULL 以外なら、指定したリソースデータ
	//----------------------------------------------------------
	template< class T >
		T* GetResource( int id )
	{
		T* pTemp = NULL;

		m_Error = 0x00;

		//	リソースデータの検索
		m_Error = m_pBank->Get( id, pTemp );

		//	何かしらのエラーが発生した
		if ( m_Error )
		{
			//	失敗したことにする
			pTemp = NULL;
		}
		return pTemp;
	};

	//----------------------------------------------------------
	//	指定したリソースを検索し破棄する
	//
	//	@name	ResourceManager::Erase
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	破棄するリソースの型
	//
	//	@param	(in)id	登録時に指定した検索キー
	//
	//	@return	none
	//----------------------------------------------------------
	template< class T >
		void Erase( int id )
	{
		T*	pTemp = NULL;

		m_Error = 0x00;

		//	破棄するリソースの検索
		m_Error = m_pBank->Remove( id, pTemp );

		//	検索に成功
		if ( m_Error == 0 )
		{
			typename T::Property property;

			//	状態情報を取得
			pTemp->GetProperty( property );

			//	検索対象から外す
			property.m_Entry = false;

			//	リソースの破棄
			pTemp->Release();
		}
	};

	//----------------------------------------------------------
	//	指定したリソースを全て破棄する
	//
	//	@name	ResourceManager::Clear
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	破棄するリソースの型
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	template< class T >
		void Clear(void)
	{
		T*	pTemp = NULL;

		//	管理中の全てのリソースを破棄する
		m_pBank->Clear( pTemp );
	};

	//----------------------------------------------------------
	//	最後に発生したエラーフラグを取得する
	//
	//	@name	ResourceManager::LastError
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	int	０以外なら、エラーフラグ
	//----------------------------------------------------------
	int LastError(void)
	{
		return m_Error;
	};

protected:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	ResourceManager::ResourceManager
	//
	//	@memo	派生先でのみ生成可能
	//
	//	@attrib	protected
	//
	//	@param	none
	//----------------------------------------------------------
	ResourceManager(void)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	ResourceManager::~ResourceManager
	//
	//	@memo	派生先でのみ破棄可能
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~ResourceManager(void)
	{
	};
};

#endif