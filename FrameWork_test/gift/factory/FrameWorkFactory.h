//----------------------------------------------------------
//	@file	FrameWorkFactory.h
//
//	@memo	�t���[�����[�N�̐������e�𒊏ۉ�����
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__FRAMEWORK_FACTORY_H
#define	__FRAMEWORK_FACTORY_H

#include <stdio.h>
#include "FrameCompFactory.h"
#include "../FrameComponent/System/SystemManager.h"
#include "../FrameComponent/Material/MaterialManager.h"
#include "../FrameComponent/Graphics/GraphicsManager.h"

class	FrameWork;
//class	FrameCompFactory;
class	SystemManager;
class	MaterialManager;
class	GraphicsManager;

//----------------------------------------------------------
//	@name	FrameWorkFactory
//
//	@memo	�t���[�����[�N�ɕK�v�ȃR���|�[�l���g�𐶐��A��������
//			�t���[�����[�N����I�u�W�F�N�g�𐶐�����
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	FrameWorkFactory
{
public:
	static const int	NOT_SYS_FAC	=	0x0001;	//	�V�X�e�������I�u�W�F���o�^
	static const int	NOT_MAT_FAC	=	0x0002;	//	�}�e���A�������I�u�W�F���o�^
	static const int	NOT_GRA_FAC	=	0x0004;	//	�O���t�B�b�N����I�u�W�F���o�^
	static const int	NOT_SYSTEM	=	0x0008;	//	�V�X�e���֌W�������s
	static const int	NOT_MATERIAL=	0x0010;	//	�}�e���A���֌W�������s
	static const int	NOT_GRAPHICS=	0x0020;	//	�O���t�B�b�N�֌W�������s

protected:
	int					m_error;		//	�G���[�t���O
	FrameWork*			m_pFrameWork;	//	�t���[�����[�N�̃C���X�^���X

private:
	FrameCompFactory< SystemManager >*		m_pSystem;		//	�V�X�e������
	FrameCompFactory< MaterialManager >*	m_pMaterial;	//	�}�e���A������
	FrameCompFactory< GraphicsManager >*	m_pGraphics;	//	�O���t�B�b�N����

	SystemManager*		m_pSystemManager;	//	�V�X�e���֌W����I�u�W�F�N�g
	MaterialManager*	m_pMaterialManager;	//	�}�e���A���֌W����I�u�W�F�N�g
	GraphicsManager*	m_pGraphicsManager;	//	�O���t�B�b�N�֌W����I�u�W�F�N�g

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	FrameWorkFactory(void);

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	virtual ~FrameWorkFactory(void);

	//----------------------------------------------------------
	//	�V�X�e������I�u�W�F�N�g�̐������@��o�^
	//
	//	@name	FrameWorkFactory::SetSystemFactory
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pFactory	�V�X�e���̍\���𐶐�����I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	void SetSystemFactory( FrameCompFactory< SystemManager >* pFactory)
	{
		m_pSystem = pFactory;
	};

	//----------------------------------------------------------
	//	�}�e���A������I�u�W�F�N�g�̐������@��o�^
	//
	//	@name	FrameWorkFactory::SetMaterialFactory
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pFactory	�}�e���A������\���𐶐�����I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	void SetMaterialFactory( FrameCompFactory< MaterialManager >* pFactory)
	{
		m_pMaterial = pFactory;
	};

	//----------------------------------------------------------
	//	�O���t�B�b�N����I�u�W�F�N�g�̐������@��o�^
	//
	//	@name	FrameWorkFactory::SetGraphicsFactory
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pFactory	�O���t�B�b�N����\���𐶐�����I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	void SetGraphicsFactory( FrameCompFactory< GraphicsManager >* pFactory)
	{
		m_pGraphics = pFactory;
	};

	//----------------------------------------------------------
	//	�V�X�e���֌W�̐���I�u�W�F�N�g���擾����
	//
	//	@name	FrameWorkFactory::GetSystem
	//
	//	@memo	�V�X�e���Ɋւ���I�u�W�F�N�g����������Ă��邱��
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	SystemManager*	�V�X�e������I�u�W�F�N�g
	//----------------------------------------------------------
	SystemManager* GetSystem(void) const
	{
		return m_pSystemManager;
	};

	//----------------------------------------------------------
	//	�}�e���A���֌W�̐���I�u�W�F�N�g���擾����
	//
	//	@name	FrameWorkFactory::GetMaterial
	//
	//	@memo	�}�e���A���Ɋւ���I�u�W�F�N�g����������Ă��邱��
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	MaterialManager*	�}�e���A������I�u�W�F�N�g
	//----------------------------------------------------------
	MaterialManager* GetMaterial(void) const
	{
		return m_pMaterialManager;
	};

	//----------------------------------------------------------
	//	�O���t�B�b�N�֌W�̐���I�u�W�F�N�g���擾����
	//
	//	@name	FrameWorkFactory::GetGraphics
	//
	//	@memo	�O���t�B�b�N�Ɋւ���I�u�W�F�N�g����������Ă��邱��
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	GraphicsManager*	�O���t�B�b�N����I�u�W�F�N�g
	//----------------------------------------------------------
	GraphicsManager* GetGraphics(void) const
	{
		return m_pGraphicsManager;
	};

	//----------------------------------------------------------
	//	�t���[�����[�N�̐������J�n����
	//
	//	@name	FrameWorkFactory::Create
	//
	//	@memo	�e�R���|�[�l���g�̐����ƃt���[�����[�N�𐶐�����
	//
	//	@attrib	public virtual
	//
	//	@param	none
	//
	//	@return bool	false	�����Ɏ��s
	//----------------------------------------------------------
	virtual bool Create(void);

	//----------------------------------------------------------
	//	�G���[�t���O���擾����
	//
	//	@name	FrameWorkFactory::GetError
	//
	//	@memo	�������ɃG���[���N�����ƃr�b�g�t���O���~�ς���
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	int	�O�ȊO	�������̃G���[�t���O
	//----------------------------------------------------------
	int GetError(void)
	{
		return m_error;
	};

	//----------------------------------------------------------
	//	���������t���[�����[�N���擾����
	//
	//	@name	FrameWorkFactory::GetFrameWork
	//
	//	@memo	�t���[�����[�N�j���̐ӔC�����n����
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	FrameWork*	�������ꂽ�t���[�����[�N�̃C���X�^���X
	//----------------------------------------------------------
	FrameWork* GetFrameWork(void)
	{
		FrameWork*	pTemp = m_pFrameWork;

		//	�����ɗ��p�����I�u�W�F�N�g���������
		ReleaseComponents();

		m_pFrameWork = NULL;

		return pTemp;
	};

protected:
	//----------------------------------------------------------
	//	�t���[�����[�N�̐��������s����
	//
	//	@name	FrameWorkFactory::CreateFrameWork
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void CreateFrameWork(void) = 0;

	//----------------------------------------------------------
	//	�����ɗ��p�����I�u�W�F�N�g���������
	//
	//	@name	FrameWorkFactory::ReleaseComponents
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void ReleaseComponents(void) = 0;

	//----------------------------------------------------------
	//	���������t���[�����[�N��j������
	//
	//	@name	FrameWorkFactory::ReleaseFrameWork
	//
	//	@memo	�����ߒ��Ŏ��s�����Ƃ��ȂǂŌĂяo�����
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void ReleaseFrameWork(void) = 0;
};

#endif