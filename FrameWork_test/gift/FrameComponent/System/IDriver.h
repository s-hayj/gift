//----------------------------------------------------------
//	@file	IDriver.h
//
//	@memo	主に外部情報制御オブジェクトの基底クラス
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------

#ifndef	__IDRIVER_H
#define	__IDRIVER_H

#include <string>
#include "DriveManager.h"

class	IDriveObserver;
class	DriveManager;

//----------------------------------------------------------
//	@name	IDriver
//
//	@memo	メッセージの送信可能な周辺機器制御インターフェース
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
class	IDriver
{
	//	自身のカプセル化を無効化する唯一の対象
	friend	DriveManager;

public:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IDriver::~IDriver
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IDriver(void) {};

	//----------------------------------------------------------
	//	ドライバの識別名を取得する
	//
	//	@name	IDriver::Name
	//
	//	@memo	識別するための派生先固有データを参照
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	std::string	制御ドライバの名前
	//----------------------------------------------------------
	virtual std::string Name(void) = 0;

	//----------------------------------------------------------
	//	登録されているドライバ内での処理優先度を取得する
	//
	//	@name	IDriver::GetPriority
	//
	//	@memo	値が小さいほど、優先度が高くなる。重複した場合は接続順
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	int		処理優先度
	//----------------------------------------------------------
	virtual int GetPriority(void) = 0;

	//----------------------------------------------------------
	//	メッセージの送信先を登録する
	//
	//	@name	IDriver::Add
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pObserver	メッセージを受信するオブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Add( IDriveObserver* pObserver ) = 0;

	//----------------------------------------------------------
	//	メッセージの送信対象から外す
	//
	//	@name	IDriver::Erase
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pObserver	送信対象から外すオブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Erase( IDriveObserver* pObserver ) = 0;

protected:
	//----------------------------------------------------------
	//	初期化
	//
	//	@name	IDriver::Initialize
	//
	//	@memo	ドライバマネージャーに接続されたときに呼び出される
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Initialize(void) = 0;

	//----------------------------------------------------------
	//	リセット処理
	//
	//	@name	IDriver::Terminate
	//
	//	@memo	ドライバマネージャーの管理下から外されたときに呼び出される
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Terminate(void) = 0;

	//----------------------------------------------------------
	//	状態を更新させる
	//
	//	@name	IDriver::Update
	//
	//	@memo	ドライブマネージャー以外がこれを呼び出してはいけない
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Update(void) = 0;

	//----------------------------------------------------------
	//	メッセージを送信する
	//
	//	@name	IDriver::Notify
	//
	//	@memo	自身を送信しているので、メッセージの解釈は送信先が行う
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Notify(void) = 0;
};


//----------------------------------------------------------
//	@name	IDriveObserver
//
//	@memo	ドライバのメッセージを受信する
//
//	@attirb	public interface
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
class	IDriveObserver
{
public:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IDriveObserver::~IDriveObserver
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IDriveObserver(void) {};

	//----------------------------------------------------------
	//	ドライバからのメッセージを受け取る
	//
	//	@name	IDriveObserver::Update
	//
	//	@memo	ドライバが送られるので、メッセージ内容の解釈は実装先が行う
	//
	//	@attirb	public abstract
	//
	//	@param	(in)pDriver		メッセージを内包したドライバ自身
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Update( IDriver* pDriver ) = 0;
};

#endif