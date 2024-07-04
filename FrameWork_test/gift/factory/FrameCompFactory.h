//----------------------------------------------------------
//	@file	FrameCompFactory.h
//
//	@memo	フレームワークを構成する各要素の生成方法を隠蔽する
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__FRAME_COMP_FACTORY_H
#define	__FRAME_COMP_FACTORY_H

#include <stdio.h>
//#include "FrameWorkFactory.h"

class	FrameWorkFactory;

//----------------------------------------------------------
//	@name	FrameCompFactory
//
//	@memo	フレームワークを構成するコンポーネントを生成
//
//	@attrib	public template abstract class
//
//	@type	Component	生成するコンポーネント名
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
template<class Component>
class	FrameCompFactory
{
protected:
	Component*	m_pComponent;	//	生成したコンポーネントのインスタンス

private:
	bool	m_created;		//	生成したコンポーネントの責任の有無

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	FrameCompFactory(void)
		: m_pComponent( NULL ), m_created( false )
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	virtual ~FrameCompFactory(void)
	{
		//	インスタンスを委譲していない
		if ( m_created )
		{
			//	インスタンスの破棄
			Release();
		}
		m_created		= false;
		m_pComponent	= NULL;
	};

	//----------------------------------------------------------
	//	オブジェクトの生成
	//
	//	@name	FrameCompFactory::Create
	//
	//	@memo	テンプレート引数のオブジェクトを生成させる
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Create(void)
	{
		//	まだ生成していない
		if ( !m_created )
		{
			//	責任を所持
			m_created = true;

			//	コンポーネントを生成する
			CreateComponent();
		}
	};

	//----------------------------------------------------------
	//	生成したオブジェクトの初期化
	//
	//	@name	FrameCompFactory::Initialize
	//
	//	@memo	生成したオブジェクトの初期化等にしようする
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pFrameFactory	フレームワークを作成するオブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Initialize( const FrameWorkFactory* pFrameFactory ) = 0;

	//----------------------------------------------------------
	//	生成したコンポーネントを取得する
	//
	//	@name	FrameCompFactory::GetComponent
	//
	//	@memo	責任ごと生成したコンポーネントのインスタンスを委譲する
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	Component*	生成したコンポーネントのインスタンス
	//----------------------------------------------------------
	Component* GetComponent(void)
	{
		m_created = false;

		return m_pComponent;
	};

protected:
	//----------------------------------------------------------
	//	コンポーネントを生成する
	//
	//	@name	FrameCompFactory::CreateComponent
	//
	//	@memo	コンポーネントを生成する
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void CreateComponent(void) = 0;

	//----------------------------------------------------------
	//	コンポーネントの破棄
	//
	//	@name	FrameCompFactory::Release
	//
	//	@memo	生成したコンポーネントを破棄する
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Release(void) = 0;
};

#endif