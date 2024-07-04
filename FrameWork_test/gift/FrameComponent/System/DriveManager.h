//----------------------------------------------------------
//	@file	DriveManager.h
//
//	@memo	外部制御用オブジェクトの格納管理
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------

#ifndef	__DRIVE_MANAGER_H
#define	__DRIVE_MANAGER_H

#include <stdio.h>
#include <assert.h>
#include "IDriver.h"

class	IDriver;

//----------------------------------------------------------
//	@name	DriveManager
//
//	@memo	外部制御オブジェクトの集合管理制御を行う
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
class	DriveManager
{
public:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	DriveManager::DriveManager
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IDriveManager(void)
	{
	};

	//----------------------------------------------------------
	//	ドライバの接続を行う
	//
	//	@name	DriveManager::Connect
	//
	//	@memo	派生しても DriveManager::Connect を呼び出すこと
	//
	//	@attrib	public virtual
	//
	//	@param	(in)pDriver		管理下におくドライバ
	//
	//	@return	bool	true なら、正常に接続された
	//----------------------------------------------------------
	virtual bool Connect( IDriver* pDriver )
	{
		//	接続対象が存在する
		ASSERT( pDriver != NULL );

		//	接続時の初期化処理
		pDriver->Initialize();

		return true;
	};

	//----------------------------------------------------------
	//	指定ドライバを管理下から外す
	//
	//	@name	DriveManager::Disconnect
	//
	//	@memo	派生しても DriveManager::Disconnect を呼び出すこと
	//
	//	@attrib	public virtual
	//
	//	@param	(in)pDriver		管理下から外すドライバ
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Disconnect( IDriver* pDriver )
	{
		//	接続対象が存在する
		ASSERT( pDriver != NULL );

		//	管理から外したときの処理
		pDriver->Terminate();
	};

	//----------------------------------------------------------
	//	管理中のドライバを検索し、目的のドライバを参照
	//
	//	@name	DriveManager::Get
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pName	検索に利用するドライバ識別名
	//
	//	@return	IDriver*	NULL 以外なら、指定ドライバへのポインタ
	//----------------------------------------------------------
	virtual IDriver* Get( char* pName ) = 0;

	//----------------------------------------------------------
	//	管理中のドライバの各種処理を実行する
	//
	//	@name	DriveManager::Execute
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Execute(void) = 0;
};

#endif