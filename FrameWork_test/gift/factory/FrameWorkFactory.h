//----------------------------------------------------------
//	@file	FrameWorkFactory.h
//
//	@memo	フレームワークの生成内容を抽象化する
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__FRAMEWORK_FACTORY_H
#define	__FRAMEWORK_FACTORY_H

#include <stdio.h>
#include "FrameCompFactory.h"
#include "../FrameComponent/System/SystemManager.h"
#include "../FrameComponent/Material/MaterialManager.h"
#include "../FrameComponent/Graphics/GraphicsManager.h"

class	FrameWork;
//class	FrameCompFactory;
class	SystemManager;
class	MaterialManager;
class	GraphicsManager;

//----------------------------------------------------------
//	@name	FrameWorkFactory
//
//	@memo	フレームワークに必要なコンポーネントを生成、結合させ
//			フレームワーク制御オブジェクトを生成する
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	FrameWorkFactory
{
public:
	static const int	NOT_SYS_FAC	=	0x0001;	//	システム生成オブジェ未登録
	static const int	NOT_MAT_FAC	=	0x0002;	//	マテリアル生成オブジェ未登録
	static const int	NOT_GRA_FAC	=	0x0004;	//	グラフィック制御オブジェ未登録
	static const int	NOT_SYSTEM	=	0x0008;	//	システム関係生成失敗
	static const int	NOT_MATERIAL=	0x0010;	//	マテリアル関係生成失敗
	static const int	NOT_GRAPHICS=	0x0020;	//	グラフィック関係生成失敗

protected:
	int					m_error;		//	エラーフラグ
	FrameWork*			m_pFrameWork;	//	フレームワークのインスタンス

private:
	FrameCompFactory< SystemManager >*		m_pSystem;		//	システム生成
	FrameCompFactory< MaterialManager >*	m_pMaterial;	//	マテリアル生成
	FrameCompFactory< GraphicsManager >*	m_pGraphics;	//	グラフィック生成

	SystemManager*		m_pSystemManager;	//	システム関係制御オブジェクト
	MaterialManager*	m_pMaterialManager;	//	マテリアル関係制御オブジェクト
	GraphicsManager*	m_pGraphicsManager;	//	グラフィック関係制御オブジェクト

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	FrameWorkFactory(void);

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	virtual ~FrameWorkFactory(void);

	//----------------------------------------------------------
	//	システム制御オブジェクトの生成方法を登録
	//
	//	@name	FrameWorkFactory::SetSystemFactory
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pFactory	システムの構造を生成するオブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	void SetSystemFactory( FrameCompFactory< SystemManager >* pFactory)
	{
		m_pSystem = pFactory;
	};

	//----------------------------------------------------------
	//	マテリアル制御オブジェクトの生成方法を登録
	//
	//	@name	FrameWorkFactory::SetMaterialFactory
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pFactory	マテリアル制御構造を生成するオブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	void SetMaterialFactory( FrameCompFactory< MaterialManager >* pFactory)
	{
		m_pMaterial = pFactory;
	};

	//----------------------------------------------------------
	//	グラフィック制御オブジェクトの生成方法を登録
	//
	//	@name	FrameWorkFactory::SetGraphicsFactory
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pFactory	グラフィック制御構造を生成するオブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	void SetGraphicsFactory( FrameCompFactory< GraphicsManager >* pFactory)
	{
		m_pGraphics = pFactory;
	};

	//----------------------------------------------------------
	//	システム関係の制御オブジェクトを取得する
	//
	//	@name	FrameWorkFactory::GetSystem
	//
	//	@memo	システムに関するオブジェクトが生成されていること
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	SystemManager*	システム制御オブジェクト
	//----------------------------------------------------------
	SystemManager* GetSystem(void) const
	{
		return m_pSystemManager;
	};

	//----------------------------------------------------------
	//	マテリアル関係の制御オブジェクトを取得する
	//
	//	@name	FrameWorkFactory::GetMaterial
	//
	//	@memo	マテリアルに関するオブジェクトが生成されていること
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	MaterialManager*	マテリアル制御オブジェクト
	//----------------------------------------------------------
	MaterialManager* GetMaterial(void) const
	{
		return m_pMaterialManager;
	};

	//----------------------------------------------------------
	//	グラフィック関係の制御オブジェクトを取得する
	//
	//	@name	FrameWorkFactory::GetGraphics
	//
	//	@memo	グラフィックに関するオブジェクトが生成されていること
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	GraphicsManager*	グラフィック制御オブジェクト
	//----------------------------------------------------------
	GraphicsManager* GetGraphics(void) const
	{
		return m_pGraphicsManager;
	};

	//----------------------------------------------------------
	//	フレームワークの生成を開始する
	//
	//	@name	FrameWorkFactory::Create
	//
	//	@memo	各コンポーネントの生成とフレームワークを生成する
	//
	//	@attrib	public virtual
	//
	//	@param	none
	//
	//	@return bool	false	生成に失敗
	//----------------------------------------------------------
	virtual bool Create(void);

	//----------------------------------------------------------
	//	エラーフラグを取得する
	//
	//	@name	FrameWorkFactory::GetError
	//
	//	@memo	生成時にエラーを起こすとビットフラグが蓄積する
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	int	０以外	生成時のエラーフラグ
	//----------------------------------------------------------
	int GetError(void)
	{
		return m_error;
	};

	//----------------------------------------------------------
	//	生成したフレームワークを取得する
	//
	//	@name	FrameWorkFactory::GetFrameWork
	//
	//	@memo	フレームワーク破棄の責任も譲渡する
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	FrameWork*	生成されたフレームワークのインスタンス
	//----------------------------------------------------------
	FrameWork* GetFrameWork(void)
	{
		FrameWork*	pTemp = m_pFrameWork;

		//	生成に利用したオブジェクトを解放する
		ReleaseComponents();

		m_pFrameWork = NULL;

		return pTemp;
	};

protected:
	//----------------------------------------------------------
	//	フレームワークの生成を実行する
	//
	//	@name	FrameWorkFactory::CreateFrameWork
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void CreateFrameWork(void) = 0;

	//----------------------------------------------------------
	//	生成に利用したオブジェクトを解放する
	//
	//	@name	FrameWorkFactory::ReleaseComponents
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void ReleaseComponents(void) = 0;

	//----------------------------------------------------------
	//	生成したフレームワークを破棄する
	//
	//	@name	FrameWorkFactory::ReleaseFrameWork
	//
	//	@memo	生成過程で失敗したときなどで呼び出される
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void ReleaseFrameWork(void) = 0;
};

#endif