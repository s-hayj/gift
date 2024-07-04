//----------------------------------------------------------
//	@file	IFrameComponent.h
//
//	@memo	フレームワークを構成するオブジェクト制御インターフェース
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__IFRAME_COMPONENT_H
#define	__IFRAME_COMPONENT_H


//----------------------------------------------------------
//	@name	IFrameComponent
//
//	@memo	フレームワークを形成するオブジェクト群を抽象化する
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	IFrameComponent
{
public:
	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	virtual ~IFrameComponent(void) = 0;

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
};

#endif