//----------------------------------------------------------
//	@file	MaterialManager.h
//
//	@memo	マテリアル制御系を統括し、制御内容を抽象化する
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__MATERIAL_MANAGER_H
#define	__MATERIAL_MANAGER_H

#include "../IFrameComponent.h"

//----------------------------------------------------------
//	@name	MaterialManager
//
//	@memo	マテリアル系の各制御オブジェクトの集合管理
//
//	@attrib	public abstract sub class
//
//	@base	public IFrameComponent
//
//	@author	sano-y
//	@data	2008-05-13	unfinished
//----------------------------------------------------------
class	MaterialManager
	: public IFrameComponent
{
public:
	//----------------------------------------------------------
	//	@name	MaterialManager::Reference
	//
	//	@memo	必要最低限（不変）のインターフェースを公開する
	//
	//	@attrib	public nested interface
	//
	//	@author	sano-y
	//	@data	2008-05-08	unfinished
	//----------------------------------------------------------
	class Reference
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
	typedef	MaterialManager::Reference	Ref;
	
public:
	//----------------------------------------------------------
	//	コンストラクタ
	//
	//	@name	MaterialManager::MaterialManager
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	MaterialManager(void)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	MaterialManager::~MaterialManager
	//
	//	@attrib	public
	//----------------------------------------------------------
	virtual ~MaterialManager(void)
	{
	};

	//----------------------------------------------------------
	//	マテリアル制御系へのアクセス用インターフェースを取得する
	//
	//	@name	MaterialManager::GetReference
	//
	//	@memo	参照のみを公開する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	MaterialManager::Reference*	アクセス用インターフェース
	//----------------------------------------------------------
	virtual MaterialManager::Ref* GetReference(void) = 0;

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