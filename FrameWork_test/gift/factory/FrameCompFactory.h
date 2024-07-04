//----------------------------------------------------------
//	@file	FrameCompFactory.h
//
//	@memo	�t���[�����[�N���\������e�v�f�̐������@���B������
//
//	@author	sano-y
//
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__FRAME_COMP_FACTORY_H
#define	__FRAME_COMP_FACTORY_H

#include <stdio.h>
//#include "FrameWorkFactory.h"

class	FrameWorkFactory;

//----------------------------------------------------------
//	@name	FrameCompFactory
//
//	@memo	�t���[�����[�N���\������R���|�[�l���g�𐶐�
//
//	@attrib	public template abstract class
//
//	@type	Component	��������R���|�[�l���g��
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
template<class Component>
class	FrameCompFactory
{
protected:
	Component*	m_pComponent;	//	���������R���|�[�l���g�̃C���X�^���X

private:
	bool	m_created;		//	���������R���|�[�l���g�̐ӔC�̗L��

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	FrameCompFactory(void)
		: m_pComponent( NULL ), m_created( false )
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	virtual ~FrameCompFactory(void)
	{
		//	�C���X�^���X���Ϗ����Ă��Ȃ�
		if ( m_created )
		{
			//	�C���X�^���X�̔j��
			Release();
		}
		m_created		= false;
		m_pComponent	= NULL;
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̐���
	//
	//	@name	FrameCompFactory::Create
	//
	//	@memo	�e���v���[�g�����̃I�u�W�F�N�g�𐶐�������
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Create(void)
	{
		//	�܂��������Ă��Ȃ�
		if ( !m_created )
		{
			//	�ӔC������
			m_created = true;

			//	�R���|�[�l���g�𐶐�����
			CreateComponent();
		}
	};

	//----------------------------------------------------------
	//	���������I�u�W�F�N�g�̏�����
	//
	//	@name	FrameCompFactory::Initialize
	//
	//	@memo	���������I�u�W�F�N�g�̏��������ɂ��悤����
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pFrameFactory	�t���[�����[�N���쐬����I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Initialize( const FrameWorkFactory* pFrameFactory ) = 0;

	//----------------------------------------------------------
	//	���������R���|�[�l���g���擾����
	//
	//	@name	FrameCompFactory::GetComponent
	//
	//	@memo	�ӔC���Ɛ��������R���|�[�l���g�̃C���X�^���X���Ϗ�����
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	Component*	���������R���|�[�l���g�̃C���X�^���X
	//----------------------------------------------------------
	Component* GetComponent(void)
	{
		m_created = false;

		return m_pComponent;
	};

protected:
	//----------------------------------------------------------
	//	�R���|�[�l���g�𐶐�����
	//
	//	@name	FrameCompFactory::CreateComponent
	//
	//	@memo	�R���|�[�l���g�𐶐�����
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void CreateComponent(void) = 0;

	//----------------------------------------------------------
	//	�R���|�[�l���g�̔j��
	//
	//	@name	FrameCompFactory::Release
	//
	//	@memo	���������R���|�[�l���g��j������
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Release(void) = 0;
};

#endif