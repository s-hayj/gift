//----------------------------------------------------------
//	@file	ResourceManager.h
//
//	@memo	���\�[�X�f�[�^�̑�����ꊇ���ĒS������
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__RESOURCE_MANAGER_H
#define	__RESOURCE_MANAGER_H

#include "../Graphics/IResourceFactory.h"
#include "ResourceBank.h"

class	IResourceFactory;
class	Texture;
class	Mesh;
struct	Texture::CreateOption;
struct	Texture::ReadOption;
struct	Mesh::CreateOption;
struct	Mesh::ReadOption;

//----------------------------------------------------------
//	@name	ResourceManager
//
//	@memo	���\�[�X�Ɋւ��鑀�������U��
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
class	ResourceManager
{
protected:
	int					m_Error;	//	�Ō�ɏo�͂��ꂽ�G���[�t���O
	IResourceFactory*	m_pFactory;	//	���\�[�X�����Ǘ�
	ResourceBank*		m_pBank;	//	���\�[�X�̃C���X�^���X�Ǘ�

public:
	//----------------------------------------------------------
	//	���\�[�X�t�@�C������e���\�[�X�f�[�^��ǂݍ���
	//
	//	@name	ResourceManager::Load
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	�ǂݍ��ރ��\�[�X�f�[�^�̌^
	//
	//	@param	(in/out)option	�ǂݍ��ݎ��ɕK�v�ȃf�[�^�Q
	//
	//	@return	T*	�ǂݍ��܂ꂽ���\�[�X�f�[�^�ւ̃|�C���^
	//----------------------------------------------------------
	template<class T>
		T* Load( typename T::ReadOption& option )
	{
		//	�t�@�C���̓ǂݍ��݊J�n
		T*	pTemp = typename T::Loading( m_pFactory, option );

		//	����ɓǂݍ��܂ꂽ
		if ( option.m_Error == 0 )
		{
			//	�����\�ɂ���
			if ( option.m_Entry )
			{
				option.m_Error |= m_pBank->Add( option.m_Id, pTemp );
			}
		}
		return pTemp;
	};

	//----------------------------------------------------------
	//	���\�[�X�f�[�^����e���\�[�X�𐶐�����
	//
	//	@name	ResourceManager::Create
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	�������ރ��\�[�X�f�[�^�̌^
	//
	//	@param	(in/out)option	�������ݎ��ɕK�v�ȃf�[�^�Q
	//
	//	@return	T*	�������܂ꂽ���\�[�X�f�[�^�ւ̃|�C���^
	//----------------------------------------------------------
	template<class T>
		T* Create( typename T::CreateOption& option )
	{
		//	�f�[�^�̏����o���J�n
		T* pTemp = typename T::Create( m_pFactory, option );

		//	����ɏ����o���ꂽ
		if ( option.m_Error == 0 )
		{
			//	�����\�ɂ���
			if ( option.m_Entry )
			{
				option.m_Error |= m_pBank->Add( option.m_Id, pTemp );
			}
		}
		return pTemp;
	};

	//----------------------------------------------------------
	//	�i�[���������\�[�X�f�[�^����������
	//
	//	@name	ResourceManager::GetResource
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	�擾���郊�\�[�X�̌^
	//
	//	@param	(in)id	�o�^���Ɏw�肵�������L�[
	//
	//	@return	T*	NULL �ȊO�Ȃ�A�w�肵�����\�[�X�f�[�^
	//----------------------------------------------------------
	template< class T >
		T* GetResource( int id )
	{
		T* pTemp = NULL;

		m_Error = 0x00;

		//	���\�[�X�f�[�^�̌���
		m_Error = m_pBank->Get( id, pTemp );

		//	��������̃G���[����������
		if ( m_Error )
		{
			//	���s�������Ƃɂ���
			pTemp = NULL;
		}
		return pTemp;
	};

	//----------------------------------------------------------
	//	�w�肵�����\�[�X���������j������
	//
	//	@name	ResourceManager::Erase
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	�j�����郊�\�[�X�̌^
	//
	//	@param	(in)id	�o�^���Ɏw�肵�������L�[
	//
	//	@return	none
	//----------------------------------------------------------
	template< class T >
		void Erase( int id )
	{
		T*	pTemp = NULL;

		m_Error = 0x00;

		//	�j�����郊�\�[�X�̌���
		m_Error = m_pBank->Remove( id, pTemp );

		//	�����ɐ���
		if ( m_Error == 0 )
		{
			typename T::Property property;

			//	��ԏ����擾
			pTemp->GetProperty( property );

			//	�����Ώۂ���O��
			property.m_Entry = false;

			//	���\�[�X�̔j��
			pTemp->Release();
		}
	};

	//----------------------------------------------------------
	//	�w�肵�����\�[�X��S�Ĕj������
	//
	//	@name	ResourceManager::Clear
	//
	//	@memo
	//
	//	@attrib	public template
	//
	//	@type	T	�j�����郊�\�[�X�̌^
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	template< class T >
		void Clear(void)
	{
		T*	pTemp = NULL;

		//	�Ǘ����̑S�Ẵ��\�[�X��j������
		m_pBank->Clear( pTemp );
	};

	//----------------------------------------------------------
	//	�Ō�ɔ��������G���[�t���O���擾����
	//
	//	@name	ResourceManager::LastError
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int LastError(void)
	{
		return m_Error;
	};

protected:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	ResourceManager::ResourceManager
	//
	//	@memo	�h����ł̂ݐ����\
	//
	//	@attrib	protected
	//
	//	@param	none
	//----------------------------------------------------------
	ResourceManager(void)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	ResourceManager::~ResourceManager
	//
	//	@memo	�h����ł̂ݔj���\
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~ResourceManager(void)
	{
	};
};

#endif