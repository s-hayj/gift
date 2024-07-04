//----------------------------------------------------------
//	@file	Resource.h
//
//	@memo	リソースの基底クラス、主に破棄に関するオペレーションを提供
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__RESOURCE_H
#define	__RESOURCE_H

#include "ResourceBank.h"

class	ResourceBank;

//----------------------------------------------------------
//	@name	Resource
//
//	@memo	リソースアダプターの破棄に関するインターフェースを提供
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
class	Resource
{
protected:
	//----------------------------------------------------------
	//	@name	Resource::Property
	//
	//	@memo	各リソースの状態を表す共通のデータ
	//
	//	@attrib	protected nested struct
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	struct	Property
	{
	public:
		bool	m_Entry;	//	検索リスト登録の有無
		int		m_Id;		//	登録されている番号

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	Resource::Property::Property
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		Property(void)
			: m_Entry( false ), m_Id( 0 )
		{
		};
	};


	//----------------------------------------------------------
	//	@name	Resource::ReadOption
	//
	//	@memo	各リソース読み込み時に必要な共通のデータ
	//
	//	@attrib	protected nested struct
	//
	//	@author	snao-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	struct	ReadOption
	{
	public:
		char*	m_pName;	//	読み込むファイルパス
		bool	m_Entry;	//	インスタンスの貯蔵管理の有無
		int		m_Id;		//	貯蔵管理時の識別番号
		int		m_Error;	//	処理時のエラーフラグ

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	Resource::ReadOption::ReadOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		ReadOption(void)
			: m_pName( NULL ), m_Entry( false ), m_Id( 0 ), m_Error( 0x00 )
		{
		};

		//----------------------------------------------------------
		//	格納情報を初期値に戻す
		//
		//	@name	Resource::ReadOption::Initialize
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
			m_pName	= NULL;
			m_Entry	= false;
			m_Id	= 0;
			m_Error	= 0x00;
		};
	};

	//----------------------------------------------------------
	//	@name	Resource::CreateOption
	//
	//	@memo	各リソース生成時に必要な共通のデータ
	//
	//	@attrib	protected nested struct
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	struct	CreateOption
	{
	public:
		bool	m_Entry;	//	インスタンスの貯蔵管理の有無
		int		m_Id;		//	貯蔵管理時の識別番号
		int		m_Error;	//	処理時のエラーフラグ

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	Resource::CreateOption::CreateOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		CreateOption(void)
			: m_Entry( false ), m_Id( 0 ), m_Error( 0x00 )
		{
		};

		//----------------------------------------------------------
		//	格納データを初期値に戻す
		//
		//	@name	Resource::CreateOption::Initialize
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
			m_Entry	= false;
			m_Id	= 0;
			m_Error	= 0x00;
		};
	};

protected:
	static ResourceBank*	s_pBank;	//	リソースのインスタンス管理

public:
	//----------------------------------------------------------
	//	リソースアダプターの返却と、リソースデータの破棄を実行
	//
	//	@name	Resource::Release
	//
	//	@memo	格納データならびに、自身が破棄される
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Release(void) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	Resource::~Resource
	//
	//	@memo	派生先でのみ破棄可能
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~Resource(void) {};

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
	virtual void Destroy(void) = 0;
};

#endif