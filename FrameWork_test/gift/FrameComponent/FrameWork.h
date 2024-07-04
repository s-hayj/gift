//----------------------------------------------------------
//	@file	FrameWork.h
//
//	@memo	フレームワークを構成し、その振る舞いを抽象化する
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__FRAMEWORK_H
#define	__FRAMEWORK_H

#include <stdio.h>
#include <map>
#include "../factory/FrameCompFactory.h"
#include "System/SystemManager.h"
#include "Material/MaterialManager.h"
#include "Graphics/GraphicsManager.h"

//----------------------------------------------------------
//	@name	FrameWork
//
//	@memo	フレームワークの構造定義、振る舞いは抽象化
//
//	@attrib	public abstract class
//
//	author	sano-y
//	data	2008-05-13	unfinished
//----------------------------------------------------------
class	FrameWork
{
public:
	static const int	NORMAL_EXIT = 0x0001;	//	正常終了
	static const int	EXCEPTION	= 0x0002;	//	例外

protected:
	SystemManager*		m_pSystem;		//	システム制御系
	MaterialManager*	m_pMaterial;	//	マテリアル制御系
	GraphicsManager*	m_pGraphics;	//	グラフィック制御系

	std::map< int, IFrameComponent* >	m_FrameComp;	//	構成内容格納

	int		m_message;	//	メッセージフラグ

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	FrameWork::FrameWork
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	FrameWork(void);

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	FrameWork::~FrameWork
	//
	//	@attrib	public
	//----------------------------------------------------------
	virtual ~FrameWork(void);

	//----------------------------------------------------------
	//	初期化
	//
	//	@name	FrameWork::Initialize
	//
	//	@memo	フレームワークの構造を組み立てる
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pSystem		システム制御系オブジェクト
	//	@param	(in)pMaterial	マテリアル制御系オブジェクト
	//	@param	(in)pGraphics	グラフィック制御系オブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Initialize( SystemManager* pSystem,
		MaterialManager* pMaterial, GraphicsManager* pGraphics) = 0;

	//----------------------------------------------------------
	//	破棄
	//
	//	@name	FrameWork::Release
	//
	//	@memo	フレームワークの構成を破棄する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Release(void) = 0;

	//----------------------------------------------------------
	//	システム制御系へアクセス
	//
	//	@name	FrameWork::GetSystem
	//
	//	@memo	参照のみを譲渡
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	SystemManager::Reference*	システム系へのポインタ
	//----------------------------------------------------------
	SystemManager::Ref* GetSustem(void)
	{
		return m_pSystem->GetReference();
	};

	//----------------------------------------------------------
	//	マテリアル制御系へアクセス
	//
	//	@name	FrameWork::GetMaterial
	//
	//	@memo	参照のみを譲渡
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	MaterialManager::Reference*	マテリアル系へのポインタ
	//----------------------------------------------------------
	MaterialManager::Ref* GetMaterial(void)
	{
		return m_pMaterial->GetReference();
	};

	//----------------------------------------------------------
	//	グラフィック制御系へアクセス
	//
	//	@name	FrameWork::GetGraphics
	//
	//	@memo	参照のみを譲渡
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	GraphicsManager::Reference*	グラフィック系へのポインタ
	//----------------------------------------------------------
	GraphicsManager::Ref* GetGraphics(void)
	{
		return m_pGraphics->GetReference();
	};

	//----------------------------------------------------------
	//	フレームワーク内の処理を実行する
	//
	//	@name	FrameWork::Execute
	//
	//	@memo	デフォルトの振る舞いを定義
	//
	//	@attrib	public virtual
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Execute(void);

	//----------------------------------------------------------
	//	終了フラグを取得する
	//
	//	@name	FrameWork::Exit
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true	終了
	//----------------------------------------------------------
	virtual bool Exit(void) = 0;

	//----------------------------------------------------------
	//	メッセージフラグを取得
	//
	//	@name	FrameWork::GetMessage
	//
	//	@memo	最後に発行されたメッセージフラグを取得
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	int	０以外	メッセージフラグ
	//----------------------------------------------------------
	int GetMessage(void)
	{
		return m_message;
	};
};

#endif