//----------------------------------------------------------
//	@file	IDrawContainerFactory.h
//
//	@memo	描画操作コンテナの生成管理用インターフェース
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__IDRAW_CONTAINER_FACTORY_H
#define	__IDRAW_CONTAINER_FACTORY_H

#include "IDrawContainer.h"

//----------------------------------------------------------
//	@name	IDrawContainerFactory
//
//	@memo	描画操作コンテナの生成方法、生成結果を隠蔽する
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	IDrawContainerFactory
{
public:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IDrawContainerFactory::~IDrawContainerFactory
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IDrawContainerFactory(void) {};

	//----------------------------------------------------------
	//	描画コンテナの格納方法を指定して、連結管理可能なコンテナを生成
	//
	//	@name	IDrawContainerFactory::Create
	//
	//	@memo	コンテナを連結することを前提にした描画コンテナを生成
	//
	//	@attrib	public abstract
	//
	//	@param	(in)sort	描画順番ソート時の比較方法
	//
	//	@return	IDrawContainer*	生成された描画コンテナ
	//----------------------------------------------------------
	virtual IDrawContainer* Create( int sort = 0 ) = 0;

	//----------------------------------------------------------
	//	描画情報を格納して、連結可能なコンテナを生成
	//
	//	@name	IDrawContainerFactory::Create
	//
	//	@memo	描画情報格納コンテナとして生成
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pBegin		描画実行呼び出し先（NULL 指定不可）
	//	@param	(in)pEnd		描画の後処理呼び出し先（NULL 指定可）
	//	@param	(in)priority	描画順番ソート時の比較値
	//	@param	(in)hold		描画情報自動破棄適用の有無
	//
	//	@return	IDrawContainer*	生成された描画コンテナ
	//----------------------------------------------------------
	virtual IDrawContainer* Create( IRenderable* pBegin,
		IRenderable* pEnd, float priority = 0.0f, bool hold = false ) = 0;

	//----------------------------------------------------------
	//	描画コンテナを返却する
	//
	//	@name	IDrawContainerFactory::Restore
	//
	//	@memo	返却すると、格納情報は全て破棄される
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pContainer	生成された描画コンテナ
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Restore( IDrawContainer* pContainer ) = 0;
};

#endif