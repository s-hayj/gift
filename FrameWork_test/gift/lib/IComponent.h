//----------------------------------------------------------
//	@file	IComponent.h
//
//	@memo	�R���|�[�l���g����p�e���v���[�g�C���^�[�t�F�[�X
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__ICOMPONENT_H
#define	__ICOMPONENT_H


//----------------------------------------------------------
//	@name	IComponent
//
//	@memo	�W�F�l���b�N�R���|�[�l���g�C���^�[�t�F�[�X
//
//	@attrib	public template interface
//
//	@type	T	�i�[����f�[�^�^
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
template<class T>
class	IComponent
{
public:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IComponent::~IComponent
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IComponent(void) {};

	//----------------------------------------------------------
	//	�i�[�I�u�W�F�N�g��]��
	//
	//	@name	IComponent::Set
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)obj	�i�[������I�u�W�F�N�g�ւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Set( T& obj ) = 0;

	//----------------------------------------------------------
	//	�i�[�I�u�W�F�N�g���擾
	//
	//	@name	IComponent::Get
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	T&	�i�[�I�u�W�F�N�g�ւ̎Q��
	//----------------------------------------------------------
	virtual T& Get(void) = 0;

	//----------------------------------------------------------
	//	���̘A������AID�w��Ŏ擾
	//
	//	@name	IComponent::Next
	//
	//	@memo	��ɁA�q�ւ̃A�N�Z�X�ɗ��p����
	//
	//	@attrib	public abstract
	//
	//	@param	(in)id = 0	�A���ԍ����w�肷��
	//
	//	@return	IComponent*	�A����̃R���|�[�l���g
	//----------------------------------------------------------
	virtual IComponent<T>* Next( int id = 0 ) = 0;

	//----------------------------------------------------------
	//	��O�̘A������擾����
	//
	//	@name	IComponent::Back
	//
	//	@memo	��ɁA�e�ւ̃A�N�Z�X�ɗ��p����
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	IComponent*	�A����̃R���|�[�l���g
	//----------------------------------------------------------
	virtual IComponent<T>* Back(void) = 0;

	//----------------------------------------------------------
	//	ID���w�肵�āA�R���|�[�l���g��A��������
	//
	//	@name	IComponent::Connect
	//
	//	@memo	��ɁA�q�Ƃ��ĘA��������Ƃ��ɗ��p����
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pComponent	�A��������R���|�[�l���g
	//	@param	(in)id = 0		���ʗp�̔ԍ�
	//
	//	@return	bool	true �̂Ƃ��A�A���ɐ���
	//----------------------------------------------------------
	virtual bool Connect( IComponent<T>* pComponent, int id = 0 ) = 0;

	//----------------------------------------------------------
	//	�e�Ƃ��ăR���|�[�l���g��A��������
	//
	//	@name	IComponent::ConnectParent
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pComponent	�A��������R���|�[�l���g
	//
	//	@return	bool	true �̂Ƃ��A�A���ɐ���
	//----------------------------------------------------------
	virtual bool ConnectParent( IComponent<T>* pParent ) = 0;
};

#endif
