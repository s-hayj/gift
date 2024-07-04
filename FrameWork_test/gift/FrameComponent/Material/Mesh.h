//----------------------------------------------------------
//	@file	Mesh.h
//
//	@memo	メッシュ制御に関する抽象クラス
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__MESH_H
#define	__MESH_H

#include <stdio.h>
#include "../Graphics/IResourceFactory.h"
#include "ResourceManager.h;
#include "Resource.h"

class	IResourceFactory;
class	ResourceManager;

//----------------------------------------------------------
//	@name	Mesh
//
//	@memo	メッシュ制御用抽象クラス
//
//	@attrib	public abstract sub class
//
//	@base	public Resource
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------
class	Mesh
	: public Resource
{
	//	唯一カプセル化の無効化を許可する対象
	friend	ResourceManager;

public:
	//----------------------------------------------------------
	//	@name	Mesh::Property
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
		//	@name	Mesh::Property::Property
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
	//	@name	Mesh::ReadOption
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
		//	@name	Mesh::ReadOption::ReadOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		ReadOption(void)
		{
		};

		//----------------------------------------------------------
		//	格納情報を初期値に戻す
		//
		//	@name	Mesh::ReadOption::Initialize
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
	//	@name	Mesh::CreateOption
	//
	//	@memo	メッシュデータの作成時に必要な情報格納
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
		//	@name	Mesh::CreateOpetion::CreateOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		CreateOption(void)
		{
		};

		//----------------------------------------------------------
		//	格納情報を初期値に戻す
		//
		//	@name	Mesh::CreateOption::Initialize
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
	Mesh::Property	m_Property;	//	状態に関する情報

public:
	//----------------------------------------------------------
	//	状態情報を取得する
	//
	//	@name	Mesh::GetProperty
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(out)property	状態情報を格納する変数への参照
	//
	//	@return	none
	//----------------------------------------------------------
	void GetProperty( Mesh::Property& property )
	{
		property = m_Property;
	};

	//----------------------------------------------------------
	//	メッシュデータを解放する
	//
	//	@name	Mesh::Release
	//
	//	@memo	呼び出すと、自身も破棄される
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
		//	格納しているリソースデータを破棄
		Destroy();

		//	検索用にID管理されていた
		if ( m_Property.m_Entry )
		{
			Mesh* pTemp = NULL;

			//	検索対象から自身を破棄する
			Resource::s_pBank->Remove( m_Property.m_Id, pTemp );

			m_Property.m_Entry = false;
		}

		//	自身が用済みになったことを通知し、在庫行きにする
		Resource::s_pBank->Restore( this );
	};

protected:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	Mesh::Mesh
	//
	//	@memo	派生先でのみ生成可能
	//
	//	@attrib	protected
	//
	//	@param	none
	//----------------------------------------------------------
	Mesh(void)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	Mesh::~Mesh
	//
	//	@memo	派生先でのみ破棄可能
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~Mesh(void)
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
	//	メッシュの読み込み処理を実行させる
	//
	//	@name	Mesh::sLoading
	//
	//	@memo
	//
	//	@attrib	private static
	//
	//	@param	(in)pFactory	読み込み処理を実行する対象
	//	@param	(in/out)option		読み込み時に必要な情報群
	//
	//	@return	Mesh*	読み込まれたメッシュデータ
	//----------------------------------------------------------
	static Mesh* sLoading( IResourceFactory* pFactory,
		Mesh::ReadOption& option )
	{
		Mesh* pTemp = NULL;

		//	メッシュ格納領域を取得する
		Resource::s_pBank->Order( pTemp );

		//	メッシュを読み込む
		return pFactory->Load( pTemp, option );
	};

	//----------------------------------------------------------
	//	メッシュデータの作成を実行させる
	//
	//	@name	Mesh::sCreating
	//
	//	@memo
	//
	//	@attrib	private static
	//
	//	@param	(in)pFactory	作成処理を実行する対象
	//	@param	(in/out)option		作成時に必要な情報群
	//
	//	@return	Mesh*	作成されたメッシュデータ
	//----------------------------------------------------------
	static Mesh* sCreating( IResourceFactory* pFactory,
		Mesh::CreateOption& option )
	{
		Mesh* pTemp = NULL;
		
		//	メッシュ格納領域を取得する
		Resource::s_pBank->Order( pTemp );

		//	メッシュを作成する
		return pFactory->Create( option );
	};
};

#endif