//----------------------------------------------------------
//	@file	Timer.h
//
//	@memo	���ԂɊւ��鐧����e�𒊏ۉ�����
//
//	@author	sano-y
//	@data	2008-05-13	unfinished
//----------------------------------------------------------

#ifndef	__TIMER_H
#define	__TIMER_H

#include <stdio.h>
#include <assert.h>

//----------------------------------------------------------
//	@name	TimeStamp
//
//	@memo	���Ԃ̎Q�ƕ��@��񋟂���C���^�[�t�F�[�X
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	ITimeStamp
{
public:
	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�Ԃ��~���b�P�ʂŎQ��
	//
	//	@name	ITimeStamp::GetMillisecond
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	�~���b�P�ʂ̎���
	//----------------------------------------------------------
	virtual double GetMillisecond(void) = 0;

	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�Ԃ�b�P�ʂŎQ��
	//
	//	@name	ITimeStamp::GetSecond
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	�b�P�ʂ̎���
	//----------------------------------------------------------
	virtual double GetSecond(void) = 0;

	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�Ԃ𕪒P�ʂŎQ��
	//
	//	@name	ITimeStamp::GetMinute
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	���P�ʂ̎���
	//----------------------------------------------------------
	virtual double GetMinute(void) = 0;

	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�Ԃ����P�ʂŎQ��
	//
	//	@name	ITimeStamp::GetHour
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	���P�ʂ̎���
	//----------------------------------------------------------
	virtual double GetHour(void) = 0;

	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�Ԃ���P�ʂŎQ��
	//
	//	@name	ITimeStamp::GetDay
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	���P�ʂ̎���
	//----------------------------------------------------------
	virtual double GetDay(void) = 0;

	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�ԃf�[�^�𒼂ɎQ��
	//
	//	@name	ITimeStamp::GetTime
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	long	�Ǘ����Ă���f�[�^
	//----------------------------------------------------------
	virtual long GetTime(void) = 0;

	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�Ԃ��o�ߎ��Ԃ̑��v�ł���
	//
	//	@name	ITimeStamp::IsTotalTime
	//
	//	@memo	�V�X�e���N��������̒~�ώ��Ԃł��邩�ۂ�
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true	�~�ώ��Ԃł���
	//----------------------------------------------------------
	virtual bool IsTotalTime(void) = 0;

	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�Ԃ��O��̍X�V���Ƃ̍����ł���
	//
	//	@name	ITimeStamp::IsElapsedTime
	//
	//	@memo	�V�X�e���̍X�V���Ԃ̍������Ǘ����Ă��邩�ۂ�
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true	�X�V�ɗv�������Ԃ��Ǘ����Ă���
	//----------------------------------------------------------
	virtual bool IsElapsedTime(void) = 0;

	//----------------------------------------------------------
	//	�Ǘ��f�[�^���s�v�ɂȂ������Ƃ�ʒm
	//
	//	@name	ITimeStamp::Release
	//
	//	@memo	Timer�N���X�֋L�����Ă��鎞�Ԃ̉�����w������
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Release(void) = 0;

	//----------------------------------------------------------
	//	���Ԃ����Z���A�V�������ԊǗ��I�u�W�F�N�g��f���o��
	//
	//	@name	ITiemStamp::operator +
	//
	//	@memo	Timer����L���I�u�W�F�N�g�𐿋����Ă���
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	���Z���鎞�ԊǗ��I�u�W�F�N�g
	//
	//	@return	ITimeStamp*	�v�Z��̎��Ԃ��Ǘ�����V�����I�u�W�F�N�g
	//----------------------------------------------------------
	virtual ITimeStamp* operator + ( const ITimeStamp* pTime ) = 0;

	//----------------------------------------------------------
	//	���Ԃ����Z���A�V�������ԊǗ��I�u�W�F�N�g��f���o��
	//
	//	@name	ITimeStamp::operator -
	//
	//	@memo	Timer����L���I�u�W�F�N�g�𐿋����Ă���
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	���Z���鎞�ԊǗ��I�u�W�F�N�g
	//
	//	@return	ITiemStamp*	�v�Z��̎��Ԃ��Ǘ�����V�����I�u�W�F�N�g
	//----------------------------------------------------------
	virtual ITiemStamp* operator - ( const ITimeStamp* pTime ) = 0;

	//----------------------------------------------------------
	//	���g�̎��Ԃ����Z����
	//
	//	@name	ITimeStamp::operator +=
	//
	//	@memo	�����̊Ǘ����Ԃ𑀍삷��
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	���Z���鎞�Ԃւ̎Q�ƑΏ�
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void operator += ( const ITimeStamp* pTime ) = 0;

	//----------------------------------------------------------
	//	���g�̎��Ԃ����Z����
	//
	//	@name	ITimeStamp::operator -=
	//
	//	@memo	�����̊Ǘ����Ԃ𑀍삷��
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	���Z���鎞�Ԃւ̎Q�ƑΏ�
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void operator -= ( const ITimeStamp* pTime ) = 0;

	//----------------------------------------------------------
	//	�Ǘ����鎞�Ԃ��R�s�[����
	//
	//	@name	ITimeStamp::operator =
	//
	//	@memo	�������Ԃ��X�V����
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	�X�V���鎞�Ԃւ̎Q�ƑΏ�
	//
	//	@return	ITimeStamp*	���g�ւ̃|�C���^
	//----------------------------------------------------------
	virtual ITimeStamp* operator = ( const ITimeStamp* pTime ) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	ITimeStamp::~ITimeStamp
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~ITimeStamp(void) {};
};

//----------------------------------------------------------
//	@name	TimeStamp
//
//	@memo	ITimeStamp�̃C���X�^���X���I�[�g�ϐ��Ԋu�Ŏ��p����N���X
//
//	@attrib	public class
//
//	@author	sano-y
//	@data	2008-5-13
//----------------------------------------------------------
class	TimeStamp
{
private:
	ITimeStamp*	m_pTime;

public:
	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	TimeStamp::TimeStamp
	//
	//	@memo	�f�t�H���g�R���X�g���N�^
	//
	//	@attrib	public
	//
	//	@param	none
	//----------------------------------------------------------
	TimeStamp(void)
		: m_pTime( NULL )
	{
	};

	//----------------------------------------------------------
	//	�R���X�g���N�^
	//
	//	@name	TimeStamp::TimeStamp
	//
	//	@memo	�R�s�[�R���X�g���N�^�A�R�s�[�Ώۂ͊Ǘ���������
	//
	//	@attrib	public
	//
	//	@param	(in)time	�R�s�[���TimeStamp
	//----------------------------------------------------------
	TimeStamp( TimeStamp& time )
		: m_pTime( time.m_pTime )
	{
		//	�Q�Ɛ�͊Ǘ���������
		time.m_pTime = NULL;
	};

	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	TimeStamp::~TimeStmap
	//
	//	@memo	���Ԃ��Ǘ����Ă���Ȃ�A�j�����w������
	//
	//	@attrib	public
	//----------------------------------------------------------
	~TimeStamp(void)
	{
		//	���Ԃ��Ǘ����Ă���
		if ( m_pTime )
		{
			m_pTime->Release();
			m_pTime = NULL;
		}
	};

	//----------------------------------------------------------
	//	���Ԃ��Ǘ����Ă��Ȃ�
	//
	//	@name	TimeStamp::IsNone
	//
	//	@memo	���Ԑ���Ɋւ��鑀����s���邩���ׂ�
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	bool	true	���Ԑ��䂪����ɍs���Ȃ�
	//----------------------------------------------------------
	bool IsNone(void)
	{
		return !static_cast<bool>(m_pTime);
	};

	//----------------------------------------------------------
	//	���ԊǗ����s����悤�Ƀf�[�^���i�[����
	//
	//	@name	TimeStamp::Setting
	//
	//	@memo	�R�s�[��͊Ǘ�����������
	//
	//	@attrib	public
	//
	//	@param	(in)time	�f�[�^���擾����Ώ�
	//
	//	@return	bool	false	����ɊǗ����s���Ȃ�
	//----------------------------------------------------------
	bool Setting( TimeStamp& time )
	{
		//	�ȑO�ɊǗ����Ă������̂�������
		if ( m_pTime )
		{
			m_pTime->Release();
		}
		m_pTime = time.m_pTime;

		//	�擾�Ώۂ̌����𖳂���
		time.m_pTime = NULL;

		return static_cast<bool>(m_pTime);
	};

	//----------------------------------------------------------
	//	���Ԃ����Z���A�V�������ԊǗ��I�u�W�F�N�g��f���o��
	//
	//	@name	TimeStamp::oprator +
	//
	//	@memo	Timer����L���I�u�W�F�N�g�𐿋����Ă���
	//
	//	@attrib	public
	//
	//	@param	(in)time	���Z���鎞�ԊǗ��I�u�W�F�N�g
	//
	//	@return	TimeStamp	�v�Z��̎��Ԃ��Ǘ�����V�����I�u�W�F�N�g
	//----------------------------------------------------------
	TimeStamp operator + ( const TimeStamp& time )
	{
		TimeStamp temp;

		//	���ԊǗ����ł��Ă���
		ASSERT( m_pTime != NULL );

		temp.m_pTime = (*m_pTime) + time.m_pTime;

		return temp;
	};

	//----------------------------------------------------------
	//	���Ԃ����Z���A�V�������ԊǗ��I�u�W�F�N�g��f���o��
	//
	//	@name	TimeStamp::oprator -
	//
	//	@memo	Timer����L���I�u�W�F�N�g�𐿋����Ă���
	//
	//	@attrib	public
	//
	//	@param	(in)time	���Z���鎞�ԊǗ��I�u�W�F�N�g
	//
	//	@return	TimeStamp	�v�Z��̎��Ԃ��Ǘ�����V�����I�u�W�F�N�g
	//----------------------------------------------------------
	TimeStamp operator - ( const TimeStamp& time )
	{
		TimeStamp temp;

		//	���ԊǗ����ł���
		ASSERT( m_pTime != NULL );

		temp.m_pTime = (*m_pTime) - time.m_pTime;

		return temp;
	};

	//----------------------------------------------------------
	//	���g�̎��Ԃ����Z����
	//
	//	@name	TimeStamp::operator +=
	//
	//	@memo	�����̊Ǘ����Ԃ𑀍삷��
	//
	//	@attrib	public
	//
	//	@param	(in)time	���Z���鎞�Ԃւ̎Q�ƑΏ�
	//
	//	@return	none
	//----------------------------------------------------------
	void operator += ( const TimeStamp& time )
	{
		//	���Ԑ��䂪�ł���
		ASSERT( m_pTime != NULL );

		(*m_pTime) += time.m_pTime;
	};

	//----------------------------------------------------------
	//	���g�̎��Ԃ����Z����
	//
	//	@name	TimeStamp::operator -=
	//
	//	@memo	�����̊Ǘ����Ԃ𑀍삷��
	//
	//	@attrib	public
	//
	//	@param	(in)time	���Z���鎞�Ԃւ̎Q�ƑΏ�
	//
	//	@return	none
	//----------------------------------------------------------
	void operator -= ( const TimeStamp& time )
	{
		//	���Ԃ̐��䂪�ł���
		ASSERT( m_pTime != NULL );

		(*m_pTime) -= time.m_pTime;
	};

	//----------------------------------------------------------
	//	�Ǘ����鎞�Ԃ��R�s�[����
	//
	//	@name	TimeStamp::operator =
	//
	//	@memo	�������Ԃ��X�V����
	//
	//	@attrib	public
	//
	//	@param	(in)time	�X�V���鎞�Ԃւ̎Q�ƑΏ�
	//
	//	@return	TimeStamp&	���g�ւ̎Q��
	//----------------------------------------------------------
	TimeStamp& operator = ( const TimeStamp& time )
	{
		//	���Ԑ��䂪�ł���
		ASSERT( m_pTime != NULL );

		(*m_pTime) = time.m_pTime;

		return *this;
	};

	//----------------------------------------------------------
	//	�Ǘ����Ă��鎞�Ԑ���I�u�W�F�N�g�ւ̎Q��
	//
	//	@name	TimeStamp::operator ->
	//
	//	@memo	���ڊǗ��I�u�W�F�N�g�֎Q�Ƃ���
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	ITimeStamp*	�Q�ƑΏۂւ̃|�C���^
	//----------------------------------------------------------
	ITimeStamp* operator -> (void)
	{
		//	���Ԃ̐��䂪�ł���
		ASSERT( m_pTime != NULL );

		return m_pTime;
	};
};

//----------------------------------------------------------
//	@name	ITimeStampFactory
//
//	@memo	���Ԃ̎Q�ƕ��@�ʃI�u�W�F�N�g�����C���^�[�t�F�[�X
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	ITimeStampFactory
{
public:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	ITimeStampFactory::~ITimeStampFactory
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~ITimeStampFactory(void) {};

	//----------------------------------------------------------
	//	��b�ƔF���������l���擾����
	//
	//	@name	ITimeStampFactory::GetSecondTime
	//
	//	@memo	���Ԃ̒��f�[�^��b�P�ʂɕϊ����邽�߂̐��l
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	long	��b�P�ʂɕϊ����鐔�l
	//----------------------------------------------------------
	virtual long GetSecondTime(void) = 0;

	//----------------------------------------------------------
	//	���Ԃ��Q�Ƃ���I�u�W�F�N�g�𐶐�����
	//
	//	@name	ITimeStampFactory::Create
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTimer	���Ԑ���I�u�W�F�N�g
	//
	//	@return	ITimeStamp*	���ԎQ�ƃI�u�W�F�N�g
	//----------------------------------------------------------
	virtual ITimeStamp* Create( Timer* pTimer ) = 0;
};

//----------------------------------------------------------
//	@name	Timer
//
//	@memo	�e���Ԃ̍X�V�A�Q�Ƃ��Ǘ�
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-09	unfinished
//----------------------------------------------------------
class	Timer
{
protected:
	ITimeStamp*	m_pClockTime;	//	CPU�N���b�N��
	ITimeStamp*	m_pFrameTime;	//	�t���[���J�E���g

	ITimeStampFactory*	m_pFactory;	//	���ԎQ�ƃN���X�̐���

public:
};

#endif