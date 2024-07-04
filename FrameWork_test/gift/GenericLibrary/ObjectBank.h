//----------------------------------------------------------
// file name: ObjectBank.h
//
// memo: �I�u�W�F�N�g�̃X�g�b�N���Ǘ�
//----------------------------------------------------------

#ifndef	__OBJECT_BANK_H
#define	__OBJECT_BANK_H

#include "NewDelManager.h"
#include "IComponent.h"

namespace gift
{
	
//----------------------------------------------------------
// name: gift::ObjectBank
//
// attrib: template final class
//
// typename: T �c �����Ǘ�����I�u�W�F�N�g�̌^
//
// memo: �I�u�W�F�N�g�̐����X�g�b�N�Ǘ�
//----------------------------------------------------------
template<class T>
class	ObjectBank
{
private:
	//----------------------------------------------------------
	// name: gift::ObjectBank::List
	//
	// attrib: private template final class
	//
	// memo: ���������I�u�W�F�N�g�̊Ǘ��p�P�������X�g
	//----------------------------------------------------------
	template<class U>
	class	List
	{
	private:
		U	_obj;			//	�i�[����I�u�W�F�N�g

		List<U>*	_pNext;	//	���̘A����ւ̃|�C���^

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//----------------------------------------------------------
		List(void)
			: _pNext(NULL)
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//----------------------------------------------------------
		~List(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[�I�u�W�F�N�g��]��
		//
		// parameter: (in)U& obj �c �i�[������I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		void Set(U& obj)
		{
			_obj = obj;
		};

		//----------------------------------------------------------
		//	�i�[�I�u�W�F�N�g���擾
		//
		// return: U& �c �i�[�I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		U& Get(void)
		{
			return _obj;
		};

		//----------------------------------------------------------
		//	���̘A������擾
		//
		// return: List<U>* �c �A����̃R���|�[�l���g
		//----------------------------------------------------------
		List<U>* Next(void)
		{
			return _pNext;
		};

		//----------------------------------------------------------
		//	�R���|�[�l���g��A��������
		//
		// parameter: (in)List<U>* pComponent �c �A��������R���|�[�l���g
		//----------------------------------------------------------
		void Connect(List<U>* pComponent)
		{
			_pNext = pComponent;
		};
	};

private:
	List<T>	_ObjectStock;	//	�I�u�W�F�N�g�̍݌�
	List<T>	_ListStock;		//	�I�u�W�F�N�g���Ǘ����郊�X�g�̍݌�

	NewDelManager<T>	_ObjectManager;	//	�i�[�I�u�W�F�N�g�̐����A�j���Ǘ�

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//----------------------------------------------------------
	ObjectBank(void)
	{
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	// parameter: (in)NewDelManager<T>& manager �c �I�u�W�F�N�g�̐����A�j�����@
	//----------------------------------------------------------
	ObjectBank(NewDelManager<T>& manager)
		: _ObjectManager(manager)
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//----------------------------------------------------------
	~ObjectBank(void)
	{
		//	�݌ɂ̃��X�g�Ȃ�тɁA�I�u�W�F�N�g��j������
		this->Release();
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̒������󂯂�
	//
	// return: T& �c ���s���ꂽ�I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	T& Order(void)
	{
		//	�I�u�W�F�N�g���o�ׂ���
		return this->ObjectOrder();
	};

	//----------------------------------------------------------
	//	�ԋp���ꂽ�I�u�W�F�N�g���󂯎��
	//
	// parameter: (in)T& value �c �ԋp���ꂽ�I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	void Return(T& value)
	{
		//	�I�u�W�F�N�g��ԋp����
		this->ObjectReturn(value);
	};

	//----------------------------------------------------------
	//	�݌ɊǗ����Ă���I�u�W�F�N�g�̐����A�j���Ǘ����@��o�^����
	//
	// parameter: (in)NewDelManager<T>& manager �c �����j���Ǘ��I�u�W�F�N�g
	//----------------------------------------------------------
	void Register(NewDelManager<T>& manager)
	{
		_ObjectManager = manager;
	};

	//----------------------------------------------------------
	//	���X�g�Ȃ�тɁA�݌ɂ̃I�u�W�F�N�g��j������
	//----------------------------------------------------------
	void Release(void)
	{
		List<T>* pTemp = NULL;

		//	�݌ɃI�u�W�F�N�g��j������
		pTemp = _ObjectStock.Next();

		//	�݌ɂ������Ȃ�܂�
		while	(pTemp != NULL)
		{
			_ObjectStock.Connect(pTemp->Next());

			//	�݌ɂ̔j���������s
			_ObjectManager.Release(pTemp->Get());

			//	�i�[���Ă������X�g�̔j��
			delete pTemp;

			//	���̍݌ɂ�j������
			pTemp = _ObjectStock.Next();
		}

		//	�݌ɂ̃��X�g��j������
		pTemp = _ListStock.Next();

		//	�݌ɂ������Ȃ�܂�
		while	(pTemp != NULL)
		{
			_ListStock.Connect(pTemp->Next());

			//	���X�g�̔j��
			delete pTemp;

			//	���̍݌ɂ�j������
			pTemp = _ListStock.Next();
		}
	};

private:
	//----------------------------------------------------------
	//	�R�s�[�R���X�g���N�^�̋֎~
	//----------------------------------------------------------
	ObjectBank(ObjectBank& bank)
	{
	};

	ObjectBank(ObjectBank* pBank)
	{
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̔������󂯂�
	//
	// return: T& �c ���s����I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	T& ObjectOrder(void)
	{
		List<T>* pTemp = _ObjectStock.Next();

		//	�݌ɂ��m���߂�
		if (pTemp)
		{
			//	�݌Ƀ��X�g���番��������
			_ObjectStock.Connect(pTemp->Next());

			//	�I�u�W�F�N�g���i�[���Ă������X�g��ԋp����
			this->ListReturn(pTemp);

			//	�I�u�W�F�N�g���o�ׂ���
			return pTemp->Get();
		}
		//	�݌ɂ�����
		else
		{
			//	�V�������X�g�𔭒�����
			pTemp = this->ListOrder();

			//	���X�g��ԋp����
			this->ListReturn(pTemp);

			//	�I�u�W�F�N�g����������A�o��
			return _ObjectManager.Initialize(pTemp->Get());
		}
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̕ԋp���󂯂�
	//
	// parameter: (in)T& obj �c �ԋp���ꂽ�I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	void ObjectReturn(T& obj)
	{
		//	�I�u�W�F�N�g���i�[���郊�X�g�𔭒�����
		List<T>* pTemp = this->ListOrder();

		//	�I�u�W�F�N�g���i�[����
		pTemp->Set(obj);

		//	�I�u�W�F�N�g�̍݌ɂƂ��Ċi�[����
		pTemp->Connect(_ObjectStock.Next());
		_ObjectStock.Connect(pTemp);
	};

	//----------------------------------------------------------
	//	���X�g�̔������󂯂�
	//
	// return: List<T>* �c ���s���郊�X�g�ւ̃|�C���^
	//----------------------------------------------------------
	List<T>* ListOrder(void)
	{
		List<T>* pTemp = _ListStock.Next();

		//	�݌ɂ��m���߂�
		if (pTemp)
		{
			//	�݌Ƀ��X�g���番��������
			_ListStock.Connect(pTemp->Next());
		}
		//	�݌ɂ�����
		else
		{
			//	���X�g��V���ɐ�������
			pTemp = new ObjectBank<T>::List<T>();
		}

		//	���X�g�𔭍s����
		return pTemp;
	};

	//----------------------------------------------------------
	//	���X�g�̕ԋp���󂯂�
	//
	// parameter: (in)List<T>* pList �c �ԋp���ꂽ���X�g�ւ̃|�C���^
	//----------------------------------------------------------
	void ListReturn(List<T>* pList)
	{
		//	���X�g�̍݌Ƀ��X�g�ɘA��
		pList->Connect(_ListStock.Next());
		_ListStock.Connect(pList);
	};
};

};//namespace gift

#endif
