//----------------------------------------------------------
//	@file	GraphicsManager.h
//
//	@memo	グラフィック制御系を統括し、制御内容を抽象化する
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__GRAPHICS_MANAGER_H
#define	__GRAPHICS_MANAGER_H

#include "../IFrameComponent.h"

//----------------------------------------------------------
//	@name	GraphicsManager
//
//	@memo	グラフィック系の各制御オブジェクトの集合管理
//
//	@attrib	public abstract sub class
//
//	@base	public IFrameComponent
//
//	@author	sano-y
//	@data	2008-05-13	unfinished
//----------------------------------------------------------
class	GraphicsManager
	: public IFrameComponent
{
public:
	//----------------------------------------------------------
	//	@name	GraphicsManager::Reference
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
		//	@attrib	protected
		//----------------------------------------------------------
		virtual ~Reference(void) {};
	};

public:
	typedef	GraphicsManager::Reference	Ref;

public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	GraphicsManager::GraphicsManager
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	GraphicsManager(void)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@attrib	public
	//----------------------------------------------------------
	virtual ~GraphicsManager(void)
	{
	};

	//----------------------------------------------------------
	//	グラフィック制御系へのアクセス用インターフェースを取得する
	//
	//	@name	GraphicsManager::GetReference
	//
	//	@memo	参照のみを公開する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	GraphicsManager::Reference*	アクセス用インターフェース
	//----------------------------------------------------------
	virtual GraphicsManager::Ref* GetReference(void) = 0;

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