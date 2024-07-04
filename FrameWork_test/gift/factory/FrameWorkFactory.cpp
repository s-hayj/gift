//----------------------------------------------------------
//	@file	FrameWorkFactory.cpp
//
//	@memo	フレームワークの生成内容を抽象化する
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#include "FrameWorkFactory.h"
#include "../FrameComponent/System/SystemManager.h"
#include "../FrameComponent/Material/MaterialManager.h"
#include "../FrameComponent/Graphics/GraphicsManager.h"

//----------------------------------------------------------
//	コンストラクタ
//
//	@name	FrameWorkFactory::FrameWorkFactory
//
//	@param	none
//----------------------------------------------------------
FrameWorkFactory::FrameWorkFactory(void)
:	m_error( 0x00 ), m_pFrameWork( NULL ), m_pSystem( NULL ),
	m_pMaterial( NULL ), m_pGraphics( NULL ), m_pSystemManager( NULL ),
	m_pMaterialManager( NULL ), m_pGraphicsManager( NULL )
{
}

//----------------------------------------------------------
//	デストラクタ
//
//	@name	FrameWorkFactory::~FrameWorkFactory
//----------------------------------------------------------
FrameWorkFactory::~FrameWorkFactory(void)
{
	//	生成に利用したオブジェクトを破棄する
	ReleaseComponents();

	//	生成したフレームワークが譲渡されなかった
	if ( m_pFrameWork )
	{
		//	フレームワークの破棄
		ReleaseFrameWork();
	}
}

//----------------------------------------------------------
//	フレームワークの生成を開始する
//
//	@name	FrameWorkFactory::Create
//
//	@memo	各コンポーネントの生成とフレームワークを生成する
//
//	@attrib	public
//
//	@param	none
//
//	@return bool	false	生成に失敗
//----------------------------------------------------------
bool FrameWorkFactory::Create(void)
{
	//	システム制御オブジェクトの生成
	if ( m_pSystem )
	{
		m_pSystem->Create();
	}
	else
	{
		m_error |= FrameWorkFactory::NOT_SYS_FAC;
	}

	//	マテリアル制御オブジェクトの生成
	if ( m_pMaterial )
	{
		m_pMaterial->Create();
	}
	else
	{
		m_error |= FrameWorkFactory::NOT_MAT_FAC;
	}

	//	グラフィック制御オブジェクトの生成
	if ( m_pGraphics )
	{
		m_pGraphics->Create();
	}
	else
	{
		m_error |= FrameWorkFactory::NOT_GRA_FAC;
	}

	//	グラフィック制御系の構築
	m_pGraphics->Initialize( this );

	//	マテリアル制御系の構築
	m_pMaterial->Initialize( this );

	//	システム制御系の構築
	m_pSystem->Initialize( this );

	//	各コンポーネントのインスタンスを取得
	m_pGraphicsManager	= m_pGraphics->GetComponent();
	m_pMaterialManager	= m_pMaterial->GetComponent();
	m_pSystemManager	= m_pSystem->GetComponent();

	//	各コンポーネントが正常に取得できたか検査
	if ( m_pGraphicsManager == NULL )
	{
		m_error |= FrameWorkFactory::NOT_GRAPHICS;
	}
	if ( m_pMaterialManager == NULL )
	{
		m_error |= FrameWorkFactory::NOT_MATERIAL;
	}
	if ( m_pSystemManager == NULL )
	{
		m_error |= FrameWorkFactory::NOT_SYSTEM;
	}

	return (m_error == 0);
}
