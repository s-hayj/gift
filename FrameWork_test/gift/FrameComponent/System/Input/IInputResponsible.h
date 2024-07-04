//----------------------------------------------------------
//	@file	InputResponsible.h
//
//	@memo	外部からの入力情報を識別可能な情報へ変換する流れを組み立てる
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
//	@memo	識別可能な情報へ変換する作業工程を組み立てる
//
//	@attrib	public abstract template class
//
//	@type	T	外部からの入力情報の型
//	@type	U	解析結果を通知する対象の型
//
//	@author	sano-y
//	@data	2008-05-15
//----------------------------------------------------------
template< class T, class U >
class	InputResponsible
{
private:
	InputResponsible< T >*	m_pNext;	//	次の作業に委譲する対象

public:
	//----------------------------------------------------------
	//	コンストラクタ
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
	//	次に作業委譲する対象を公開し、任意の処置を施してもらう
	//
	//	@name	InputResponsible::Accept
	//
	//	@memo
	//
	//	@attrib	public virtual
	//
	//	@param	(in)pVisitor	操作をしてくれる対象
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Accept( InputVisitor* pVisitor )
	{
		//	次に作業する先を教える
		pVisitor->SetNext( m_pNext );

		//	自身の状態を教える
		pVisitor->SetResponsible( this );
	};

	//----------------------------------------------------------
	//	次に作業を委譲する対象を登録する
	//
	//	@name	InputResponsible::SetNext
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pNext	次に作業をする対象
	//
	//	@return	InputResponsible*	登録した次の作業対象
	//----------------------------------------------------------
	InputResponsible< T, U >* SetNext( InputResponsible* pNext )
	{
		m_pNext = pNext;

		return m_pNext;
	};

	//----------------------------------------------------------
	//	入力情報の解析をする
	//
	//	@name	InputResponsible::Execute
	//
	//	@memo	自身ができる内容をこなし、次へ作業を引き継がせる
	//
	//	@attrib	public
	//
	//	@param	(in)question	解析する情報への参照
	//	@param	(in)answer		解析結果を通知する対象への参照
	//
	//	@return	neno
	//----------------------------------------------------------
	void Execute( T& question, U& answer )
	{
		//	自身ができるところまで解析する
		Judge( question, answer );

		//	引継ぎ先がいる
		if ( m_pNext )
		{
			//	残りの作業をやってもらう
			m_pNext->Execute( question, answer );
		}
	};

protected:
	//----------------------------------------------------------
	//	引数の情報を解析する
	//
	//	@name	InputResponsible::Judge
	//
	//	@memo
	//
	//	@attrib	protected abstract
	//
	//	@param	(in)question	解析する情報への参照
	//	@param	(in)answer		解析結果を報告する対象への参照
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Judge( T& question, U& answer ) = 0;
};

#endif