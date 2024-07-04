//----------------------------------------------------------
//	@file	IResourceFactory.h
//
//	@memo	リソースデータの生成、読み込み操作用インターフェース
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__IRESOURCE_FACTORY_H
#define	__IRESOURCE_FACTORY_H

#include "../Material/Texture.h"

class	Texture;
class	Mesh;
struct	Texture::ReadOption;
struct	Mesh::ReadOption;
struct	Texture::CreateOption;
struct	Mesh::CreateOption;

//----------------------------------------------------------
//	@name	IResourceFactory
//
//	@memo	リソースデータの作成に関する操作用インターフェース
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------
class	IResourceFactory
{
public:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IResourceFactory::~IResourceFactory
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IResourceFactory(void) {};

	//----------------------------------------------------------
	//	テクスチャファイルからテクスチャの読み込みを行う
	//
	//	@name	IResourceFactory::Load
	//
	//	@memo	引数の格納オブジェクトは戻り値と同じ値になる
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTexture	テクスチャの格納用オブジェクト
	//	@param	(in/out)option	読み込み時に必要な情報群
	//
	//	@return	Texture*	読み込まれたテクスチャ情報
	//----------------------------------------------------------
	virtual Texture* Load( Texture* pTexture, Texture::ReadOption& option ) = 0;

	//----------------------------------------------------------
	//	メッシュファイルからメッシュの読み込みを行う
	//
	//	@name	IResourceFactory::Load
	//
	//	@memo	引数の格納オブジェクトは戻り値と同じ値になる
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pMesh		メッシュの格納用オブジェクト
	//	@param	(in/out)option	読み込み時に必要な情報群
	//
	//	@return	Mesh*	読み込まれたメッシュ情報
	//----------------------------------------------------------
	virtual Mesh* Load( Mesh* pMesh, Mesh::ReadOption& option ) = 0;

	//----------------------------------------------------------
	//	テクスチャデータを作成する
	//
	//	@name	IResourceFactory::Create
	//
	//	@memo	引数の格納オブジェクトは戻り値と同じ値になる
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTextrue	テクスチャの格納用オブジェクト
	//	@param	(in/out)option	作成時に必要な情報群
	//
	//	@return	Texture*	作成されたテクスチャ情報
	//----------------------------------------------------------
	virtual Texture* Create( Texture* pTexture, Texture::CreateOption& option ) = 0;

	//----------------------------------------------------------
	//	メッシュデータを作成する
	//
	//	@name	IResourceFactory::Create
	//
	//	@memo	引数の格納オブジェクトは戻り値と同じ値になる
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pMesh		メッシュの格納用オブジェクト
	//	@param	(in/out)option	作成時に必要な情報群
	//
	//	@return	Mesh*	作成されたメッシュ情報
	//----------------------------------------------------------
	virtual Mesh* Create( Mesh* pMesh, Mesh::CreateOption& option ) = 0;
};

#endif