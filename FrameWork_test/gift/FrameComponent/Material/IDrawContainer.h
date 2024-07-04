//----------------------------------------------------------
//	@file	IDrawContainer.h
//
//	@memo	�o�^�����`��̎��s���{���p�C���^�[�t�F�[�X
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__IDRAW_CONTAINER_H
#define	__IDRAW_CONTAINER_H

#include <stdio.h>
#include <assert.h>
#include "../Graphics/RenderState.h"

class	DrawOperator;

//----------------------------------------------------------
//	@name	IDrawOperation
//
//	@memo	�`��̎��s���e���B������C���^�[�t�F�[�X
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	IDrawOperation
{
public:
	//----------------------------------------------------------
	//	�`�揈���̎��s���s��
	//
	//	@name	IDrawOperation::Execute
	//
	//	@memo	�`��J�n�����Ȃ̂��A�㏈���Ȃ̂��͉B��
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pOperator	������@�A�`����i�[�I�u�W�F�N�g
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Execute( DrawOperator* pOperator ) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IDrawOperation::~IDrawOperation
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IDrawOperation(void) {};
};


//----------------------------------------------------------
//	@name	DrawOperator
//
//	@memo	�`����s���C���̊e���s�����A�`����̎󂯓n�����󂯎���
//
//	@attrib	public class
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	DrawOperator
{
private:
	RenderState*	m_pState;	//	�`����ւ̎Q��

public:
	//----------------------------------------------------------
	//	�`����Q�Ɛ��o�^����
	//
	//	@name	DrawOperator::SetState
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pState	�`����Q�Ɛ�
	//
	//	@return	none
	//----------------------------------------------------------
	void SetState( RenderState* pState )
	{
		m_pState = pState;
	};

	//----------------------------------------------------------
	//	�`����ւ̎Q�Ƃ��擾
	//
	//	@name	DrawOperator::GetState
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	RenderState*	�`����ւ̎Q��
	//----------------------------------------------------------
	RenderState* GetState(void)
	{
		return m_pState;
	};

	//----------------------------------------------------------
	//	�`�摀��̎��s���s��
	//
	//	@name	DrawOperator::Execute
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pOperation	���s����Ώ�
	//
	//	@return	none
	//----------------------------------------------------------
	void Execute( IDrawOperation* pOperation )
	{
		//	���s�悪���݂���
		ASSERT( pOperation != NULL );

		//	�B�����ꂽ���s�̌Ăяo���Ǝ��g�̎󂯓n��
		pOperation->Execute( this );
	};

protected:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	DrawOperator::DrawOperator
	//
	//	@attrib	protected
	//
	//	@param	none
	//----------------------------------------------------------
	DrawOperator(void)
		: m_pState( NULL )
	{
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	DrawOperator::~DrawOperator
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~DrawOperator(void)
	{
		m_pState = NULL;
	};
};


//----------------------------------------------------------
//	@name	IDrawContainer
//
//	@memo	�`�揈�����s�̗L���⏇�Ԃ�ݒ�A�Q�Ƃ���
//
//	@attrib	public interface
//
//	@author sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	IDrawContainer
{
public:
	//----------------------------------------------------------
	//	@name	IDrawContainer::IConnector
	//
	//	@memo	�`�揈���i�[�R���e�i�̘A���Ǘ��p�C���^�[�t�F�[�X
	//
	//	@attrib	public nested interface
	//
	//	@author	sano-y
	//	@data	2008-05-13
	//----------------------------------------------------------
	class	IConnector
	{
	public:
		//----------------------------------------------------------
		//	�i�[�R���e�i�Q�̃\�[�g�L����ݒ肷��
		//
		//	@name	IDrawContainer::IConnector::Sort
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	(in)mode	1�ȏ�Ȃ�A�����\�[�g
		//						0�Ȃ�A�\�[�g���s��Ȃ�
		//						-1�ȏ�Ȃ�A�~���\�[�g
		//
		//	@return	none
		//----------------------------------------------------------
		virtual void Sort( int mode = 0 ) = 0;

		//----------------------------------------------------------
		//	�\�[�g�L���̐ݒ�󋵂��m�F����
		//
		//	@name	IDrawContainer::IConnector::IsSort
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	none
		//
		//	@return	int	1�ȏ�Ȃ�A�����\�[�g���s��
		//				0�Ȃ�A�\�[�g���s��Ȃ�
		//				-1�ȏ�Ȃ�A�~���\�[�g���s��
		//----------------------------------------------------------
		virtual int IsSort(void) = 0;

		//----------------------------------------------------------
		//	�`����i�[�R���e�i�̒ǉ����s��
		//
		//	@name	IDrawContainer::IConnector::Add
		//
		//	@memo	�`����s���C���̖��[�ɒǉ������
		//
		//	@attrib	public abstract
		//
		//	@param	(in)pContainer	�A��������R���e�i
		//
		//	@return	bool	false �Ȃ�A�A�����s
		//----------------------------------------------------------
		virtual bool Add( IDrawContainer* pContainer ) = 0;
		
		//----------------------------------------------------------
		//	�w�肵���R���e�i�����s���C������O��
		//
		//	@name	IDrawContainer::IConnector::Erase
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	(in)pContainer	�O���ΏۃR���e�i
		//
		//	@return	bool	false �Ȃ�A�������s
		//----------------------------------------------------------
		virtual bool Erase( IDrawContainer* pContainer ) = 0;

		//----------------------------------------------------------
		//	�i�[���̃R���e�i��������ɍ������̂��O��
		//
		//	@name	IDrawContainer::IConnector::Clear
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	(in)hold	1�ȏ�Ȃ� IsHold()==true �̃R���e�i���O��
		//						0�Ȃ� IsHold() �̏����ŃR���e�i���O���Ȃ�
		//						-1�ȉ��Ȃ� IsHold()==false �̃R���e�i���O��
		//	@param	(in)visible	1�ȏ�Ȃ� IsVisible()==true �̃R���e�i���O��
		//						0�Ȃ� IsVisible() �̏����ŃR���e�i���O���Ȃ�
		//						-1�ȉ��Ȃ� IsVisible()==false �̃R���e�i���O��
		//
		//	@return	none
		//----------------------------------------------------------
		virtual void Clear( int hold = 0, int visible = 0 ) = 0;

		//----------------------------------------------------------
		//	�i�[���̃R���e�i��S�Ĕj������
		//
		//	@name	IDrawContainer::IConnector::Clear
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	none
		//
		//	@return	none
		//----------------------------------------------------------
		virtual void Clear(void) = 0;

	protected:
		//----------------------------------------------------------
		//	�f�X�g���N�^
		//
		//	@name	IDrawContainer::IConnector::~IConnector
		//
		//	@attrib	protected virtual
		//----------------------------------------------------------
		virtual ~IConnector(void) {};
	};

public:
	//----------------------------------------------------------
	//	�i�[����S�ď�����Ԃɖ߂�
	//
	//	@name	IDrawContainer::Initialize
	//
	//	@memo	���s����ƕ`�揈�����s���Ȃ��Ȃ�
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Initialize(void) = 0;

	//----------------------------------------------------------
	//	�`�揈�����Ԃ�ݒ肷��
	//
	//	@name	IDrawContainer::SetPriority
	//
	//	@memo	���ԃ\�[�g���̔�r��l��ݒ肷��
	//
	//	@attrib	public abstract
	//
	//	@param	(in)priority	���ԃ\�[�g��r�l
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void SetPriority( float priority = 0.0f ) = 0;

	//----------------------------------------------------------
	//	�ݒ肳��Ă���`�揇�ԃ\�[�g��r�l���Q�Ƃ���
	//
	//	@name	IDrawContainer::GetPriority
	//
	//	@memo	�o�^���ꂽ���s���C����ŎQ�Ƃ����
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	float	�ݒ肳��Ă����r�l
	//----------------------------------------------------------
	virtual float GetPriority(void) = 0;

	//----------------------------------------------------------
	//	�`�揈�����s�̗L����ݒ肷��
	//
	//	@name	IDrawContainer::Visible
	//
	//	@memo	���C���o�^����A���̐ݒ莟��Ŏ��s���L�����Z������
	//
	//	@attrib	public abstract
	//
	//	@param	(in)visible	false �Ȃ�A�`�揈�������s���Ȃ�
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Visible( bool visible = false ) = 0;

	//----------------------------------------------------------
	//	�`�揈�����s�L���̐ݒ�󋵂��m�F����
	//
	//	@name	IDrawContainer::IsVisible
	//
	//	@memo	�`�揈���̒��O�ɌĂяo����A�L�����m�F����
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return bool	false �Ȃ�A�`�揈�����s��Ȃ�
	//----------------------------------------------------------
	virtual bool IsVisible(void) = 0;

	//----------------------------------------------------------
	//	�`��I����̃f�[�^�j���̗L����ݒ�
	//
	//	@name	IDrawContainer::Hold
	//
	//	@memo	�`���Ƀ��C������O����A�i�[���������������
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	true �Ȃ�A�I��������C���ɗ��܂�
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Hold( bool enable = false ) = 0;

	//----------------------------------------------------------
	//	�����f�[�^�j���L���̐ݒ�󋵂��m�F����
	//
	//	@name	IDrawContainer::IsHold
	//
	//	@memo	�`�揈���I����ɌĂяo����A�L�����m�F����
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true �Ȃ�A���C���ɗ��܂�����ێ�����
	//----------------------------------------------------------
	virtual bool IsHold(void) = 0;

	//----------------------------------------------------------
	//	���g�̕`�摀��̎��s���Ϗ�����
	//
	//	@name	IDrawContainer::Accept
	//
	//	@memo	�B�������`����e�����s���Ă��炤
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pOperator	�����̈Ϗ���
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Accept( DrawOperator* pOperator ) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IDrawContainer::~IDrawContainer
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IDrawContainer(void) {};
};
#if 0
//----------------------------------------------------------
//	@name	IDrawContainer
//
//	@memo	�`�惉�C���o�^���̏����p�b�N���A�Q�Ƃ���C���^�[�t�F�[�X
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-12
//----------------------------------------------------------
class	IDrawContainer
{
public:
	//----------------------------------------------------------
	//	�`�揇�ԃ\�[�g���̊�l��ݒ肷��
	//
	//	@name	IDrawContainer::SetPriority
	//
	//	@memo	�f�t�H���g�Ȃ�тɕW���l�� 0.0f
	//
	//	@attrib	public abstract
	//
	//	@param	(in)priority	�\�[�g���̔�r�l
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void SetPriority( float priority = 0.0f ) = 0;

	//----------------------------------------------------------
	//	�ݒ肳��Ă���`�揇�ԃ\�[�g���̔�r�l���Q��
	//
	//	@name	IDrawContainer::GetPriority
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	float	�ݒ肳��Ă����r�l
	//----------------------------------------------------------
	virtual float GetPriority(void) = 0;

	//----------------------------------------------------------
	//	���݂̕`����s��Ԃ��Q��
	//
	//	@name	IDrawContainer::IsVisible
	//
	//	@memo	�`����s�̌Ăяo���L�����m�F����
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true �Ȃ�A�`����s�������Ăяo��
	//----------------------------------------------------------
	virtual bool IsVisible(void) = 0;

	//----------------------------------------------------------
	//	�`����s�����̌Ăяo���L����ݒ�
	//
	//	@name	IDrawContainer::Visible
	//
	//	@memo	���s���C���ɓo�^��������Ăяo���L����ݒ�ł���
	//
	//	@attrib	public abstract
	//
	//	@param	(in)visible	true �Ȃ�A�`�揈�����Ăяo��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Visible( bool visible = true ) = 0;

	//----------------------------------------------------------
	//	�`��I��������s���C���ɓo�^�������邩�ݒ肷��
	//
	//	@name	IDrawContainer::Hold
	//
	//	@memo	�����I�����ɓo�^�p���̗L�����`�F�b�N����
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	true �Ȃ�A�o�^�̌p�����s��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Hold( bool enable = false ) = 0;

	//----------------------------------------------------------
	//	���݁A���s���C���ւ̓o�^�p���L�����Q�Ƃ���
	//
	//	@name	IDrawContainer::IsHold
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true �Ȃ�A�o�^�p�����s���Ă���
	//----------------------------------------------------------
	virtual bool IsHold(void) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IDrawContainer::~IDrawContainer
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IDrawContainer(void) {};
};
#endif
#if 0
//----------------------------------------------------------
//	@name	IDrawContainer
//
//	@memo	�`�摀��Ɋւ���o�^���@��񋟂���C���^�[�t�F�[�X
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-12
//----------------------------------------------------------
class	IDrawContainer
{
public:
	//----------------------------------------------------------
	//	�`�揈�����J�n����
	//
	//	@name	IDrawContainer::SetBeign
	//
	//	@memo	�`����s���Ԃ��ƂɌĂяo�����A�`��̎��s�Ăяo��
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pRenderable	�`����s���s������
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void SetBeign( IRenderable* pRenderable ) = 0;

	//----------------------------------------------------------
	//	�`��̌㏈�������s����
	//
	//	@name	IDrawContainer::SetEnd
	//
	//	@memo	�`����s���Ԃ̋t����Ăяo�����A�`��̌㏈��
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pRenderable	�`��̌㏈��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void SetEnd( IRenderable* pRenderable ) = 0;

	//----------------------------------------------------------
	//	�`����s�̌Ăяo���L����ݒ肷��
	//
	//	@name	IDrawContainer::Visible
	//
	//	@memo	���s���C���ɓo�^���Ă��Ă��A�`����s�̗L���𐧌䂷��
	//
	//	@attrib	public abstract
	//
	//	@param	(in)visible	true �Ȃ�A�`����s�������Ăяo��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Visible( bool visible ) = 0;

	//----------------------------------------------------------
	//	�`�揇�Ԃ̗D��x��ݒ肷��
	//
	//	@name	IDrawContainer::Priority
	//
	//	@memo	�`�揇�ԃ\�[�g�̂Ƃ��̊�l
	//
	//	@attrib	public abstract
	//
	//	@param	(in)priority = 0.0f	���ԃ\�[�g���̊�l
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Priority( float priority = 0.0f ) = 0;

	//----------------------------------------------------------
	//	�i�[���ێ��̗L����ݒ�
	//
	//	@name	IDrawContainer::Hold
	//
	//	@memo	�ێ�����ꍇ�A�`����s���C������O��Ȃ�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	true �Ȃ�A�`�����i�[�����ێ���������
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Hold( bool enable = false ) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IDrawContainer::~IDrawContainer
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IDrawContainer(void) {};
};
#endif

#endif