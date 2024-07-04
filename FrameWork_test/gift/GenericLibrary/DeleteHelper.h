//----------------------------------------------------------
// file name: DeleteHelper.h
//
// memo: �C���X�^���X�̔j�����@���w�肵�ĈϏ�����N���X
//----------------------------------------------------------

#ifndef	__DELETE_HELPER_H
#define	__DELETE_HELPER_H

#include <assert.h>
#include "ICommand.h"

namespace gift
{

//----------------------------------------------------------
// name: gift::DeleteHelper
//
// attrib: template final class
//
// memo: �C���X�^���X�̔j�����@���w�肵�āA���s����
//----------------------------------------------------------
template<bool is_Delete_ReleaseMethod = false>
class DeleteHelper
{
private:
	//----------------------------------------------------------
	// name: gift::DeleteHelper::Select
	//
	// attrib: private template sub class
	//
	// base: gift::ICommand is interface
	//
	// typename: bool �c true �̂Ƃ��A���̃I�u�W�F�N�g�����������
	// typename: T �c �j������I�u�W�F�N�g�̌^
	//
	// memo: Release() �����o�֐��ɂ���āA�I�u�W�F�N�g�j�������s����
	//----------------------------------------------------------
	template<bool flag, class T>
	class Select
		: public ICommand
	{
	private:
		T* _pObj;	//	�j������I�u�W�F�N�g�ւ̃|�C���^

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		// parameter: (in)T* pObj �c �j������I�u�W�F�N�g�ւ̃|�C���^
		//----------------------------------------------------------
		Select(T* pObj)
		{
			_pObj = pObj;
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//----------------------------------------------------------
		~Select(void)
		{
			//	�܂��j������Ă��Ȃ�����
			if (_pObj != NULL)
			{
				this->Execute();
			}
		};

		//----------------------------------------------------------
		//	�j�����������s����
		//
		// attrib: override
		//----------------------------------------------------------
		void Execute(void)
		{
			_pObj->Release();
			_pObj = NULL;
		};
	};

	//----------------------------------------------------------
	// name: gift::DeleteHelper::Select
	//
	// attrib: private template sub class
	//
	// base: gift::ICommand is interface
	//
	// typename: T �c �j������I�u�W�F�N�g�̌^
	//
	// memo: delete ���Z�q�ɂ���āA�I�u�W�F�N�g��j������
	//----------------------------------------------------------
	template<class T>
	class Select<false, T>
		: public ICommand
	{
	private:
		T* _pObj;	//	�j������I�u�W�F�N�g�ւ̃|�C���^

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		// parameter: (in)T* pObj �c �j������I�u�W�F�N�g�ւ̃|�C���^
		//----------------------------------------------------------
		Select(T* pObj)
		{
			_pObj = pObj;
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//----------------------------------------------------------
		~Select(void)
		{
			//	�܂��j������Ă��Ȃ�����
			if (_pObj != NULL)
			{
				this->Execute();
			}
		};

		//----------------------------------------------------------
		//	�j�����������s����
		//
		// attrib: override
		//----------------------------------------------------------
		void Execute(void)
		{
			delete _pObj;
			_pObj = NULL;
		};
	};

private:
	ICommand* _pCommand;	//	�I�u�W�F�N�g�j�������Ăяo���p

public:
	//----------------------------------------------------------
	//	�R�s�[�R���X�g���N�^
	//
	// parameter: (in)DeleteHelper<is_Delete_ReleaseMethod>& obj �c �R�s�[���ւ̎Q��
	//----------------------------------------------------------
	DeleteHelper(DeleteHelper<is_Delete_ReleaseMethod>& obj)
	{
		_pCommand = obj._pCommand;

		_pCommand = NULL;
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)T* pObj �c �j������I�u�W�F�N�g�ւ̃|�C���^
	//----------------------------------------------------------
	template<class T>
		DeleteHelper(T* pObj)
		: _pCommand(NULL)
	{
		assert(pObj != NULL);

		_pCommand = new Select<is_Delete_ReleaseMethod, T>(pObj);
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~DeleteHelper(void)
	{
		//	�j���������Ăяo��
		(*this)();
	};

	//----------------------------------------------------------
	//	�j�����������s����
	//----------------------------------------------------------
	void operator ()(void)
	{
		//	�܂��I�u�W�F�N�g���j������Ă��Ȃ�
		if (_pCommand != NULL)
		{
			//	�Ǝ��̃I�u�W�F�N�g�j�����������s
			_pCommand->Execute();

			//	�j�������I�u�W�F�N�g�̔j��
			delete _pCommand;

			_pCommand = NULL;
		}
	};

	//----------------------------------------------------------
	//	�j���������s�I�u�W�F�N�g���󂯓n��
	//
	// return: ICommand* �c �j�����������s����I�u�W�F�N�g�ւ̃|�C���^
	//
	// memo: �ÖٓI�^�ϊ��ɂ��A�j�������I�u�W�F�N�g���O���ɈϏ�����
	//�@�@�@�Ϗ����ꂽ�҂́AICommand �I�u�W�F�N�g�̔j����K�����邱��
	//----------------------------------------------------------
	operator ICommand* (void)
	{
		ICommand* pTemp = _pCommand;

		_pCommand = NULL;

		return pTemp;
	};
};

};//namespace gift

#endif
