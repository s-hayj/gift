//----------------------------------------------------------
//	@file	IRenderable.h
//
//	@memo	描画処理を呼び出すインターフェース
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__IRENDERABLE_H
#define	__IRENDERABLE_H

#include "RenderState.h"

//----------------------------------------------------------
//	@name	IRenderable
//
//	@memo	描画処理実行のためのインターフェース
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	IRenderable
{
public:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IRenderable::~IRenderable
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IRenderable(void) {};

	//----------------------------------------------------------
	//	描画処理を実行する
	//
	//	@name	IRenderable::Draw
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in/out)pState	レンダーステート
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Draw( RenderState* pState ) = 0;
};

#endif