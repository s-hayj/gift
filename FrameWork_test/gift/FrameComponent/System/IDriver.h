//----------------------------------------------------------
//	@file	IDriver.h
//
//	@memo	��ɊO����񐧌�I�u�W�F�N�g�̊��N���X
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------

#ifndef	__IDRIVER_H
#define	__IDRIVER_H

#include <string>
#include "DriveManager.h"

class	IDriveObserver;
class	DriveManager;

//----------------------------------------------------------
//	@name	IDriver
//
//	@memo	���b�Z�[�W�̑��M�\�Ȏ��Ӌ@�퐧��C���^�[�t�F�[�X
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
class	IDriver
{
	//	���g�̃J�v�Z�����𖳌�������B��̑Ώ�
	friend	DriveManager;

public:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IDriver::~IDriver
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IDriver(void) {};

	//----------------------------------------------------------
	//	�h���C�o�̎��ʖ����擾����
	//
	//	@name	IDriver::Name
	//
	//	@memo	���ʂ��邽�߂̔h����ŗL�f�[�^���Q��
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	std::string	����h���C�o�̖��O
	//----------------------------------------------------------
	virtual std::string Name(void) = 0;

	//----------------------------------------------------------
	//	�o�^����Ă���h���C�o���ł̏����D��x���擾����
	//
	//	@name	IDriver::GetPriority
	//
	//	@memo	�l���������قǁA�D��x�������Ȃ�B�d�������ꍇ�͐ڑ���
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	int		�����D��x
	//----------------------------------------------------------
	virtual int GetPriority(void) = 0;

	//----------------------------------------------------------
	//	���b�Z�[�W�̑��M���o�^����
	//
	//	@name	IDriver::Add
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pObserver	���b�Z�[�W����M����I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Add( IDriveObserver* pObserver ) = 0;

	//----------------------------------------------------------
	//	���b�Z�[�W�̑��M�Ώۂ���O��
	//
	//	@name	IDriver::Erase
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pObserver	���M�Ώۂ���O���I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Erase( IDriveObserver* pObserver ) = 0;

protected:
	//----------------------------------------------------------
	//	������
	//
	//	@name	IDriver::Initialize
	//
	//	@memo	�h���C�o�}�l�[�W���[�ɐڑ����ꂽ�Ƃ��ɌĂяo�����
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Initialize(void) = 0;

	//----------------------------------------------------------
	//	���Z�b�g����
	//
	//	@name	IDriver::Terminate
	//
	//	@memo	�h���C�o�}�l�[�W���[�̊Ǘ�������O���ꂽ�Ƃ��ɌĂяo�����
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Terminate(void) = 0;

	//----------------------------------------------------------
	//	��Ԃ��X�V������
	//
	//	@name	IDriver::Update
	//
	//	@memo	�h���C�u�}�l�[�W���[�ȊO��������Ăяo���Ă͂����Ȃ�
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Update(void) = 0;

	//----------------------------------------------------------
	//	���b�Z�[�W�𑗐M����
	//
	//	@name	IDriver::Notify
	//
	//	@memo	���g�𑗐M���Ă���̂ŁA���b�Z�[�W�̉��߂͑��M�悪�s��
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Notify(void) = 0;
};


//----------------------------------------------------------
//	@name	IDriveObserver
//
//	@memo	�h���C�o�̃��b�Z�[�W����M����
//
//	@attirb	public interface
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
class	IDriveObserver
{
public:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IDriveObserver::~IDriveObserver
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IDriveObserver(void) {};

	//----------------------------------------------------------
	//	�h���C�o����̃��b�Z�[�W���󂯎��
	//
	//	@name	IDriveObserver::Update
	//
	//	@memo	�h���C�o��������̂ŁA���b�Z�[�W���e�̉��߂͎����悪�s��
	//
	//	@attirb	public abstract
	//
	//	@param	(in)pDriver		���b�Z�[�W�������h���C�o���g
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Update( IDriver* pDriver ) = 0;
};

#endif