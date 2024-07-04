//----------------------------------------------------------
//	@file	IResourceCollection.h
//
//	@memo	�����\�Ȋe���\�[�X�W�����Ǘ����邽�߂̃I�y���[�V�������
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__IRESOURCE_COLLECTION_H
#define	__IRESOURCE_COLLECTION_H

#include <stdio.h>
#include <assert.h>

//----------------------------------------------------------
//	@name	IResourceCollection
//
//	@memo	�e���\�[�X�̏W�����Ǘ����A�����Q�Ɖ\�ɂ���
//
//	@attrib	public template abstract class
//
//	@type	T	�Ǘ����郊�\�[�X�̌^
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
template< class T >
class	IResourceCollection
{
public:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IResourceCollection::~IResourceCollection
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~ResourceCollection(void) {};

	//----------------------------------------------------------
	//	���\�[�X������ID�Ƌ��ɊǗ����ɒǉ�����
	//
	//	@name	IResourceCollection::Add
	//
	//	@memo	�o�^ID�͏d�����邱�Ƃ��ł��Ȃ��̂ŁA�G���[
	//
	//	@attrib	public abstract
	//
	//	@param	(in)id			��������ۂ̃L�[
	//	@param	(in)resource	�i�[���郊�\�[�X�f�[�^�ւ̎Q��
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	virtual int Add( int id, T& resource ) = 0;

	//----------------------------------------------------------
	//	�w�胊�\�[�X��������擾����
	//
	//	@name	IResourceCollection::Get
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)id			�o�^�����Ƃ��̌����L�[
	//	@param	(out)resource	�w�胊�\�[�X�i�[��ւ̎Q��
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	virtual int Get( int id, T& resource ) = 0;

	//----------------------------------------------------------
	//	�w�肵�����\�[�X���Ǘ�������O��
	//
	//	@name	IResourceCollection::Remove
	//
	//	@memo	���\�[�X�W������O���݂̂ŁA���\�[�X�j���͍s��Ȃ�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)id			�o�^�����Ƃ��̌����L�[
	//	@param	(out)resource	�Ǘ�������O���ꂽ���\�[�X�i�[��ւ̎Q��
	//
	//	@return	int	�O�ȊO�Ȃ�A�G���[�t���O
	//----------------------------------------------------------
	virtual int Remove( int id, T& resource ) = 0;

	//----------------------------------------------------------
	//	�i�[���Ă���S�Ẵ��\�[�X�����\�[�X�f�[�^�Ƌ��ɔj������
	//
	//	@name	IResourceCollection::Clear
	//
	//	@memo	�i�[���Ă���S�Ẵ��\�[�X��j������
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Clear(void) = 0;
};

#endif