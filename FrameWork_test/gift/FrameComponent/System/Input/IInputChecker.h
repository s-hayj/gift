//----------------------------------------------------------
//	@file	IInputChecker.h
//
//	@memo	入力された状態を調べるためのインターフェース
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------

#ifndef	__IINPUT_CHECKER_H
#define	__IINPUT_CHECKER_H

//----------------------------------------------------------
//	@name	IInputChecker
//
//	@memo	入力情報を調べる
//
//	@attrib	public template interface
//
//	@type	T	調べる入力情報フラグの型
//
//	@author	sano-y
//	@data	2008-05-14
//----------------------------------------------------------
template< class T >
class	IInputChecker
{
public:
	//----------------------------------------------------------
	//	指定の入力が入力された
	//
	//	@name	IInputChecker::Push
	//
	//	@memo	前フレームまでは入力が無かったときのみ反応
	//
	//	@attrib	public abstract
	//
	//	@param	(in)input	確認する入力フラグ
	//
	//	@return	bool	true なら、条件を満たした
	//----------------------------------------------------------
	virtual bool Push( T& input ) = 0;

	//----------------------------------------------------------
	//	指定の入力がされているか確認する
	//
	//	@name	IInputChecker::Press
	//
	//	@memo	今フレームで入力が確認できたときに反応
	//
	//	@attrib	public abstract
	//
	//	@param	(in)input	確認する入力フラグ
	//
	//	@return	bool	true なら、条件を満たした
	//----------------------------------------------------------
	virtual bool Press( T& input ) = 0;

	//----------------------------------------------------------
	//	指定の入力が途絶えたか確認する
	//
	//	@name	IInputChecker::Release
	//
	//	@memo	前フレームまで入力されており、今フレームで入力されないとき反応
	//
	//	@attrib	public abstract
	//
	//	@param	(in)input	確認する入力フラグ
	//
	//	@return	bool	true なら、条件を満たした
	//----------------------------------------------------------
	virtual bool Release( T& input ) = 0;

	//----------------------------------------------------------
	//	指定の入力情報に変化したか確認する
	//
	//	@name	IInputChecker::Change
	//
	//	@memo	前フレームと今フレームで、入力の有無に変化があるときに反応
	//
	//	@attrib	public abstract
	//
	//	@param	(in)input	確認する入力フラグ
	//
	//	@return	bool	true なら、条件を満たした
	//----------------------------------------------------------
	virtual bool Change( T& input ) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IInputChecker::~IInputChecker
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IInputChecker(void) {};
};

#endif