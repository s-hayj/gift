//----------------------------------------------------------
//	@file	FrameWork.h
//
//	@memo	�t���[�����[�N���\�����A���̐U�镑���𒊏ۉ�����
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__FRAMEWORK_H
#define	__FRAMEWORK_H

#include <stdio.h>
#include <map>
#include "../factory/FrameCompFactory.h"
#include "System/SystemManager.h"
#include "Material/MaterialManager.h"
#include "Graphics/GraphicsManager.h"

//----------------------------------------------------------
//	@name	FrameWork
//
//	@memo	�t���[�����[�N�̍\����`�A�U�镑���͒��ۉ�
//
//	@attrib	public abstract class
//
//	author	sano-y
//	data	2008-05-13	unfinished
//----------------------------------------------------------
class	FrameWork
{
public:
	static const int	NORMAL_EXIT = 0x0001;	//	����I��
	static const int	EXCEPTION	= 0x0002;	//	��O

protected:
	SystemManager*		m_pSystem;		//	�V�X�e������n
	MaterialManager*	m_pMaterial;	//	�}�e���A������n
	GraphicsManager*	m_pGraphics;	//	�O���t�B�b�N����n

	std::map< int, IFrameComponent* >	m_FrameComp;	//	�\�����e�i�[

	int		m_message;	//	���b�Z�[�W�t���O

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	FrameWork::FrameWork
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	FrameWork(void);

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	FrameWork::~FrameWork
	//
	//	@attrib	public
	//----------------------------------------------------------
	virtual ~FrameWork(void);

	//----------------------------------------------------------
	//	������
	//
	//	@name	FrameWork::Initialize
	//
	//	@memo	�t���[�����[�N�̍\����g�ݗ��Ă�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pSystem		�V�X�e������n�I�u�W�F�N�g
	//	@param	(in)pMaterial	�}�e���A������n�I�u�W�F�N�g
	//	@param	(in)pGraphics	�O���t�B�b�N����n�I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Initialize( SystemManager* pSystem,
		MaterialManager* pMaterial, GraphicsManager* pGraphics) = 0;

	//----------------------------------------------------------
	//	�j��
	//
	//	@name	FrameWork::Release
	//
	//	@memo	�t���[�����[�N�̍\����j������
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Release(void) = 0;

	//----------------------------------------------------------
	//	�V�X�e������n�փA�N�Z�X
	//
	//	@name	FrameWork::GetSystem
	//
	//	@memo	�Q�Ƃ݂̂����n
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	SystemManager::Reference*	�V�X�e���n�ւ̃|�C���^
	//----------------------------------------------------------
	SystemManager::Ref* GetSustem(void)
	{
		return m_pSystem->GetReference();
	};

	//----------------------------------------------------------
	//	�}�e���A������n�փA�N�Z�X
	//
	//	@name	FrameWork::GetMaterial
	//
	//	@memo	�Q�Ƃ݂̂����n
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	MaterialManager::Reference*	�}�e���A���n�ւ̃|�C���^
	//----------------------------------------------------------
	MaterialManager::Ref* GetMaterial(void)
	{
		return m_pMaterial->GetReference();
	};

	//----------------------------------------------------------
	//	�O���t�B�b�N����n�փA�N�Z�X
	//
	//	@name	FrameWork::GetGraphics
	//
	//	@memo	�Q�Ƃ݂̂����n
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	GraphicsManager::Reference*	�O���t�B�b�N�n�ւ̃|�C���^
	//----------------------------------------------------------
	GraphicsManager::Ref* GetGraphics(void)
	{
		return m_pGraphics->GetReference();
	};

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
	virtual void Execute(void);

	//----------------------------------------------------------
	//	�I���t���O���擾����
	//
	//	@name	FrameWork::Exit
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true	�I��
	//----------------------------------------------------------
	virtual bool Exit(void) = 0;

	//----------------------------------------------------------
	//	���b�Z�[�W�t���O���擾
	//
	//	@name	FrameWork::GetMessage
	//
	//	@memo	�Ō�ɔ��s���ꂽ���b�Z�[�W�t���O���擾
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	int	�O�ȊO	���b�Z�[�W�t���O
	//----------------------------------------------------------
	int GetMessage(void)
	{
		return m_message;
	};
};

#endif