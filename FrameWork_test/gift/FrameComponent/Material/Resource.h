//----------------------------------------------------------
//	@file	Resource.h
//
//	@memo	���\�[�X�̊��N���X�A��ɔj���Ɋւ���I�y���[�V�������
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__RESOURCE_H
#define	__RESOURCE_H

#include "ResourceBank.h"

class	ResourceBank;

//----------------------------------------------------------
//	@name	Resource
//
//	@memo	���\�[�X�A�_�v�^�[�̔j���Ɋւ���C���^�[�t�F�[�X���
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
class	Resource
{
protected:
	//----------------------------------------------------------
	//	@name	Resource::Property
	//
	//	@memo	�e���\�[�X�̏�Ԃ�\�����ʂ̃f�[�^
	//
	//	@attrib	protected nested struct
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	struct	Property
	{
	public:
		bool	m_Entry;	//	�������X�g�o�^�̗L��
		int		m_Id;		//	�o�^����Ă���ԍ�

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	Resource::Property::Property
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		Property(void)
			: m_Entry( false ), m_Id( 0 )
		{
		};
	};


	//----------------------------------------------------------
	//	@name	Resource::ReadOption
	//
	//	@memo	�e���\�[�X�ǂݍ��ݎ��ɕK�v�ȋ��ʂ̃f�[�^
	//
	//	@attrib	protected nested struct
	//
	//	@author	snao-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	struct	ReadOption
	{
	public:
		char*	m_pName;	//	�ǂݍ��ރt�@�C���p�X
		bool	m_Entry;	//	�C���X�^���X�̒����Ǘ��̗L��
		int		m_Id;		//	�����Ǘ����̎��ʔԍ�
		int		m_Error;	//	�������̃G���[�t���O

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	Resource::ReadOption::ReadOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		ReadOption(void)
			: m_pName( NULL ), m_Entry( false ), m_Id( 0 ), m_Error( 0x00 )
		{
		};

		//----------------------------------------------------------
		//	�i�[���������l�ɖ߂�
		//
		//	@name	Resource::ReadOption::Initialize
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	none
		//----------------------------------------------------------
		void Initialize(void)
		{
			m_pName	= NULL;
			m_Entry	= false;
			m_Id	= 0;
			m_Error	= 0x00;
		};
	};

	//----------------------------------------------------------
	//	@name	Resource::CreateOption
	//
	//	@memo	�e���\�[�X�������ɕK�v�ȋ��ʂ̃f�[�^
	//
	//	@attrib	protected nested struct
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	struct	CreateOption
	{
	public:
		bool	m_Entry;	//	�C���X�^���X�̒����Ǘ��̗L��
		int		m_Id;		//	�����Ǘ����̎��ʔԍ�
		int		m_Error;	//	�������̃G���[�t���O

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	Resource::CreateOption::CreateOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		CreateOption(void)
			: m_Entry( false ), m_Id( 0 ), m_Error( 0x00 )
		{
		};

		//----------------------------------------------------------
		//	�i�[�f�[�^�������l�ɖ߂�
		//
		//	@name	Resource::CreateOption::Initialize
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	none
		//----------------------------------------------------------
		void Initialize(void)
		{
			m_Entry	= false;
			m_Id	= 0;
			m_Error	= 0x00;
		};
	};

protected:
	static ResourceBank*	s_pBank;	//	���\�[�X�̃C���X�^���X�Ǘ�

public:
	//----------------------------------------------------------
	//	���\�[�X�A�_�v�^�[�̕ԋp�ƁA���\�[�X�f�[�^�̔j�������s
	//
	//	@name	Resource::Release
	//
	//	@memo	�i�[�f�[�^�Ȃ�тɁA���g���j�������
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Release(void) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	Resource::~Resource
	//
	//	@memo	�h����ł̂ݔj���\
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~Resource(void) {};

	//----------------------------------------------------------
	//	�i�[���Ă��郊�\�[�X�f�[�^��j������
	//
	//	@name	Resource::Destroy
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Destroy(void) = 0;
};

#endif