//----------------------------------------------------------
//	@file	Timer.h
//
//	@memo	時間に関する制御内容を抽象化する
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
//	@memo	時間の参照方法を提供するインターフェース
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
	//	管理している時間をミリ秒単位で参照
	//
	//	@name	ITimeStamp::GetMillisecond
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	ミリ秒単位の時間
	//----------------------------------------------------------
	virtual double GetMillisecond(void) = 0;

	//----------------------------------------------------------
	//	管理している時間を秒単位で参照
	//
	//	@name	ITimeStamp::GetSecond
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	秒単位の時間
	//----------------------------------------------------------
	virtual double GetSecond(void) = 0;

	//----------------------------------------------------------
	//	管理している時間を分単位で参照
	//
	//	@name	ITimeStamp::GetMinute
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	分単位の時間
	//----------------------------------------------------------
	virtual double GetMinute(void) = 0;

	//----------------------------------------------------------
	//	管理している時間を時単位で参照
	//
	//	@name	ITimeStamp::GetHour
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	時単位の時間
	//----------------------------------------------------------
	virtual double GetHour(void) = 0;

	//----------------------------------------------------------
	//	管理している時間を日単位で参照
	//
	//	@name	ITimeStamp::GetDay
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	double	日単位の時間
	//----------------------------------------------------------
	virtual double GetDay(void) = 0;

	//----------------------------------------------------------
	//	管理している時間データを直に参照
	//
	//	@name	ITimeStamp::GetTime
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	long	管理しているデータ
	//----------------------------------------------------------
	virtual long GetTime(void) = 0;

	//----------------------------------------------------------
	//	管理している時間が経過時間の総計である
	//
	//	@name	ITimeStamp::IsTotalTime
	//
	//	@memo	システム起動時からの蓄積時間であるか否か
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true	蓄積時間である
	//----------------------------------------------------------
	virtual bool IsTotalTime(void) = 0;

	//----------------------------------------------------------
	//	管理している時間が前回の更新時との差分である
	//
	//	@name	ITimeStamp::IsElapsedTime
	//
	//	@memo	システムの更新時間の差分を管理しているか否か
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true	更新に要した時間を管理している
	//----------------------------------------------------------
	virtual bool IsElapsedTime(void) = 0;

	//----------------------------------------------------------
	//	管理データが不要になったことを通知
	//
	//	@name	ITimeStamp::Release
	//
	//	@memo	Timerクラスへ記憶している時間の解放を指示する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Release(void) = 0;

	//----------------------------------------------------------
	//	時間を加算し、新しい時間管理オブジェクトを吐き出す
	//
	//	@name	ITiemStamp::operator +
	//
	//	@memo	Timerから記憶オブジェクトを請求している
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	加算する時間管理オブジェクト
	//
	//	@return	ITimeStamp*	計算後の時間を管理する新しいオブジェクト
	//----------------------------------------------------------
	virtual ITimeStamp* operator + ( const ITimeStamp* pTime ) = 0;

	//----------------------------------------------------------
	//	時間を減算し、新しい時間管理オブジェクトを吐き出す
	//
	//	@name	ITimeStamp::operator -
	//
	//	@memo	Timerから記憶オブジェクトを請求している
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	減算する時間管理オブジェクト
	//
	//	@return	ITiemStamp*	計算後の時間を管理する新しいオブジェクト
	//----------------------------------------------------------
	virtual ITiemStamp* operator - ( const ITimeStamp* pTime ) = 0;

	//----------------------------------------------------------
	//	自身の時間を加算する
	//
	//	@name	ITimeStamp::operator +=
	//
	//	@memo	内部の管理時間を操作する
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	加算する時間への参照対象
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void operator += ( const ITimeStamp* pTime ) = 0;

	//----------------------------------------------------------
	//	自身の時間を減算する
	//
	//	@name	ITimeStamp::operator -=
	//
	//	@memo	内部の管理時間を操作する
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	減算する時間への参照対象
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void operator -= ( const ITimeStamp* pTime ) = 0;

	//----------------------------------------------------------
	//	管理する時間をコピーする
	//
	//	@name	ITimeStamp::operator =
	//
	//	@memo	内部時間を更新する
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTime	更新する時間への参照対象
	//
	//	@return	ITimeStamp*	自身へのポインタ
	//----------------------------------------------------------
	virtual ITimeStamp* operator = ( const ITimeStamp* pTime ) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
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
//	@memo	ITimeStampのインスタンスをオート変数間隔で私用するクラス
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
	//	コンストラクタ
	//
	//	@name	TimeStamp::TimeStamp
	//
	//	@memo	デフォルトコンストラクタ
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
	//	コンストラクタ
	//
	//	@name	TimeStamp::TimeStamp
	//
	//	@memo	コピーコンストラクタ、コピー対象は管理権を失う
	//
	//	@attrib	public
	//
	//	@param	(in)time	コピー先のTimeStamp
	//----------------------------------------------------------
	TimeStamp( TimeStamp& time )
		: m_pTime( time.m_pTime )
	{
		//	参照先は管理権を失う
		time.m_pTime = NULL;
	};

	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	TimeStamp::~TimeStmap
	//
	//	@memo	時間を管理しているなら、破棄を指示する
	//
	//	@attrib	public
	//----------------------------------------------------------
	~TimeStamp(void)
	{
		//	時間を管理している
		if ( m_pTime )
		{
			m_pTime->Release();
			m_pTime = NULL;
		}
	};

	//----------------------------------------------------------
	//	時間を管理していない
	//
	//	@name	TimeStamp::IsNone
	//
	//	@memo	時間制御に関する操作を行えるか調べる
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	bool	true	時間制御が正常に行えない
	//----------------------------------------------------------
	bool IsNone(void)
	{
		return !static_cast<bool>(m_pTime);
	};

	//----------------------------------------------------------
	//	時間管理が行えるようにデータを格納する
	//
	//	@name	TimeStamp::Setting
	//
	//	@memo	コピー先は管理権限を失う
	//
	//	@attrib	public
	//
	//	@param	(in)time	データを取得する対象
	//
	//	@return	bool	false	正常に管理が行えない
	//----------------------------------------------------------
	bool Setting( TimeStamp& time )
	{
		//	以前に管理していたものがあった
		if ( m_pTime )
		{
			m_pTime->Release();
		}
		m_pTime = time.m_pTime;

		//	取得対象の権限を無くす
		time.m_pTime = NULL;

		return static_cast<bool>(m_pTime);
	};

	//----------------------------------------------------------
	//	時間を加算し、新しい時間管理オブジェクトを吐き出す
	//
	//	@name	TimeStamp::oprator +
	//
	//	@memo	Timerから記憶オブジェクトを請求している
	//
	//	@attrib	public
	//
	//	@param	(in)time	加算する時間管理オブジェクト
	//
	//	@return	TimeStamp	計算後の時間を管理する新しいオブジェクト
	//----------------------------------------------------------
	TimeStamp operator + ( const TimeStamp& time )
	{
		TimeStamp temp;

		//	時間管理ができている
		ASSERT( m_pTime != NULL );

		temp.m_pTime = (*m_pTime) + time.m_pTime;

		return temp;
	};

	//----------------------------------------------------------
	//	時間を減算し、新しい時間管理オブジェクトを吐き出す
	//
	//	@name	TimeStamp::oprator -
	//
	//	@memo	Timerから記憶オブジェクトを請求している
	//
	//	@attrib	public
	//
	//	@param	(in)time	減算する時間管理オブジェクト
	//
	//	@return	TimeStamp	計算後の時間を管理する新しいオブジェクト
	//----------------------------------------------------------
	TimeStamp operator - ( const TimeStamp& time )
	{
		TimeStamp temp;

		//	時間管理ができる
		ASSERT( m_pTime != NULL );

		temp.m_pTime = (*m_pTime) - time.m_pTime;

		return temp;
	};

	//----------------------------------------------------------
	//	自身の時間を加算する
	//
	//	@name	TimeStamp::operator +=
	//
	//	@memo	内部の管理時間を操作する
	//
	//	@attrib	public
	//
	//	@param	(in)time	加算する時間への参照対象
	//
	//	@return	none
	//----------------------------------------------------------
	void operator += ( const TimeStamp& time )
	{
		//	時間制御ができる
		ASSERT( m_pTime != NULL );

		(*m_pTime) += time.m_pTime;
	};

	//----------------------------------------------------------
	//	自身の時間を減算する
	//
	//	@name	TimeStamp::operator -=
	//
	//	@memo	内部の管理時間を操作する
	//
	//	@attrib	public
	//
	//	@param	(in)time	減算する時間への参照対象
	//
	//	@return	none
	//----------------------------------------------------------
	void operator -= ( const TimeStamp& time )
	{
		//	時間の制御ができる
		ASSERT( m_pTime != NULL );

		(*m_pTime) -= time.m_pTime;
	};

	//----------------------------------------------------------
	//	管理する時間をコピーする
	//
	//	@name	TimeStamp::operator =
	//
	//	@memo	内部時間を更新する
	//
	//	@attrib	public
	//
	//	@param	(in)time	更新する時間への参照対象
	//
	//	@return	TimeStamp&	自身への参照
	//----------------------------------------------------------
	TimeStamp& operator = ( const TimeStamp& time )
	{
		//	時間制御ができる
		ASSERT( m_pTime != NULL );

		(*m_pTime) = time.m_pTime;

		return *this;
	};

	//----------------------------------------------------------
	//	管理している時間制御オブジェクトへの参照
	//
	//	@name	TimeStamp::operator ->
	//
	//	@memo	直接管理オブジェクトへ参照する
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	ITimeStamp*	参照対象へのポインタ
	//----------------------------------------------------------
	ITimeStamp* operator -> (void)
	{
		//	時間の制御ができる
		ASSERT( m_pTime != NULL );

		return m_pTime;
	};
};

//----------------------------------------------------------
//	@name	ITimeStampFactory
//
//	@memo	時間の参照方法別オブジェクト生成インターフェース
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
	//	デストラクタ
	//
	//	@name	ITimeStampFactory::~ITimeStampFactory
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~ITimeStampFactory(void) {};

	//----------------------------------------------------------
	//	一秒と認識する基準数値を取得する
	//
	//	@name	ITimeStampFactory::GetSecondTime
	//
	//	@memo	時間の直データを秒単位に変換するための数値
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	long	一秒単位に変換する数値
	//----------------------------------------------------------
	virtual long GetSecondTime(void) = 0;

	//----------------------------------------------------------
	//	時間を参照するオブジェクトを生成する
	//
	//	@name	ITimeStampFactory::Create
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pTimer	時間制御オブジェクト
	//
	//	@return	ITimeStamp*	時間参照オブジェクト
	//----------------------------------------------------------
	virtual ITimeStamp* Create( Timer* pTimer ) = 0;
};

//----------------------------------------------------------
//	@name	Timer
//
//	@memo	各時間の更新、参照を管理
//
//	@attrib	public abstract class
//
//	@author	sano-y
//	@data	2008-05-09	unfinished
//----------------------------------------------------------
class	Timer
{
protected:
	ITimeStamp*	m_pClockTime;	//	CPUクロック数
	ITimeStamp*	m_pFrameTime;	//	フレームカウント

	ITimeStampFactory*	m_pFactory;	//	時間参照クラスの生成

public:
};

#endif