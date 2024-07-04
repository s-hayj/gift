//----------------------------------------------------------
//	@file	SystemManager.h
//
//	@memo	�V�X�e������n�𓝊����A������e�𒊏ۉ�����
//
//	@author	sano-y
//	@data	2008-05-15	unfinished
//----------------------------------------------------------

#ifndef	__SYSTEM_MANAGER_H
#define	__SYSTEM_MANAGER_H

#include "../IFrameComponent.h"
#include "DriveManager.h"

//----------------------------------------------------------
//	@name	SystemManager
//
//	@memo	�V�X�e���n�̊e����I�u�W�F�N�g�̏W���Ǘ�
//
//	@attrib	public abstract sub class
//
//	@base	public IFrameComponent
//
//	@author	sano-y
//	@data	2008-05-15	unfinished
//----------------------------------------------------------
class	SystemManager
	: public IFrameComponent
{
public:
	//----------------------------------------------------------
	//	@name	SystemManager::Reference
	//
	//	@memo	�K�v�Œ���i�s�ρj�̃C���^�[�t�F�[�X�����J����
	//
	//	@attrib	public nested interface
	//
	//	@author	sano-y
	//	@data	2008-05-08	unfinished
	//----------------------------------------------------------
	class	Reference
	{
	public:
	protected:
		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	SystemManager::Reference::~Reference
		//
		//	@attrib	protected
		//----------------------------------------------------------
		virtual ~Reference(void) {};
	};

public:
	typedef	SystemManager::Reference	Ref;

protected:
	DriveManager*	m_pDriveManager;	//	�O������Ǘ�

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	SystemManager::SystemManager
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	SystemManager(void)
		: m_pDriveManager( NULL )
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	SystemManager::~SystemManager
	//
	//	@attrib	public
	//----------------------------------------------------------
	virtual ~SystemManager(void)
	{
	};

	//----------------------------------------------------------
	//	�V�X�e������n�ւ̃A�N�Z�X�p�C���^�[�t�F�[�X���擾����
	//
	//	@name	SystemManager::GetReference
	//
	//	@memo	�Q�Ƃ݂̂����J����
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	SystemManager::Reference*	�A�N�Z�X�p�C���^�[�t�F�[�X
	//----------------------------------------------------------
	virtual SystemManager::Ref* GetReference(void) = 0;

#if 0	//	�v�I�[�o�[���C�h���\�b�h
	//----------------------------------------------------------
	//	��Ԃ̍X�V
	//
	//	@name	IFrameComponent::Update
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	int	���b�Z�[�W�t���O
	//----------------------------------------------------------
	virtual int Update(void) = 0;

	//----------------------------------------------------------
	//	�j��
	//
	//	@name	IFrameComponent::Release
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	int	�O�ȊO	���g�̔j�����Ϗ�
	//----------------------------------------------------------
	virtual int Release(void) = 0;
#endif
};

#endif