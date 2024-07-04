//----------------------------------------------------------
//	@file	FrameWork.cpp
//
//	@memo	フレームワークを構成し、その振る舞いを抽象化する
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#include "FrameWork.h"

//----------------------------------------------------------
//	コンストラクタ
//
//	@name	FrameWork::FrameWork
//
//	@attrib	public
//
//	@param	none
//----------------------------------------------------------
FrameWork::FrameWork(void)
:	m_pSystem( NULL ), m_pMaterial( NULL ), m_pGraphics( NULL ),
	m_message( 0x00 ), m_FrameComp()
{
}

//----------------------------------------------------------
//	デストラクタ
//
//	@attrib	public
//----------------------------------------------------------
FrameWork::~FrameWork(void)
{
	//	フレームワークの破棄
	Release();
}

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
void FrameWork::Execute(void)
{
	std::map< int, IFrameComponent* >::iterator i;

	//	メッセージの初期化
	m_message = 0;

	//	各フレームワーク構成要素の更新
	for ( i = m_FrameComp.begin(); i != m_FrameComp.end(); ++i )
	{
		//	更新とメッセージの追加
		m_message |= (*i).second->Update();
	}
}
