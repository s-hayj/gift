//----------------------------------------------------------
//	@file	GraphicsManager.h
//
//	@memo	�O���t�B�b�N����n�𓝊����A������e�𒊏ۉ�����
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__GRAPHICS_MANAGER_H
#define	__GRAPHICS_MANAGER_H

#include "../IFrameComponent.h"

//----------------------------------------------------------
//	@name	GraphicsManager
//
//	@memo	�O���t�B�b�N�n�̊e����I�u�W�F�N�g�̏W���Ǘ�
//
//	@attrib	public abstract sub class
//
//	@base	public IFrameComponent
//
//	@author	sano-y
//	@data	2008-05-13	unfinished
//----------------------------------------------------------
class	GraphicsManager
	: public IFrameComponent
{
public:
	//----------------------------------------------------------
	//	@name	GraphicsManager::Reference
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
		//	@attrib	protected
		//----------------------------------------------------------
		virtual ~Reference(void) {};
	};

public:
	typedef	GraphicsManager::Reference	Ref;

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	GraphicsManager::GraphicsManager
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	GraphicsManager(void)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@attrib	public
	//----------------------------------------------------------
	virtual ~GraphicsManager(void)
	{
	};

	//----------------------------------------------------------
	//	�O���t�B�b�N����n�ւ̃A�N�Z�X�p�C���^�[�t�F�[�X���擾����
	//
	//	@name	GraphicsManager::GetReference
	//
	//	@memo	�Q�Ƃ݂̂����J����
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	GraphicsManager::Reference*	�A�N�Z�X�p�C���^�[�t�F�[�X
	//----------------------------------------------------------
	virtual GraphicsManager::Ref* GetReference(void) = 0;

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