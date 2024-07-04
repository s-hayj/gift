//----------------------------------------------------------
//	@file	IRenderable.h
//
//	@memo	�`�揈�����Ăяo���C���^�[�t�F�[�X
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
//	@memo	�`�揈�����s�̂��߂̃C���^�[�t�F�[�X
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
	//	�f�X�g���N�^
	//
	//	@name	IRenderable::~IRenderable
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IRenderable(void) {};

	//----------------------------------------------------------
	//	�`�揈�������s����
	//
	//	@name	IRenderable::Draw
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in/out)pState	�����_�[�X�e�[�g
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Draw( RenderState* pState ) = 0;
};

#endif