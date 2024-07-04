//----------------------------------------------------------
//	@file	InputResponsible.h
//
//	@memo	�O������̓��͏������ʉ\�ȏ��֕ϊ����闬���g�ݗ��Ă�
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------

#ifndef	__INPUT_RESPONSIBLE_H
#define	__INPUT_RESPONSIBLE_H

#include <stdio.h>

class	InputVisitor;

//----------------------------------------------------------
//	@name	InputResponsible
//
//	@memo	���ʉ\�ȏ��֕ϊ������ƍH����g�ݗ��Ă�
//
//	@attrib	public abstract template class
//
//	@type	T	�O������̓��͏��̌^
//	@type	U	��͌��ʂ�ʒm����Ώۂ̌^
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
template< class T, class U >
class	InputResponsible
{
private:
	InputResponsible< T >*	m_pNext;	//	���̍�ƂɈϏ�����Ώ�

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	InputResponsible::InputResponsible
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	InputResponsible(void)
		: m_pNext( NULL )
	{
	};

	//----------------------------------------------------------
	//	���ɍ�ƈϏ�����Ώۂ����J���A�C�ӂ̏��u���{���Ă��炤
	//
	//	@name	InputResponsible::Accept
	//
	//	@memo
	//
	//	@attrib	public virtual
	//
	//	@param	(in)pVisitor	��������Ă����Ώ�
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Accept( InputVisitor* pVisitor )
	{
		//	���ɍ�Ƃ�����������
		pVisitor->SetNext( m_pNext );

		//	���g�̏�Ԃ�������
		pVisitor->SetResponsible( this );
	};

	//----------------------------------------------------------
	//	���ɍ�Ƃ��Ϗ�����Ώۂ�o�^����
	//
	//	@name	InputResponsible::SetNext
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pNext	���ɍ�Ƃ�����Ώ�
	//
	//	@return	InputResponsible*	�o�^�������̍�ƑΏ�
	//----------------------------------------------------------
	InputResponsible< T, U >* SetNext( InputResponsible* pNext )
	{
		m_pNext = pNext;

		return m_pNext;
	};

	//----------------------------------------------------------
	//	���͏��̉�͂�����
	//
	//	@name	InputResponsible::Execute
	//
	//	@memo	���g���ł�����e�����Ȃ��A���֍�Ƃ������p������
	//
	//	@attrib	public
	//
	//	@param	(in)question	��͂�����ւ̎Q��
	//	@param	(in)answer		��͌��ʂ�ʒm����Ώۂւ̎Q��
	//
	//	@return	neno
	//----------------------------------------------------------
	void Execute( T& question, U& answer )
	{
		//	���g���ł���Ƃ���܂ŉ�͂���
		Judge( question, answer );

		//	���p���悪����
		if ( m_pNext )
		{
			//	�c��̍�Ƃ�����Ă��炤
			m_pNext->Execute( question, answer );
		}
	};

protected:
	//----------------------------------------------------------
	//	�����̏�����͂���
	//
	//	@name	InputResponsible::Judge
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	(in)question	��͂�����ւ̎Q��
	//	@param	(in)answer		��͌��ʂ�񍐂���Ώۂւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Judge( T& question, U& answer ) = 0;
};

#endif