//----------------------------------------------------------
//	@file	Texture.h
//
//	@memo	�e�N�X�`������Ɋւ��钊�ۃN���X
//
//	@author	snao-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__TEXTURE_H
#define	__TEXTURE_H

#include <stdio.h>
#include "../Graphics/IResourceFactory.h"
#include "ResourceManager.h"
#include "Resource.h"

class	IResourceFactory;
class	ResourceManager;

//----------------------------------------------------------
//	@name	Texture
//
//	@memo	�e�N�X�`������p���ۃN���X
//
//	@attrib	public abstract sub class
//
//	@base	public Resource
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------
class	Texture
	: public Resource
{
	//	�B��J�v�Z�����̖�����������Ώ�
	friend	ResourceManager;

public:
	//----------------------------------------------------------
	//	@name	Texture::Property
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
		//	@name	Texture::Property::Property
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
	//	@name	Texture::ReadOption
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
		//	@name	Texture::ReadOption::ReadOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		ReadOption(void)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	Texture::ReadOption::~ReadOption
		//
		//	@attrib	public
		//----------------------------------------------------------
		~ReadOption(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[��������������
		//
		//	@name	Texture::ReadOption::Initialize
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
	//	@name	Texture::CreateOption
	//
	//	@memo	�e�N�X�`���f�[�^���쐬���ɕK�v�ȏ��i�[
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
		//	@name	Texture::CreateOption::CreateOption
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		CreateOption(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[�f�[�^��������Ԃɖ߂�
		//
		//	@name	Texture::CreateOption::Initialize
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
	Texture::Property	m_Property;	//	��ԂɊւ�����

public:
	//----------------------------------------------------------
	//	��ԏ����擾����
	//
	//	@name	Texture::GetProperty
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(out)property	��ԏ����i�[����ϐ��ւ̎Q��
	//
	//	@return none
	//----------------------------------------------------------
	void GetProperty( Texture::Property& property )
	{
		property = m_Property;
	};

	//----------------------------------------------------------
	//	�e�N�X�`���f�[�^���������
	//
	//	@name	Texture::Release
	//
	//	@memo	�Ăяo���Ǝ��g���j�������
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
		//	�i�[���Ă��郊�\�[�X�f�[�^��j������
		Destroy();

		//	�����p��ID�Ǘ�����Ă���
		if ( m_Property.m_Entry )
		{
			Texture* pTemp = NULL;

			//	�����Ώۂ��玩�g��j������
			Resource::s_pBank->Remove( m_Property.m_Id, pTemp );

			m_Property.m_Entry = false;
		}

		//	�p�ς݂ɂȂ������Ƃ�ʒm���A�݌ɍs���ɂ���
		Resource::s_pBank->Restore( this );
	};

protected:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	Texture::Texture
	//
	//	@memo	�h����ł̂ݐ����\
	//
	//	@attrib	protected
	//
	//	@param	none
	//----------------------------------------------------------
	Texture(void)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	Texture::~Texture
	//
	//	@memo	�h����ł̂ݔj���\
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~Texture(void)
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
	//	�e�N�X�`���̓ǂݍ��ݏ��������s������
	//
	//	@name	Texture::sLoading
	//
	//	@memo
	//
	//	@attrib	private static
	//
	//	@param	(in)pFactory	�ǂݍ��ݏ��������s����Ώ�
	//	@param	(in/out)option		�ǂݍ��ݎ��ɕK�v�ȏ��Q
	//
	//	@return	Texture*	�ǂݍ��܂ꂽ�e�N�X�`���f�[�^
	//----------------------------------------------------------
	static Texture* sLoading( IResourceFactory* pFactory,
		Texture::ReadOption& option )
	{
		Texture* pTemp = NULL;

		//	�e�N�X�`���i�[�̈���擾����
		Resource::s_pBank->Order( pTemp );

		//	�e�N�X�`����ǂݍ���
		return pFactory->Load( pTemp, option );
	};

	//----------------------------------------------------------
	//	�e�N�X�`���f�[�^�̍쐬�����s������
	//
	//	@name	Texture::sCreating
	//
	//	@memo
	//
	//	@attrib	private static
	//
	//	@param	(in)pFactory	�쐬���������s����Ώ�
	//	@param	(in/out)option		�쐬���ɕK�v�ȏ��Q
	//
	//	@return	Texture*	�쐬���ꂽ�e�N�X�`���f�[�^
	//----------------------------------------------------------
	static Texture* sCreating( IResourceFactory* pFactory,
		Texture::CreateOption& option )
	{
		Texture* pTemp = NULL;

		//	�e�N�X�`���i�[�̈���擾����
		Resource::s_pBank->Order( pTemp );

		//	�e�N�X�`�����쐬����
		return pFactory->Create( pTemp, option );
	};
};

#endif