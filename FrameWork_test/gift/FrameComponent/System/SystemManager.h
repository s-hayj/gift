//----------------------------------------------------------
//	@file	SystemManager.h
//
//	@memo	システム制御系を統括し、制御内容を抽象化する
//
//	@author	sano-y
//	@data	2008-05-15	unfinished
//----------------------------------------------------------

#ifndef	__SYSTEM_MANAGER_H
#define	__SYSTEM_MANAGER_H

#include "../IFrameComponent.h"
#include "DriveManager.h"

//----------------------------------------------------------
//	@name	SystemManager
//
//	@memo	システム系の各制御オブジェクトの集合管理
//
//	@attrib	public abstract sub class
//
//	@base	public IFrameComponent
//
//	@author	sano-y
//	@data	2008-05-15	unfinished
//----------------------------------------------------------
class	SystemManager
	: public IFrameComponent
{
public:
	//----------------------------------------------------------
	//	@name	SystemManager::Reference
	//
	//	@memo	必要最低限（不変）のインターフェースを公開する
	//
	//	@attrib	public nested interface
	//
	//	@author	sano-y
	//	@data	2008-05-08	unfinished
	//----------------------------------------------------------
	class	Reference
	{
	public:
	protected:
		//----------------------------------------------------------
		//	デストラクタ
		//
		//	@name	SystemManager::Reference::~Reference
		//
		//	@attrib	protected
		//----------------------------------------------------------
		virtual ~Reference(void) {};
	};

public:
	typedef	SystemManager::Reference	Ref;

protected:
	DriveManager*	m_pDriveManager;	//	外部制御管理

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	SystemManager::SystemManager
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	SystemManager(void)
		: m_pDriveManager( NULL )
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	SystemManager::~SystemManager
	//
	//	@attrib	public
	//----------------------------------------------------------
	virtual ~SystemManager(void)
	{
	};

	//----------------------------------------------------------
	//	システム制御系へのアクセス用インターフェースを取得する
	//
	//	@name	SystemManager::GetReference
	//
	//	@memo	参照のみを公開する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	SystemManager::Reference*	アクセス用インターフェース
	//----------------------------------------------------------
	virtual SystemManager::Ref* GetReference(void) = 0;

#if 0	//	要オーバーライドメソッド
	//----------------------------------------------------------
	//	状態の更新
	//
	//	@name	IFrameComponent::Update
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	int	メッセージフラグ
	//----------------------------------------------------------
	virtual int Update(void) = 0;

	//----------------------------------------------------------
	//	破棄
	//
	//	@name	IFrameComponent::Release
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	int	０以外	自身の破棄を委譲
	//----------------------------------------------------------
	virtual int Release(void) = 0;
#endif
};

#endif