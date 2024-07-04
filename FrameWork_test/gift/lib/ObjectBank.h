//----------------------------------------------------------
//	@file	ObjectBank.h
//
//	@memo	�I�u�W�F�N�g�̃X�g�b�N���Ǘ�
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__OBJECT_BANK_H
#define	__OBJECT_BANK_H

#include "NewDelManager.h"
#include "IComponent.h"

	
//----------------------------------------------------------
//	@name	ObjectBank
//
//	@memo	�I�u�W�F�N�g�̐����X�g�b�N�Ǘ�
//
//	@attrib	public template final class
//
//	@type	T	�����Ǘ�����I�u�W�F�N�g�̌^
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
template<class T>
class	ObjectBank
{
private:
	//----------------------------------------------------------
	//	@name	ObjectBank::List
	//
	//	@memo	���������I�u�W�F�N�g�̊Ǘ��p�P�������X�g
	//
	//	@attrib	private template final class
	//
	//	@author	sano-y
	//	@data	2008-05-14
	//----------------------------------------------------------
	template<class U>
	class	List
	{
	private:
		U			m_obj;		//	�i�[����I�u�W�F�N�g

		List<U>*	m_pNext;	//	���̘A����ւ̃|�C���^

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	ObjectBank::List::List
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		List(void)
			: m_pNext( NULL )
		{
		};

		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	ObjectBank::List::~List
		//
		//	@attrib	public
		//----------------------------------------------------------
		~List(void)
		{
		};

		//----------------------------------------------------------
		//	�i�[�I�u�W�F�N�g��]��
		//
		//	@name	ObjectBank::List::Set
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	(in)obj	�i�[������I�u�W�F�N�g�ւ̎Q��
		//
		//	@return	none
		//----------------------------------------------------------
		void Set( U& obj )
		{
			m_obj = obj;
		};

		//----------------------------------------------------------
		//	�i�[�I�u�W�F�N�g���擾
		//
		//	@name	ObjectBank::List::Get
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	U&	�i�[�I�u�W�F�N�g�ւ̎Q��
		//----------------------------------------------------------
		U& Get(void)
		{
			return m_obj;
		};

		//----------------------------------------------------------
		//	���̘A������擾
		//
		//	@name	ObjectBank::List::Next
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	List<U>*	�A����̃R���|�[�l���g
		//----------------------------------------------------------
		List<U>* Next(void)
		{
			return m_pNext;
		};

		//----------------------------------------------------------
		//	�R���|�[�l���g��A��������
		//
		//	@name	ObjectBank::List::Connect
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	(in)pComponent	�A��������R���|�[�l���g
		//
		//	@return	none
		//----------------------------------------------------------
		void Connect( List<U>* pComponent )
		{
			m_pNext = pComponent;
		};
	};

private:
	List<T>			m_ObjectStock;	//	�I�u�W�F�N�g�̍݌�
	List<T>			m_ListStock;	//	�I�u�W�F�N�g���Ǘ����郊�X�g�̍݌�

	NewDelManager<T>	m_ObjectManager;	//	�i�[�I�u�W�F�N�g�̐����A�j���Ǘ�

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	ObjectBank::ObjectBank
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	ObjectBank(void)
	{
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	ObjectBank::ObjectBank
	//
	//	@attrib	public
	//
	//	@param	(in)manager	�I�u�W�F�N�g�̐����A�j�����@
	//----------------------------------------------------------
	ObjectBank( NewDelManager<T>& manager )
		: m_ObjectManager( manager )
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	ObjectBank::~ObjectBank
	//
	//	@attrib	public
	//----------------------------------------------------------
	~ObjectBank(void)
	{
		//	�݌ɂ̃��X�g�Ȃ�тɁA�I�u�W�F�N�g��j������
		this->Release();
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̒������󂯂�
	//
	//	@name	ObjectBank::Order
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	T&	���s���ꂽ�I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	T& Order(void)
	{
		//	�I�u�W�F�N�g���o�ׂ���
		return this->ObjectOrder();
	};

	//----------------------------------------------------------
	//	�ԋp���ꂽ�I�u�W�F�N�g���󂯎��
	//
	//	@name	ObjectBank::Restore
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)value	�ԋp���ꂽ�I�u�W�F�N�g�ւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	void Restore(T& value)
	{
		//	�I�u�W�F�N�g��ԋp����
		this->ObjectRestore( value );
	};

	//----------------------------------------------------------
	//	�݌ɊǗ����Ă���I�u�W�F�N�g�̐����A�j���Ǘ����@��o�^����
	//
	//	@name	ObjectBank::Register
	//
	//	@memo	�o�^���i�����̃I�u�W�F�N�g�j�́A�����j���������s���Ȃ��Ȃ�
	//
	//	@attrib	public
	//
	//	@param	(in)manager	�����A�j�����@�Ǘ��I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	void Register( NewDelManager<T>& manager )
	{
		m_ObjectManager = manager;
	};

	//----------------------------------------------------------
	//	���X�g�Ȃ�тɁA�݌ɂ̃I�u�W�F�N�g��j������
	//
	//	@name	ObjectBank::Release
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	void Release(void)
	{
		List<T>* pTemp = NULL;

		//	�݌ɃI�u�W�F�N�g��j������
		pTemp = m_ObjectStock.Next();

		//	�݌ɂ������Ȃ�܂�
		while	( pTemp != NULL )
		{
			m_ObjectStock.Connect( pTemp->Next() );

			//	�݌ɂ̔j���������s
			m_ObjectManager.Release( pTemp->Get() );

			//	�i�[���Ă������X�g�̔j��
			delete pTemp;

			//	���̍݌ɂ�j������
			pTemp = m_ObjectStock.Next();
		}

		//	�݌ɂ̃��X�g��j������
		pTemp = m_ListStock.Next();

		//	�݌ɂ������Ȃ�܂�
		while	( pTemp != NULL )
		{
			m_ListStock.Connect( pTemp->Next() );

			//	���X�g�̔j��
			delete pTemp;

			//	���̍݌ɂ�j������
			pTemp = m_ListStock.Next();
		}
	};

private:
	//----------------------------------------------------------
	//	�R�s�[�R���X�g���N�^
	//
	//	@name	ObjectBank::ObjectBank
	//
	//	@memo	�R�s�[�R���X�g���N�^�̋֎~
	//
	//	@attrib	private
	//
	//	@param	(in)bank	�R�s�[����I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	ObjectBank( ObjectBank& bank )
	{
	};

	//----------------------------------------------------------
	//	�R�s�[�R���X�g���N�^
	//
	//	@name	ObjectBank::ObjectBank
	//
	//	@memo	�R�s�[�R���X�g���N�^�̋֎~
	//
	//	@attrib	private
	//
	//	@param	(in)pBank	�R�s�[����I�u�W�F�N�g�ւ̃|�C���^
	//----------------------------------------------------------
	ObjectBank( ObjectBank* pBank )
	{
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̔������󂯂�
	//
	//	@name	ObjectBank::ObjectOrder
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	none
	//
	//	@return	T&	���s����I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	T& ObjectOrder(void)
	{
		List<T>* pTemp = m_ObjectStock.Next();

		//	�݌ɂ��m���߂�
		if ( pTemp )
		{
			//	�݌Ƀ��X�g���番��������
			m_ObjectStock.Connect( pTemp->Next() );

			//	�I�u�W�F�N�g���i�[���Ă������X�g��ԋp����
			this->ListRestore( pTemp );

			//	�I�u�W�F�N�g���o�ׂ���
			return pTemp->Get();
		}
		//	�݌ɂ�����
		else
		{
			//	�V�������X�g�𔭒�����
			pTemp = this->ListOrder();

			//	���X�g��ԋp����
			this->ListRestore( pTemp );

			//	�I�u�W�F�N�g����������A�o��
			return m_ObjectManager.Initialize( pTemp->Get() );
		}
	};

	//----------------------------------------------------------
	//	�I�u�W�F�N�g�̕ԋp���󂯂�
	//
	//	@name	ObjectBnak::ObjectRestore
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	(in)obj	�ԋp���ꂽ�I�u�W�F�N�g�ւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	void ObjectReturn(T& obj)
	{
		//	�I�u�W�F�N�g���i�[���郊�X�g�𔭒�����
		List<T>* pTemp = this->ListOrder();

		//	�I�u�W�F�N�g���i�[����
		pTemp->Set( obj );

		//	�I�u�W�F�N�g�̍݌ɂƂ��Ċi�[����
		pTemp->Connect( m_ObjectStock.Next() );
		m_ObjectStock.Connect( pTemp );
	};

	//----------------------------------------------------------
	//	���X�g�̔������󂯂�
	//
	//	@name	ObjectBank::ListOrder
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	none
	//
	//	@return	List<T>*	���s���郊�X�g�ւ̃|�C���^
	//----------------------------------------------------------
	List<T>* ListOrder(void)
	{
		List<T>* pTemp = m_ListStock.Next();

		//	�݌ɂ��m���߂�
		if ( pTemp )
		{
			//	�݌Ƀ��X�g���番��������
			m_ListStock.Connect( pTemp->Next() );
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
	//	@name	ObjectBank::ListRestore
	//
	//	@memo
	//
	//	@attrib	private
	//
	//	@param	(in)pList	�ԋp���ꂽ���X�g�ւ̃|�C���^
	//
	//	@return	none
	//----------------------------------------------------------
	void ListRestore( List<T>* pList )
	{
		//	���X�g�̍݌Ƀ��X�g�ɘA��
		pList->Connect( m_ListStock.Next() );
		m_ListStock.Connect( pList );
	};
};

#endif
