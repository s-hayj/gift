//----------------------------------------------------------
//	@file	DriveManager.h
//
//	@memo	�O������p�I�u�W�F�N�g�̊i�[�Ǘ�
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------

#ifndef	__DRIVE_MANAGER_H
#define	__DRIVE_MANAGER_H

#include <stdio.h>
#include <assert.h>
#include "IDriver.h"

class	IDriver;

//----------------------------------------------------------
//	@name	DriveManager
//
//	@memo	�O������I�u�W�F�N�g�̏W���Ǘ�������s��
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
class	DriveManager
{
public:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	DriveManager::DriveManager
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IDriveManager(void)
	{
	};

	//----------------------------------------------------------
	//	�h���C�o�̐ڑ����s��
	//
	//	@name	DriveManager::Connect
	//
	//	@memo	�h�����Ă� DriveManager::Connect ���Ăяo������
	//
	//	@attrib	public virtual
	//
	//	@param	(in)pDriver		�Ǘ����ɂ����h���C�o
	//
	//	@return	bool	true �Ȃ�A����ɐڑ����ꂽ
	//----------------------------------------------------------
	virtual bool Connect( IDriver* pDriver )
	{
		//	�ڑ��Ώۂ����݂���
		ASSERT( pDriver != NULL );

		//	�ڑ����̏���������
		pDriver->Initialize();

		return true;
	};

	//----------------------------------------------------------
	//	�w��h���C�o���Ǘ�������O��
	//
	//	@name	DriveManager::Disconnect
	//
	//	@memo	�h�����Ă� DriveManager::Disconnect ���Ăяo������
	//
	//	@attrib	public virtual
	//
	//	@param	(in)pDriver		�Ǘ�������O���h���C�o
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Disconnect( IDriver* pDriver )
	{
		//	�ڑ��Ώۂ����݂���
		ASSERT( pDriver != NULL );

		//	�Ǘ�����O�����Ƃ��̏���
		pDriver->Terminate();
	};

	//----------------------------------------------------------
	//	�Ǘ����̃h���C�o���������A�ړI�̃h���C�o���Q��
	//
	//	@name	DriveManager::Get
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pName	�����ɗ��p����h���C�o���ʖ�
	//
	//	@return	IDriver*	NULL �ȊO�Ȃ�A�w��h���C�o�ւ̃|�C���^
	//----------------------------------------------------------
	virtual IDriver* Get( char* pName ) = 0;

	//----------------------------------------------------------
	//	�Ǘ����̃h���C�o�̊e�폈�������s����
	//
	//	@name	DriveManager::Execute
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Execute(void) = 0;
};

#endif