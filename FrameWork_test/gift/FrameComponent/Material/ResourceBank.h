//----------------------------------------------------------
//	@file	ResourceBank.h
//
//	@memo	���\�[�X����I�u�W�F�N�g�̃C���X�^���X�Ǘ�
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__RESOURCE_BANK_H
#define	__RESOURCE_BANK_H

#include "Mesh.h"
#include "Texture.h"
#include "../../lib/ObjectBank.h"
#include "IResourceCollection.h"

//----------------------------------------------------------
//	@name	ResourceBank
//
//	@memo	���\�[�X�Ȃ�тɃ��\�[�X�A�_�v�^�[�̍݌ɊǗ�
//
//	@attrib	public class
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------
class	ResourceBank
{
private:
	ObjectBank< Mesh* >		m_MeshBank;		//	���b�V���̃A�_�v�^�[�Ǘ�
	ObjectBank< Texture* >	m_TextureBank;	//	�e�N�X�`���̃A�_�v�^�[�Ǘ�

	IResourceCollection< Mesh* >*		m_pMeshCollection;		//	���b�V���̏W��
	IResourceCollection< Texture* >*	m_pTextureCollection;	//	�e�N�X�`���̏W��

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	ResourceBank::ResourceBank
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	ResourceBank(void);

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	ResourceBank::~ResourceBank
	//
	//	@attrib	public
	//----------------------------------------------------------
	~ResourceBank(void);

	//----------------------------------------------------------
	//	���b�V���̏W���Ǘ����@��o�^����
	//
	//	@name	ResourceBank::RegisterCollection
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pCollection	���b�V���̏W���Ǘ��I�u�W�F�N�g
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int RegisterCollection( IResourceCollection< Mesh* >* pCollection );

	//----------------------------------------------------------
	//	�e�N�X�`���̏W���Ǘ����@��o�^����
	//
	//	@name	ResourceBank::RegisterCollection
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pCollection	�e�N�X�`���̏W���Ǘ��I�u�W�F�N�g
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int RegisterCollection( IResourceCollection< Texture* >* pCollection );

	//----------------------------------------------------------
	//	���b�V���̊i�[�̈�̐����A�j�����@��o�^����
	//
	//	@name	ResourceBank::RegisterNewDelManager
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)manager	���b�V���̊i�[�I�u�W�F�N�g�̐����A�j�����@
	//
	//	@return	none
	//----------------------------------------------------------
	void RegisterNewDelManager( NewDelManager< Mesh* >& manager );

	//----------------------------------------------------------
	//	�e�N�X�`���̊i�[�̈�̐����A�j�����@��o�^����
	//
	//	@name	ResourceBank::RegisterNewDelManager
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)manager	�e�N�X�`���̊i�[�I�u�W�F�N�g�̐����A�j�����@
	//
	//	@return	none
	//----------------------------------------------------------
	void RegisterNewDelManager( NewDelManager< Texture* >& manager );

	//----------------------------------------------------------
	//	���b�V���f�[�^������ID�Ƌ��ɊǗ�������
	//
	//	@name	ResourceBank::Add
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id		��������ۂ̃L�[
	//	@param	(in)pMesh	�i�[���郁�b�V���f�[�^
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int Add( int id, Mesh* pMesh );

	//----------------------------------------------------------
	//	�e�N�X�`���f�[�^������ID�Ƌ��ɊǗ�������
	//
	//	@name	ResourceBank::Add
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id			��������ۂ̃L�[
	//	@param	(in)pTexture	�i�[����e�N�X�`���f�[�^
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int Add( int id, Texture* pTexture );

	//----------------------------------------------------------
	//	�w�胁�b�V���f�[�^���������Q�Ƃ���
	//
	//	@name	ResourceBank::Get
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id		��������ۂ̃L�[
	//	@param	(out)pMesh	�������ʂ��i�[����
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int Get( int id, Mesh*& pMesh );

	//----------------------------------------------------------
	//	�w��e�N�X�`���f�[�^���������Q�Ƃ���
	//
	//	@name	ResourceBank::Get
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id			��������ۂ̃L�[
	//	@param	(out)pTexture	�������ʂ��i�[����
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int Get( int id, Texture*& pTexture );

	//----------------------------------------------------------
	//	�w�胁�b�V���������Ώۂ���O��
	//
	//	@name	ResourceBank::Remove
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id		�o�^���Ɏw�肵�������L�[
	//	@param	(out)pMesh	�O���ꂽ���b�V���ւ̃|�C���^
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int Remove( int id, Mesh*& pMesh );

	//----------------------------------------------------------
	//	�w��e�N�X�`���������Ώۂ���O��
	//
	//	@name	ResourceBank::Remove
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)id			�o�^���Ɏw�肵�������L�[
	//	@param	(out)pTexture	�O���ꂽ�e�N�X�`���ւ̃|�C���^
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	int Remove( int id, Texture*& pTexture );

	//----------------------------------------------------------
	//	�Ǘ����Ă���S�Ẵ��b�V���f�[�^��j������
	//
	//	@name	ResourceBank::Clear
	//
	//	@memo	�I�[�o�[���[�h���邽�߂ɂ킴�킴����������
	//
	//	@attrib	public
	//
	//	@param	(in)pMesh	�j�����郊�\�[�X�^���ʗp
	//
	//	@return	none
	//----------------------------------------------------------
	void Clear( Mesh* pMesh );

	//----------------------------------------------------------
	//	�Ǘ����Ă���S�Ẵe�N�X�`���f�[�^��j������
	//
	//	@name	ResourceBank::Clear
	//
	//	@memo	�I�[�o�[���[�h���邽�߂ɂ킴�킴����������
	//
	//	@attrib	public
	//
	//	@param	(in)pTexture	�j�����郊�\�[�X�^���ʗp
	//
	//	@return	none
	//----------------------------------------------------------
	void Clear( Texture* pTexture );

	//----------------------------------------------------------
	//	���b�V���f�[�^�p�̃��\�[�X�A�_�v�^�[���擾����
	//
	//	@name	ResourceBank::Order
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(out)pMesh	���b�V���A�_�v�^�[�̊i�[��|�C���^�ւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	void Order( Mesh*& pMesh );

	//----------------------------------------------------------
	//	�e�N�X�`���f�[�^�p�̃��\�[�X�A�_�v�^�[���擾����
	//
	//	@name	ResourceBank::Order
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(out)pTexture	�e�N�X�`���A�_�v�^�[�̊i�[��|�C���^�ւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	void Order( Texture*& pTexture );

	//----------------------------------------------------------
	//	�w�胁�b�V����q�ɂ֕ԋp����
	//
	//	@name	ResourceBank::Restore
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pMesh	�ԋp����郁�b�V���ւ̃|�C���^
	//
	//	@return	none
	//----------------------------------------------------------
	void Restore( Mesh* pMesh );

	//----------------------------------------------------------
	//	�w��e�N�X�`����q�ɂ֕ԋp����
	//
	//	@name	ResourceBank::Restore
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pTexture	�ԋp�����e�N�X�`���ւ̃|�C���^
	//
	//	@return	none
	//----------------------------------------------------------
	void Restore( Texture* pTexture );
};

#endif