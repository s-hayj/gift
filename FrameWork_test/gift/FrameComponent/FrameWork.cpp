//----------------------------------------------------------
//	@file	FrameWork.cpp
//
//	@memo	�t���[�����[�N���\�����A���̐U�镑���𒊏ۉ�����
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#include "FrameWork.h"

//----------------------------------------------------------
//	�R���X�g���N�^
//
//	@name	FrameWork::FrameWork
//
//	@attrib	public
//
//	@param	none
//----------------------------------------------------------
FrameWork::FrameWork(void)
:	m_pSystem( NULL ), m_pMaterial( NULL ), m_pGraphics( NULL ),
	m_message( 0x00 ), m_FrameComp()
{
}

//----------------------------------------------------------
//	�f�X�g���N�^
//
//	@attrib	public
//----------------------------------------------------------
FrameWork::~FrameWork(void)
{
	//	�t���[�����[�N�̔j��
	Release();
}

//----------------------------------------------------------
//	�t���[�����[�N���̏��������s����
//
//	@name	FrameWork::Execute
//
//	@memo	�f�t�H���g�̐U�镑�����`
//
//	@attrib	public virtual
//
//	@param	none
//
//	@return	none
//----------------------------------------------------------
void FrameWork::Execute(void)
{
	std::map< int, IFrameComponent* >::iterator i;

	//	���b�Z�[�W�̏�����
	m_message = 0;

	//	�e�t���[�����[�N�\���v�f�̍X�V
	for ( i = m_FrameComp.begin(); i != m_FrameComp.end(); ++i )
	{
		//	�X�V�ƃ��b�Z�[�W�̒ǉ�
		m_message |= (*i).second->Update();
	}
}
