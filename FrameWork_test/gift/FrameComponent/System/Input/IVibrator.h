//----------------------------------------------------------
//	@file	IVibrator.h
//
//	@memo	主にゲームコントローラーに対する振動制御用インターフェース
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
//	@memo	振動制御に関するインターフェース
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
	//	@memo	振動情報を格納する
	//
	//	@attrib	public struct
	//
	//	@author	sano-y
	//	@data	2008-05-15
	//----------------------------------------------------------
	struct	Property
	{
	public:
		int			m_Delay;	//	振動開始するまでの無動作時間
		int			m_Time;		//	振動を継続する時間
		float		m_Volume;	//	振動する強さの割合（0.0f<=m_Volume<=1.0f）
		int			m_Interval;	//	振動する間隔（１以上）
		unsigned int m_Priority;//	作業優先度、値が低いほど優先される

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		//	@name	IVibrator::Property::Property
		//
		//	@memo	生成時の情報は、振動を停止させる情報
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
		//	振動を停止させる設定情報にする
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
			m_Delay		= 0;	//	即時処理開始
			m_Time		= 0;	//	振動処理時間なし
			m_Volume	= 0.0f;	//	振動しない
			m_Interval	= 1;
			m_Priority	= 0;	//	必ず処理が上書きされる
		};
	};

public:
	//----------------------------------------------------------
	//	現在振動しているかどうかを調べる
	//
	//	@name	IVibrator::IsActive
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true なら、現在振動している
	//----------------------------------------------------------
	virtual bool IsActive(void) = 0;

	//----------------------------------------------------------
	//	振動を許可しているか調べる
	//
	//	@name	IVibrator::IsStop
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true なら、振動を停止させる
	//----------------------------------------------------------
	virtual bool IsStop(void) = 0;

	//----------------------------------------------------------
	//	振動の有無を設定する
	//
	//	@name	IVibrator::Stop
	//
	//	@memo	振動を一時停止させる。制御情報は維持。
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	true なら、振動を停止させる。
	//						false なら、振動を再開させる。
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Stop( bool enable ) = 0;

	//----------------------------------------------------------
	//	振動情報を設定する
	//
	//	@name	IVibrator::Execute
	//
	//	@memo	設定情報を構造体でまとめる
	//
	//	@attrib	public abstract
	//
	//	@param	(in)property	設定する振動情報への参照
	//
	//	@return	bool	false なら、設定情報は無視された
	//----------------------------------------------------------
	virtual bool Execute( const IVibrator::Property& property ) = 0;

	//----------------------------------------------------------
	//	振動情報を設定する
	//
	//	@name	IVibrator::Execute
	//
	//	@memo	引数の priority 次第で設定情報が無視されることもある
	//
	//	@attrib	public abstract
	//
	//	@param	(in)delay			処理開始までの無動作時間
	//	@param	(in)time			振動継続時間
	//	@param	(in)volume			振動する強さの割合( 0.0f <= volume <= 1.0f )
	//	@param	(in)interval = 1	振動する間隔( 0 < interval )
	//	@param	(in)priority = 0	設定情報の優先度、値が低いほど優先される
	//								振動中の場合、優先度が低いと設定が無視される
	//								( -1 < priority )
	//	@param	(in)option = NULL	派生先固有の設定情報
	//
	//	@return	bool	false なら、設定情報は無視された
	//----------------------------------------------------------
	virtual bool Execute( int delay, int time, float volume,
		int interval = 1, int priority = 0, int option = NULL ) = 0;

	//----------------------------------------------------------
	//	現在設定されている振動情報を取得する
	//
	//	@name	IVibrator::GetProperty
	//
	//	@memo	振動が終了しているなら初期値になっている
	//
	//	@attrib	public abstract
	//
	//	@param	(out)property	設定情報を格納する変数先への参照
	//
	//	@return	bool	true なら、制御するべき情報を保持している
	//					false なら、制御情報は設定されていない
	//----------------------------------------------------------
	virtual bool GetProperty( IVibrator::Property& property ) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IVibrator::~IVibrator
	//
	//	@memo	派生先でのみ破棄可能
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IVibrator(void) {};

	//----------------------------------------------------------
	//	制御情報を更新する
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