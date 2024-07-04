//----------------------------------------------------------
//	@file	Texture.h
//
//	@memo	テクスチャ制御に関する抽象クラス
//
//	@author	snao-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__TEXTURE_H
#define	__TEXTURE_H

#include <stdio.h>
#include "../Graphics/IResourceFactory.h"
#include "ResourceManager.h"
#include "Resource.h"

class	IResourceFactory;
class	ResourceManager;

//----------------------------------------------------------
//	@name	Texture
//
//	@memo	テクスチャ制御用抽象クラス
//
//	@attrib	public abstract sub class
//
//	@base	public Resource
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------
class	Texture
	: public Resource
{
	//	唯一カプセル化の無効化許可する対象
	friend	ResourceManager;

public:
	//----------------------------------------------------------
	//	@name	Texture::Property
	//
	//	@memo	状態に関する情報格納
	//
	//	@attrib	public nested sub struct
	//
	//	@base	public Resource::Property
	//
	//	@author	sano-y
	//	@data	2008-05-14	unfinished
	//----------------------------------------------------------
	struct	Property
		: public Resource::Property
	{
	public:

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	Texture::Property::Property
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		Property(void)
		{
		};
	};


	//----------------------------------------------------------
	//	@name	Texture::ReadOption
	//
	//	@memo	ファイル読み込み時に必要な情報格納
	//
	//	@attrib	public nested sub struct
	//
	//	@base	public Resource::ReadOption
	//
	//	@author	sano-y
	//	@data	2008-05-14	unfinished
	//----------------------------------------------------------
	struct	ReadOption
		: public Resource::ReadOption
	{
	public:

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	Texture::ReadOption::ReadOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		ReadOption(void)
		{
		};

		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	Texture::ReadOption::~ReadOption
		//
		//	@attrib	public
		//----------------------------------------------------------
		~ReadOption(void)
		{
		};

		//----------------------------------------------------------
		//	格納情報を初期化する
		//
		//	@name	Texture::ReadOption::Initialize
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	none
		//----------------------------------------------------------
		void Initialize(void)
		{
			//	継承もとの初期化処理
			this->Resource::ReadOption::Initialize();
		};
	};


	//----------------------------------------------------------
	//	@name	Texture::CreateOption
	//
	//	@memo	テクスチャデータを作成時に必要な情報格納
	//
	//	@attrib	public nested sub struct
	//
	//	@base	public Resource::CreateOption
	//
	//	@author	sano-y
	//	@data	2008-05-14	unfinished
	//----------------------------------------------------------
	struct	CreateOption
		: public Resource::CreateOption
	{
	public:
	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	Texture::CreateOption::CreateOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		CreateOption(void)
		{
		};

		//----------------------------------------------------------
		//	格納データを初期状態に戻す
		//
		//	@name	Texture::CreateOption::Initialize
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	none
		//----------------------------------------------------------
		void Initialize(void)
		{
			//	継承もとの初期化処理
			this->Resource::CreateOption::Initialize();
		};
	};

protected:
	Texture::Property	m_Property;	//	状態に関する情報

public:
	//----------------------------------------------------------
	//	状態情報を取得する
	//
	//	@name	Texture::GetProperty
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(out)property	状態情報を格納する変数への参照
	//
	//	@return none
	//----------------------------------------------------------
	void GetProperty( Texture::Property& property )
	{
		property = m_Property;
	};

	//----------------------------------------------------------
	//	テクスチャデータを解放する
	//
	//	@name	Texture::Release
	//
	//	@memo	呼び出すと自身も破棄される
	//
	//	@attrib	public override
	//
	//	@base	Resource::Release
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Release(void)
	{
		//	格納しているリソースデータを破棄する
		Destroy();

		//	検索用にID管理されていた
		if ( m_Property.m_Entry )
		{
			Texture* pTemp = NULL;

			//	検索対象から自身を破棄する
			Resource::s_pBank->Remove( m_Property.m_Id, pTemp );

			m_Property.m_Entry = false;
		}

		//	用済みになったことを通知し、在庫行きにする
		Resource::s_pBank->Restore( this );
	};

protected:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	Texture::Texture
	//
	//	@memo	派生先でのみ生成可能
	//
	//	@attrib	protected
	//
	//	@param	none
	//----------------------------------------------------------
	Texture(void)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	Texture::~Texture
	//
	//	@memo	派生先でのみ破棄可能
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~Texture(void)
	{
	};

	//	派生先で実装するべき項目
	{
#if	0
	/*
	//----------------------------------------------------------
	//	格納しているリソースデータを破棄する
	//
	//	@name	Resource::Destroy
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Destroy(void)
	{
	};
	*/
#endif
	}

private:
	//----------------------------------------------------------
	//	テクスチャの読み込み処理を実行させる
	//
	//	@name	Texture::sLoading
	//
	//	@memo
	//
	//	@attrib	private static
	//
	//	@param	(in)pFactory	読み込み処理を実行する対象
	//	@param	(in/out)option		読み込み時に必要な情報群
	//
	//	@return	Texture*	読み込まれたテクスチャデータ
	//----------------------------------------------------------
	static Texture* sLoading( IResourceFactory* pFactory,
		Texture::ReadOption& option )
	{
		Texture* pTemp = NULL;

		//	テクスチャ格納領域を取得する
		Resource::s_pBank->Order( pTemp );

		//	テクスチャを読み込む
		return pFactory->Load( pTemp, option );
	};

	//----------------------------------------------------------
	//	テクスチャデータの作成を実行させる
	//
	//	@name	Texture::sCreating
	//
	//	@memo
	//
	//	@attrib	private static
	//
	//	@param	(in)pFactory	作成処理を実行する対象
	//	@param	(in/out)option		作成時に必要な情報群
	//
	//	@return	Texture*	作成されたテクスチャデータ
	//----------------------------------------------------------
	static Texture* sCreating( IResourceFactory* pFactory,
		Texture::CreateOption& option )
	{
		Texture* pTemp = NULL;

		//	テクスチャ格納領域を取得する
		Resource::s_pBank->Order( pTemp );

		//	テクスチャを作成する
		return pFactory->Create( pTemp, option );
	};
};

#endif