//----------------------------------------------------------
//	@file	Mesh.h
//
//	@memo	���b�V������Ɋւ��钊�ۃN���X
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__MESH_H
#define	__MESH_H

#include <stdio.h>
#include "../Graphics/IResourceFactory.h"
#include "ResourceManager.h;
#include "Resource.h"

class	IResourceFactory;
class	ResourceManager;

//----------------------------------------------------------
//	@name	Mesh
//
//	@memo	���b�V������p���ۃN���X
//
//	@attrib	public abstract sub class
//
//	@base	public Resource
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------
class	Mesh
	: public Resource
{
	//	�B��J�v�Z�����̖�������������Ώ�
	friend	ResourceManager;

public:
	//----------------------------------------------------------
	//	@name	Mesh::Property
	//
	//	@memo	��ԂɊւ�����i�[
	//
	//	@attrib	public nested sub struct
	//
	//	@base	public Resource::Property
	//
	//	@author	sano-y
	//	@data	2008-05-14	unfinished
	//----------------------------------------------------------
	struct	Property
		: public Resource::Property
	{
	public:

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	Mesh::Property::Property
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		Property(void)
		{
		};
	};


	//----------------------------------------------------------
	//	@name	Mesh::ReadOption
	//
	//	@memo	�t�@�C���ǂݍ��ݎ��ɕK�v�ȏ��i�[
	//
	//	@attrib	public nested sub struct
	//
	//	@base	public Resource::ReadOption
	//
	//	@author	sano-y
	//	@data	2008-05-14	unfinished
	//----------------------------------------------------------
	struct	ReadOption
		: public Resource::ReadOption
	{
	public:

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	Mesh::ReadOption::ReadOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		ReadOption(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[���������l�ɖ߂�
		//
		//	@name	Mesh::ReadOption::Initialize
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
			//	�p�����Ƃ̏���������
			this->Resource::ReadOption::Initialize();
		};
	};


	//----------------------------------------------------------
	//	@name	Mesh::CreateOption
	//
	//	@memo	���b�V���f�[�^�̍쐬���ɕK�v�ȏ��i�[
	//
	//	@attrib	public nested sub struct
	//
	//	@base	public Resource::CreateOption
	//
	//	@author	sano-y
	//	@data	2008-05-14	unfinished
	//----------------------------------------------------------
	struct	CreateOption
		: public Resource::CreateOption
	{
	public:
	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	Mesh::CreateOpetion::CreateOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		CreateOption(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[���������l�ɖ߂�
		//
		//	@name	Mesh::CreateOption::Initialize
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
			//	�p�����Ƃ̏���������
			this->Resource::CreateOption::Initialize();
		};
	};

protected:
	Mesh::Property	m_Property;	//	��ԂɊւ�����

public:
	//----------------------------------------------------------
	//	��ԏ����擾����
	//
	//	@name	Mesh::GetProperty
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(out)property	��ԏ����i�[����ϐ��ւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	void GetProperty( Mesh::Property& property )
	{
		property = m_Property;
	};

	//----------------------------------------------------------
	//	���b�V���f�[�^���������
	//
	//	@name	Mesh::Release
	//
	//	@memo	�Ăяo���ƁA���g���j�������
	//
	//	@attrib	public override
	//
	//	@base	Resource::Release
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Release(void)
	{
		//	�i�[���Ă��郊�\�[�X�f�[�^��j��
		Destroy();

		//	�����p��ID�Ǘ�����Ă���
		if ( m_Property.m_Entry )
		{
			Mesh* pTemp = NULL;

			//	�����Ώۂ��玩�g��j������
			Resource::s_pBank->Remove( m_Property.m_Id, pTemp );

			m_Property.m_Entry = false;
		}

		//	���g���p�ς݂ɂȂ������Ƃ�ʒm���A�݌ɍs���ɂ���
		Resource::s_pBank->Restore( this );
	};

protected:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	Mesh::Mesh
	//
	//	@memo	�h����ł̂ݐ����\
	//
	//	@attrib	protected
	//
	//	@param	none
	//----------------------------------------------------------
	Mesh(void)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	Mesh::~Mesh
	//
	//	@memo	�h����ł̂ݔj���\
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~Mesh(void)
	{
	};

	//	�h����Ŏ�������ׂ�����
	{
#if	0
	/*
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
	void Destroy(void)
	{
	};
	*/
#endif
	}

private:
	//----------------------------------------------------------
	//	���b�V���̓ǂݍ��ݏ��������s������
	//
	//	@name	Mesh::sLoading
	//
	//	@memo
	//
	//	@attrib	private static
	//
	//	@param	(in)pFactory	�ǂݍ��ݏ��������s����Ώ�
	//	@param	(in/out)option		�ǂݍ��ݎ��ɕK�v�ȏ��Q
	//
	//	@return	Mesh*	�ǂݍ��܂ꂽ���b�V���f�[�^
	//----------------------------------------------------------
	static Mesh* sLoading( IResourceFactory* pFactory,
		Mesh::ReadOption& option )
	{
		Mesh* pTemp = NULL;

		//	���b�V���i�[�̈���擾����
		Resource::s_pBank->Order( pTemp );

		//	���b�V����ǂݍ���
		return pFactory->Load( pTemp, option );
	};

	//----------------------------------------------------------
	//	���b�V���f�[�^�̍쐬�����s������
	//
	//	@name	Mesh::sCreating
	//
	//	@memo
	//
	//	@attrib	private static
	//
	//	@param	(in)pFactory	�쐬���������s����Ώ�
	//	@param	(in/out)option		�쐬���ɕK�v�ȏ��Q
	//
	//	@return	Mesh*	�쐬���ꂽ���b�V���f�[�^
	//----------------------------------------------------------
	static Mesh* sCreating( IResourceFactory* pFactory,
		Mesh::CreateOption& option )
	{
		Mesh* pTemp = NULL;
		
		//	���b�V���i�[�̈���擾����
		Resource::s_pBank->Order( pTemp );

		//	���b�V�����쐬����
		return pFactory->Create( option );
	};
};

#endif