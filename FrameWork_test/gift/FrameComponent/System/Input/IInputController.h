//----------------------------------------------------------
//	@file	IInputController.h
//
//	@memo	入力情報に関する特殊操作を施すためオペレーションを提供
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------

#ifndef	__IINPUT_CONTROLLER_H
#define	__IINPUT_CONTROLLER_H


//----------------------------------------------------------
//	@name	IInputController
//
//	@memo	入力情報を操作する
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
	//	@memo	任意の入力情報と通常の入力情報の取り扱い方
	//
	//	@attrib	public enum
	//
	//	@author	sano-y
	//	@data	2008-05-15
	//----------------------------------------------------------
	enum	Mode
	{
		None,		//	任意の入力情報を利用しない
		Overwrite,	//	任意の入力情報のみを採用する
		Merge,		//	任意と通常において、入力があるほうを採用する
	};

public:
	//----------------------------------------------------------
	//	@name	IInputController::Command
	//
	//	@memo	入力情報の状態を格納
	//
	//	@attrib	public struct
	//
	//	@author	sano-y
	//	@data	2008-05-15
	//----------------------------------------------------------
	struct	Command
	{
	public:
		int		m_Delay;	//	入力するまでの無入力時間
		int		m_Time;		//	入力を継続する時間
		int		m_Input;	//	入力する情報の種類
		float	m_Volume;	//	入力する情報
		int		m_Interval;	//	入力する間隔

		IInputController::Mode	m_Mode;	//	入力情報の取り扱い

	public:
		//----------------------------------------------------------
		//	コンストラクタ
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
	//	任意の入力情報を発行する
	//
	//	@name	IInputController::Command
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)command		発行する入力情報への参照
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Command( const IInputController::Command& command ) = 0;

	//----------------------------------------------------------
	//	任意の入力情報を発行する
	//
	//	@name	IInputController::Command
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)delay		入力するまでの無入力時間（０で即実行）
	//	@param	(in)time		入力を継続する時間
	//	@param	(in)input		入力情報の種類
	//	@param	(in)volume		入力する情報
	//	@param	(in)interval	入力する間隔
	//	@param	(in)mode		入力情報の取り扱い
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Command( int delay, int time, int input,
		float volume, int interval, IInputController::Mode mode ) = 0;

	//----------------------------------------------------------
	//	任意の入力処理の有無を設定する
	//
	//	@name	IInputController::Enable
	//
	//	@memo	false を指定すると、一切の任意の入力情報を受け付けなくなる
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	処理実行の有無
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Enable( bool enable ) = 0;

	//----------------------------------------------------------
	//	任意の入力処理を実行するかの有無を確認
	//
	//	@name	IInputController::IsEnable
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true なら、任意の入力処理を行う
	//----------------------------------------------------------
	virtual bool IsEnable(void) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IInputController::~IInputController
	//
	//	@attirb	protected virtual
	//----------------------------------------------------------
	virtual ~IInputController(void) {};

	//----------------------------------------------------------
	//	任意の入力情報の制御を行う
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