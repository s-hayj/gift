//----------------------------------------------------------
//	@file	IInputController.h
//
//	@memo	���͏��Ɋւ�����ꑀ����{�����߃I�y���[�V�������
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------

#ifndef	__IINPUT_CONTROLLER_H
#define	__IINPUT_CONTROLLER_H


//----------------------------------------------------------
//	@name	IInputController
//
//	@memo	���͏��𑀍삷��
//
//	@attrib	public interface
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
class	IInputController
{
public:
	//----------------------------------------------------------
	//	@name	IInputController::Mode
	//
	//	@memo	�C�ӂ̓��͏��ƒʏ�̓��͏��̎�舵����
	//
	//	@attrib	public enum
	//
	//	@author	sano-y
	//	@data	2008-05-15
	//----------------------------------------------------------
	enum	Mode
	{
		None,		//	�C�ӂ̓��͏��𗘗p���Ȃ�
		Overwrite,	//	�C�ӂ̓��͏��݂̂��̗p����
		Merge,		//	�C�ӂƒʏ�ɂ����āA���͂�����ق����̗p����
	};

public:
	//----------------------------------------------------------
	//	@name	IInputController::Command
	//
	//	@memo	���͏��̏�Ԃ��i�[
	//
	//	@attrib	public struct
	//
	//	@author	sano-y
	//	@data	2008-05-15
	//----------------------------------------------------------
	struct	Command
	{
	public:
		int		m_Delay;	//	���͂���܂ł̖����͎���
		int		m_Time;		//	���͂��p�����鎞��
		int		m_Input;	//	���͂�����̎��
		float	m_Volume;	//	���͂�����
		int		m_Interval;	//	���͂���Ԋu

		IInputController::Mode	m_Mode;	//	���͏��̎�舵��

	public:
		//----------------------------------------------------------
		//	�R���X�g���N�^
		//
		//	@name	IInputController::Command::Command
		//
		//	@attrib	public
		//
		//	@param	none
		//----------------------------------------------------------
		Command(void)
			: m_Delay( 0 ), m_Time( 0 ), m_Interval( 1 ),
				m_Input( 0 ), m_Volume( 0.0f ), m_Mode( None )
		{
		};
	};

public:
	//----------------------------------------------------------
	//	�C�ӂ̓��͏��𔭍s����
	//
	//	@name	IInputController::Command
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)command		���s������͏��ւ̎Q��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Command( const IInputController::Command& command ) = 0;

	//----------------------------------------------------------
	//	�C�ӂ̓��͏��𔭍s����
	//
	//	@name	IInputController::Command
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)delay		���͂���܂ł̖����͎��ԁi�O�ő����s�j
	//	@param	(in)time		���͂��p�����鎞��
	//	@param	(in)input		���͏��̎��
	//	@param	(in)volume		���͂�����
	//	@param	(in)interval	���͂���Ԋu
	//	@param	(in)mode		���͏��̎�舵��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Command( int delay, int time, int input,
		float volume, int interval, IInputController::Mode mode ) = 0;

	//----------------------------------------------------------
	//	�C�ӂ̓��͏����̗L����ݒ肷��
	//
	//	@name	IInputController::Enable
	//
	//	@memo	false ���w�肷��ƁA��؂̔C�ӂ̓��͏����󂯕t���Ȃ��Ȃ�
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	�������s�̗L��
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Enable( bool enable ) = 0;

	//----------------------------------------------------------
	//	�C�ӂ̓��͏��������s���邩�̗L�����m�F
	//
	//	@name	IInputController::IsEnable
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true �Ȃ�A�C�ӂ̓��͏������s��
	//----------------------------------------------------------
	virtual bool IsEnable(void) = 0;

protected:
	//----------------------------------------------------------
	//	�f�X�g���N�^
	//
	//	@name	IInputController::~IInputController
	//
	//	@attirb	protected virtual
	//----------------------------------------------------------
	virtual ~IInputController(void) {};

	//----------------------------------------------------------
	//	�C�ӂ̓��͏��̐�����s��
	//
	//	@name	IInputController::Update
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	none
	//
	//	preturn	none
	//----------------------------------------------------------
	virtual void Update(void) = 0;
};

#endif