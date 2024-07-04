//----------------------------------------------------------
//	@file	MaterialManager.h
//
//	@memo	�}�e���A������n�𓝊����A������e�𒊏ۉ�����
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__MATERIAL_MANAGER_H
#define	__MATERIAL_MANAGER_H

#include "../IFrameComponent.h"

//----------------------------------------------------------
//	@name	MaterialManager
//
//	@memo	�}�e���A���n�̊e����I�u�W�F�N�g�̏W���Ǘ�
//
//	@attrib	public abstract sub class
//
//	@base	public IFrameComponent
//
//	@author	sano-y
//	@data	2008-05-13	unfinished
//----------------------------------------------------------
class	MaterialManager
	: public IFrameComponent
{
public:
	//----------------------------------------------------------
	//	@name	MaterialManager::Reference
	//
	//	@memo	�K�v�Œ���i�s�ρj�̃C���^�[�t�F�[�X�����J����
	//
	//	@attrib	public nested interface
	//
	//	@author	sano-y
	//	@data	2008-05-08	unfinished
	//----------------------------------------------------------
	class Reference
	{
	public:
	protected:
		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@attrib	protected
		//----------------------------------------------------------
		virtual ~Reference(void) {};
	};

public:
	typedef	MaterialManager::Reference	Ref;
	
public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	MaterialManager::MaterialManager
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	MaterialManager(void)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	MaterialManager::~MaterialManager
	//
	//	@attrib	public
	//----------------------------------------------------------
	virtual ~MaterialManager(void)
	{
	};

	//----------------------------------------------------------
	//	�}�e���A������n�ւ̃A�N�Z�X�p�C���^�[�t�F�[�X���擾����
	//
	//	@name	MaterialManager::GetReference
	//
	//	@memo	�Q�Ƃ݂̂����J����
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	MaterialManager::Reference*	�A�N�Z�X�p�C���^�[�t�F�[�X
	//----------------------------------------------------------
	virtual MaterialManager::Ref* GetReference(void) = 0;

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