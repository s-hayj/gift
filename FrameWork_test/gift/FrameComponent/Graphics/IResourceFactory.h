//----------------------------------------------------------
//	@file	IResourceFactory.h
//
//	@memo	���\�[�X�f�[�^�̐����A�ǂݍ��ݑ���p�C���^�[�t�F�[�X
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------

#ifndef	__IRESOURCE_FACTORY_H
#define	__IRESOURCE_FACTORY_H

#include "../Material/Texture.h"

class	Texture;
class	Mesh;
struct	Texture::ReadOption;
struct	Mesh::ReadOption;
struct	Texture::CreateOption;
struct	Mesh::CreateOption;

//----------------------------------------------------------
//	@name	IResourceFactory
//
//	@memo	���\�[�X�f�[�^�̍쐬�Ɋւ��鑀��p�C���^�[�t�F�[�X
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-14	unfinished
//----------------------------------------------------------
class	IResourceFactory
{
public:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IResourceFactory::~IResourceFactory
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IResourceFactory(void) {};

	//----------------------------------------------------------
	//	�e�N�X�`���t�@�C������e�N�X�`���̓ǂݍ��݂��s��
	//
	//	@name	IResourceFactory::Load
	//
	//	@memo	�����̊i�[�I�u�W�F�N�g�͖߂�l�Ɠ����l�ɂȂ�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTexture	�e�N�X�`���̊i�[�p�I�u�W�F�N�g
	//	@param	(in/out)option	�ǂݍ��ݎ��ɕK�v�ȏ��Q
	//
	//	@return	Texture*	�ǂݍ��܂ꂽ�e�N�X�`�����
	//----------------------------------------------------------
	virtual Texture* Load( Texture* pTexture, Texture::ReadOption& option ) = 0;

	//----------------------------------------------------------
	//	���b�V���t�@�C�����烁�b�V���̓ǂݍ��݂��s��
	//
	//	@name	IResourceFactory::Load
	//
	//	@memo	�����̊i�[�I�u�W�F�N�g�͖߂�l�Ɠ����l�ɂȂ�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pMesh		���b�V���̊i�[�p�I�u�W�F�N�g
	//	@param	(in/out)option	�ǂݍ��ݎ��ɕK�v�ȏ��Q
	//
	//	@return	Mesh*	�ǂݍ��܂ꂽ���b�V�����
	//----------------------------------------------------------
	virtual Mesh* Load( Mesh* pMesh, Mesh::ReadOption& option ) = 0;

	//----------------------------------------------------------
	//	�e�N�X�`���f�[�^���쐬����
	//
	//	@name	IResourceFactory::Create
	//
	//	@memo	�����̊i�[�I�u�W�F�N�g�͖߂�l�Ɠ����l�ɂȂ�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTextrue	�e�N�X�`���̊i�[�p�I�u�W�F�N�g
	//	@param	(in/out)option	�쐬���ɕK�v�ȏ��Q
	//
	//	@return	Texture*	�쐬���ꂽ�e�N�X�`�����
	//----------------------------------------------------------
	virtual Texture* Create( Texture* pTexture, Texture::CreateOption& option ) = 0;

	//----------------------------------------------------------
	//	���b�V���f�[�^���쐬����
	//
	//	@name	IResourceFactory::Create
	//
	//	@memo	�����̊i�[�I�u�W�F�N�g�͖߂�l�Ɠ����l�ɂȂ�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pMesh		���b�V���̊i�[�p�I�u�W�F�N�g
	//	@param	(in/out)option	�쐬���ɕK�v�ȏ��Q
	//
	//	@return	Mesh*	�쐬���ꂽ���b�V�����
	//----------------------------------------------------------
	virtual Mesh* Create( Mesh* pMesh, Mesh::CreateOption& option ) = 0;
};

#endif