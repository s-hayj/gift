//----------------------------------------------------------
//	@file	IVibrator.h
//
//	@memo	��ɃQ�[���R���g���[���[�ɑ΂���U������p�C���^�[�t�F�[�X
//
//	@author	sano-y
//
//	@data	2008-05-15
//----------------------------------------------------------

#ifndef	__IVIBRATOR_H
#define	__IVIBRATOR_H
#include <algorithm>

//----------------------------------------------------------
//	@name	IVibrator
//
//	@memo	�U������Ɋւ���C���^�[�t�F�[�X
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
class	IVibrator
{
public:
	//----------------------------------------------------------
	//	@name	IVibrator::Property
	//
	//	@memo	�U�������i�[����
	//
	//	@attrib	public struct
	//
	//	@author	sano-y
	//	@data	2008-05-15
	//----------------------------------------------------------
	struct	Property
	{
	public:
		int			m_Delay;	//	�U���J�n����܂ł̖����쎞��
		int			m_Time;		//	�U�����p�����鎞��
		float		m_Volume;	//	�U�����鋭���̊����i0.0f<=m_Volume<=1.0f�j
		int			m_Interval;	//	�U������Ԋu�i�P�ȏ�j
		unsigned int m_Priority;//	��ƗD��x�A�l���Ⴂ�قǗD�悳���

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	IVibrator::Property::Property
		//
		//	@memo	�������̏��́A�U�����~��������
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		Property(void)
			: m_Delay( 0 ), m_Time( 0 ), m_Interval( 1 ),
				m_Volume( 0.0f ), m_Priority( 0 )
		{
		};

		//----------------------------------------------------------
		//	�U�����~������ݒ���ɂ���
		//
		//	@name	IVibrator::Property::Stop
		//
		//	@memo
		//
		//	@attrib	public
		//
		//	@param	none
		//
		//	@return	none
		//----------------------------------------------------------
		void Stop(void)
		{
			m_Delay		= 0;	//	���������J�n
			m_Time		= 0;	//	�U���������ԂȂ�
			m_Volume	= 0.0f;	//	�U�����Ȃ�
			m_Interval	= 1;
			m_Priority	= 0;	//	�K���������㏑�������
		};
	};

public:
	//----------------------------------------------------------
	//	���ݐU�����Ă��邩�ǂ����𒲂ׂ�
	//
	//	@name	IVibrator::IsActive
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true �Ȃ�A���ݐU�����Ă���
	//----------------------------------------------------------
	virtual bool IsActive(void) = 0;

	//----------------------------------------------------------
	//	�U���������Ă��邩���ׂ�
	//
	//	@name	IVibrator::IsStop
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true �Ȃ�A�U�����~������
	//----------------------------------------------------------
	virtual bool IsStop(void) = 0;

	//----------------------------------------------------------
	//	�U���̗L����ݒ肷��
	//
	//	@name	IVibrator::Stop
	//
	//	@memo	�U�����ꎞ��~������B������͈ێ��B
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	true �Ȃ�A�U�����~������B
	//						false �Ȃ�A�U�����ĊJ������B
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Stop( bool enable ) = 0;

	//----------------------------------------------------------
	//	�U������ݒ肷��
	//
	//	@name	IVibrator::Execute
	//
	//	@memo	�ݒ�����\���̂ł܂Ƃ߂�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)property	�ݒ肷��U�����ւ̎Q��
	//
	//	@return	bool	false �Ȃ�A�ݒ���͖������ꂽ
	//----------------------------------------------------------
	virtual bool Execute( const IVibrator::Property& property ) = 0;

	//----------------------------------------------------------
	//	�U������ݒ肷��
	//
	//	@name	IVibrator::Execute
	//
	//	@memo	������ priority ����Őݒ��񂪖�������邱�Ƃ�����
	//
	//	@attrib	public abstract
	//
	//	@param	(in)delay			�����J�n�܂ł̖����쎞��
	//	@param	(in)time			�U���p������
	//	@param	(in)volume			�U�����鋭���̊���( 0.0f <= volume <= 1.0f )
	//	@param	(in)interval = 1	�U������Ԋu( 0 < interval )
	//	@param	(in)priority = 0	�ݒ���̗D��x�A�l���Ⴂ�قǗD�悳���
	//								�U�����̏ꍇ�A�D��x���Ⴂ�Ɛݒ肪���������
	//								( -1 < priority )
	//	@param	(in)option = NULL	�h����ŗL�̐ݒ���
	//
	//	@return	bool	false �Ȃ�A�ݒ���͖������ꂽ
	//----------------------------------------------------------
	virtual bool Execute( int delay, int time, float volume,
		int interval = 1, int priority = 0, int option = NULL ) = 0;

	//----------------------------------------------------------
	//	���ݐݒ肳��Ă���U�������擾����
	//
	//	@name	IVibrator::GetProperty
	//
	//	@memo	�U�����I�����Ă���Ȃ珉���l�ɂȂ��Ă���
	//
	//	@attrib	public abstract
	//
	//	@param	(out)property	�ݒ�����i�[����ϐ���ւ̎Q��
	//
	//	@return	bool	true �Ȃ�A���䂷��ׂ�����ێ����Ă���
	//					false �Ȃ�A������͐ݒ肳��Ă��Ȃ�
	//----------------------------------------------------------
	virtual bool GetProperty( IVibrator::Property& property ) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IVibrator::~IVibrator
	//
	//	@memo	�h����ł̂ݔj���\
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IVibrator(void) {};

	//----------------------------------------------------------
	//	��������X�V����
	//
	//	@name	IVibrator::Update
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Update(void) = 0;
};

#endif