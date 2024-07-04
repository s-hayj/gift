//----------------------------------------------------------
//	@file	FrameWorkFactory.cpp
//
//	@memo	�t���[�����[�N�̐������e�𒊏ۉ�����
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#include "FrameWorkFactory.h"
#include "../FrameComponent/System/SystemManager.h"
#include "../FrameComponent/Material/MaterialManager.h"
#include "../FrameComponent/Graphics/GraphicsManager.h"

//----------------------------------------------------------
//	�R���X�g���N�^
//
//	@name	FrameWorkFactory::FrameWorkFactory
//
//	@param	none
//----------------------------------------------------------
FrameWorkFactory::FrameWorkFactory(void)
:	m_error( 0x00 ), m_pFrameWork( NULL ), m_pSystem( NULL ),
	m_pMaterial( NULL ), m_pGraphics( NULL ), m_pSystemManager( NULL ),
	m_pMaterialManager( NULL ), m_pGraphicsManager( NULL )
{
}

//----------------------------------------------------------
//	�f�X�g���N�^
//
//	@name	FrameWorkFactory::~FrameWorkFactory
//----------------------------------------------------------
FrameWorkFactory::~FrameWorkFactory(void)
{
	//	�����ɗ��p�����I�u�W�F�N�g��j������
	ReleaseComponents();

	//	���������t���[�����[�N�����n����Ȃ�����
	if ( m_pFrameWork )
	{
		//	�t���[�����[�N�̔j��
		ReleaseFrameWork();
	}
}

//----------------------------------------------------------
//	�t���[�����[�N�̐������J�n����
//
//	@name	FrameWorkFactory::Create
//
//	@memo	�e�R���|�[�l���g�̐����ƃt���[�����[�N�𐶐�����
//
//	@attrib	public
//
//	@param	none
//
//	@return bool	false	�����Ɏ��s
//----------------------------------------------------------
bool FrameWorkFactory::Create(void)
{
	//	�V�X�e������I�u�W�F�N�g�̐���
	if ( m_pSystem )
	{
		m_pSystem->Create();
	}
	else
	{
		m_error |= FrameWorkFactory::NOT_SYS_FAC;
	}

	//	�}�e���A������I�u�W�F�N�g�̐���
	if ( m_pMaterial )
	{
		m_pMaterial->Create();
	}
	else
	{
		m_error |= FrameWorkFactory::NOT_MAT_FAC;
	}

	//	�O���t�B�b�N����I�u�W�F�N�g�̐���
	if ( m_pGraphics )
	{
		m_pGraphics->Create();
	}
	else
	{
		m_error |= FrameWorkFactory::NOT_GRA_FAC;
	}

	//	�O���t�B�b�N����n�̍\�z
	m_pGraphics->Initialize( this );

	//	�}�e���A������n�̍\�z
	m_pMaterial->Initialize( this );

	//	�V�X�e������n�̍\�z
	m_pSystem->Initialize( this );

	//	�e�R���|�[�l���g�̃C���X�^���X���擾
	m_pGraphicsManager	= m_pGraphics->GetComponent();
	m_pMaterialManager	= m_pMaterial->GetComponent();
	m_pSystemManager	= m_pSystem->GetComponent();

	//	�e�R���|�[�l���g������Ɏ擾�ł���������
	if ( m_pGraphicsManager == NULL )
	{
		m_error |= FrameWorkFactory::NOT_GRAPHICS;
	}
	if ( m_pMaterialManager == NULL )
	{
		m_error |= FrameWorkFactory::NOT_MATERIAL;
	}
	if ( m_pSystemManager == NULL )
	{
		m_error |= FrameWorkFactory::NOT_SYSTEM;
	}

	return (m_error == 0);
}
