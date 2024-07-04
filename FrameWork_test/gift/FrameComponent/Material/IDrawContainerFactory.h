//----------------------------------------------------------
//	@file	IDrawContainerFactory.h
//
//	@memo	�`�摀��R���e�i�̐����Ǘ��p�C���^�[�t�F�[�X
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
//	@memo	�`�摀��R���e�i�̐������@�A�������ʂ��B������
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
	//	�f�X�g���N�^
	//
	//	@name	IDrawContainerFactory::~IDrawContainerFactory
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IDrawContainerFactory(void) {};

	//----------------------------------------------------------
	//	�`��R���e�i�̊i�[���@���w�肵�āA�A���Ǘ��\�ȃR���e�i�𐶐�
	//
	//	@name	IDrawContainerFactory::Create
	//
	//	@memo	�R���e�i��A�����邱�Ƃ�O��ɂ����`��R���e�i�𐶐�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)sort	�`�揇�ԃ\�[�g���̔�r���@
	//
	//	@return	IDrawContainer*	�������ꂽ�`��R���e�i
	//----------------------------------------------------------
	virtual IDrawContainer* Create( int sort = 0 ) = 0;

	//----------------------------------------------------------
	//	�`������i�[���āA�A���\�ȃR���e�i�𐶐�
	//
	//	@name	IDrawContainerFactory::Create
	//
	//	@memo	�`����i�[�R���e�i�Ƃ��Đ���
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pBegin		�`����s�Ăяo����iNULL �w��s�j
	//	@param	(in)pEnd		�`��̌㏈���Ăяo����iNULL �w��j
	//	@param	(in)priority	�`�揇�ԃ\�[�g���̔�r�l
	//	@param	(in)hold		�`���񎩓��j���K�p�̗L��
	//
	//	@return	IDrawContainer*	�������ꂽ�`��R���e�i
	//----------------------------------------------------------
	virtual IDrawContainer* Create( IRenderable* pBegin,
		IRenderable* pEnd, float priority = 0.0f, bool hold = false ) = 0;

	//----------------------------------------------------------
	//	�`��R���e�i��ԋp����
	//
	//	@name	IDrawContainerFactory::Restore
	//
	//	@memo	�ԋp����ƁA�i�[���͑S�Ĕj�������
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pContainer	�������ꂽ�`��R���e�i
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Restore( IDrawContainer* pContainer ) = 0;
};

#endif