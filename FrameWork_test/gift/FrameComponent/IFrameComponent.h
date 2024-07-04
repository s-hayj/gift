//----------------------------------------------------------
//	@file	IFrameComponent.h
//
//	@memo	�t���[�����[�N���\������I�u�W�F�N�g����C���^�[�t�F�[�X
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__IFRAME_COMPONENT_H
#define	__IFRAME_COMPONENT_H


//----------------------------------------------------------
//	@name	IFrameComponent
//
//	@memo	�t���[�����[�N���`������I�u�W�F�N�g�Q�𒊏ۉ�����
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	IFrameComponent
{
public:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	virtual ~IFrameComponent(void) = 0;

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
};

#endif