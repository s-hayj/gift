//----------------------------------------------------------
//	@file	IDrawContainer.h
//
//	@memo	登録した描画の実行情報閲覧用インターフェース
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
//	@memo	描画の実行内容を隠蔽するインターフェース
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
	//	描画処理の実行を行う
	//
	//	@name	IDrawOperation::Execute
	//
	//	@memo	描画開始処理なのか、後処理なのかは隠蔽
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pOperator	操作方法、描画情報格納オブジェクト
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Execute( DrawOperator* pOperator ) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
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
//	@memo	描画実行ラインの各実行処理、描画情報の受け渡しを受け持つ
//
//	@attrib	public class
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
class	DrawOperator
{
private:
	RenderState*	m_pState;	//	描画情報への参照

public:
	//----------------------------------------------------------
	//	描画情報参照先を登録する
	//
	//	@name	DrawOperator::SetState
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pState	描画情報参照先
	//
	//	@return	none
	//----------------------------------------------------------
	void SetState( RenderState* pState )
	{
		m_pState = pState;
	};

	//----------------------------------------------------------
	//	描画情報への参照を取得
	//
	//	@name	DrawOperator::GetState
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	none
	//
	//	@return	RenderState*	描画情報への参照
	//----------------------------------------------------------
	RenderState* GetState(void)
	{
		return m_pState;
	};

	//----------------------------------------------------------
	//	描画操作の実行を行う
	//
	//	@name	DrawOperator::Execute
	//
	//	@memo
	//
	//	@attrib	public
	//
	//	@param	(in)pOperation	実行する対象
	//
	//	@return	none
	//----------------------------------------------------------
	void Execute( IDrawOperation* pOperation )
	{
		//	実行先が存在する
		ASSERT( pOperation != NULL );

		//	隠蔽された実行の呼び出しと自身の受け渡し
		pOperation->Execute( this );
	};

protected:
	//----------------------------------------------------------
	//	コンストラクタ
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
	//	デストラクタ
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
//	@memo	描画処理実行の有無や順番を設定、参照する
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
	//	@memo	描画処理格納コンテナの連結管理用インターフェース
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
		//	格納コンテナ群のソート有無を設定する
		//
		//	@name	IDrawContainer::IConnector::Sort
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	(in)mode	1以上なら、昇順ソート
		//						0なら、ソートを行わない
		//						-1以上なら、降順ソート
		//
		//	@return	none
		//----------------------------------------------------------
		virtual void Sort( int mode = 0 ) = 0;

		//----------------------------------------------------------
		//	ソート有無の設定状況を確認する
		//
		//	@name	IDrawContainer::IConnector::IsSort
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	none
		//
		//	@return	int	1以上なら、昇順ソートを行う
		//				0なら、ソートを行わない
		//				-1以上なら、降順ソートを行う
		//----------------------------------------------------------
		virtual int IsSort(void) = 0;

		//----------------------------------------------------------
		//	描画情報格納コンテナの追加を行う
		//
		//	@name	IDrawContainer::IConnector::Add
		//
		//	@memo	描画実行ラインの末端に追加される
		//
		//	@attrib	public abstract
		//
		//	@param	(in)pContainer	連結させるコンテナ
		//
		//	@return	bool	false なら、連結失敗
		//----------------------------------------------------------
		virtual bool Add( IDrawContainer* pContainer ) = 0;
		
		//----------------------------------------------------------
		//	指定したコンテナを実行ラインから外す
		//
		//	@name	IDrawContainer::IConnector::Erase
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	(in)pContainer	外す対象コンテナ
		//
		//	@return	bool	false なら、検索失敗
		//----------------------------------------------------------
		virtual bool Erase( IDrawContainer* pContainer ) = 0;

		//----------------------------------------------------------
		//	格納中のコンテナから条件に合うものを外す
		//
		//	@name	IDrawContainer::IConnector::Clear
		//
		//	@memo
		//
		//	@attrib	public abstract
		//
		//	@param	(in)hold	1以上なら IsHold()==true のコンテナを外す
		//						0なら IsHold() の条件でコンテナを外さない
		//						-1以下なら IsHold()==false のコンテナを外す
		//	@param	(in)visible	1以上なら IsVisible()==true のコンテナを外す
		//						0なら IsVisible() の条件でコンテナを外さない
		//						-1以下なら IsVisible()==false のコンテナを外す
		//
		//	@return	none
		//----------------------------------------------------------
		virtual void Clear( int hold = 0, int visible = 0 ) = 0;

		//----------------------------------------------------------
		//	格納中のコンテナを全て破棄する
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
		//	デストラクタ
		//
		//	@name	IDrawContainer::IConnector::~IConnector
		//
		//	@attrib	protected virtual
		//----------------------------------------------------------
		virtual ~IConnector(void) {};
	};

public:
	//----------------------------------------------------------
	//	格納情報を全て初期状態に戻す
	//
	//	@name	IDrawContainer::Initialize
	//
	//	@memo	実行すると描画処理が行われなくなる
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Initialize(void) = 0;

	//----------------------------------------------------------
	//	描画処理順番を設定する
	//
	//	@name	IDrawContainer::SetPriority
	//
	//	@memo	順番ソート時の比較基準値を設定する
	//
	//	@attrib	public abstract
	//
	//	@param	(in)priority	順番ソート比較値
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void SetPriority( float priority = 0.0f ) = 0;

	//----------------------------------------------------------
	//	設定されている描画順番ソート比較値を参照する
	//
	//	@name	IDrawContainer::GetPriority
	//
	//	@memo	登録された実行ライン上で参照される
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	float	設定されている比較値
	//----------------------------------------------------------
	virtual float GetPriority(void) = 0;

	//----------------------------------------------------------
	//	描画処理実行の有無を設定する
	//
	//	@name	IDrawContainer::Visible
	//
	//	@memo	ライン登録後も、この設定次第で実行をキャンセルする
	//
	//	@attrib	public abstract
	//
	//	@param	(in)visible	false なら、描画処理を実行しない
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Visible( bool visible = false ) = 0;

	//----------------------------------------------------------
	//	描画処理実行有無の設定状況を確認する
	//
	//	@name	IDrawContainer::IsVisible
	//
	//	@memo	描画処理の直前に呼び出され、有無を確認する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return bool	false なら、描画処理を行わない
	//----------------------------------------------------------
	virtual bool IsVisible(void) = 0;

	//----------------------------------------------------------
	//	描画終了後のデータ破棄の有無を設定
	//
	//	@name	IDrawContainer::Hold
	//
	//	@memo	描画後にラインから外され、格納情報を初期化される
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	true なら、終了後もラインに留まる
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Hold( bool enable = false ) = 0;

	//----------------------------------------------------------
	//	自動データ破棄有無の設定状況を確認する
	//
	//	@name	IDrawContainer::IsHold
	//
	//	@memo	描画処理終了後に呼び出され、有無を確認する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true なら、ラインに留まり情報を維持する
	//----------------------------------------------------------
	virtual bool IsHold(void) = 0;

	//----------------------------------------------------------
	//	自身の描画操作の実行を委譲する
	//
	//	@name	IDrawContainer::Accept
	//
	//	@memo	隠蔽した描画内容を実行してもらう
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pOperator	処理の委譲先
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Accept( DrawOperator* pOperator ) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
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
//	@memo	描画ライン登録時の情報をパックし、参照するインターフェース
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
	//	描画順番ソート時の基準値を設定する
	//
	//	@name	IDrawContainer::SetPriority
	//
	//	@memo	デフォルトならびに標準値は 0.0f
	//
	//	@attrib	public abstract
	//
	//	@param	(in)priority	ソート時の比較値
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void SetPriority( float priority = 0.0f ) = 0;

	//----------------------------------------------------------
	//	設定されている描画順番ソート時の比較値を参照
	//
	//	@name	IDrawContainer::GetPriority
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	float	設定されている比較値
	//----------------------------------------------------------
	virtual float GetPriority(void) = 0;

	//----------------------------------------------------------
	//	現在の描画実行状態を参照
	//
	//	@name	IDrawContainer::IsVisible
	//
	//	@memo	描画実行の呼び出し有無を確認する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true なら、描画実行処理を呼び出す
	//----------------------------------------------------------
	virtual bool IsVisible(void) = 0;

	//----------------------------------------------------------
	//	描画実行処理の呼び出し有無を設定
	//
	//	@name	IDrawContainer::Visible
	//
	//	@memo	実行ラインに登録後も処理呼び出し有無を設定できる
	//
	//	@attrib	public abstract
	//
	//	@param	(in)visible	true なら、描画処理を呼び出す
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Visible( bool visible = true ) = 0;

	//----------------------------------------------------------
	//	描画終了後も実行ラインに登録し続けるか設定する
	//
	//	@name	IDrawContainer::Hold
	//
	//	@memo	処理終了時に登録継続の有無をチェックする
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	true なら、登録の継続を行う
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Hold( bool enable = false ) = 0;

	//----------------------------------------------------------
	//	現在、実行ラインへの登録継続有無を参照する
	//
	//	@name	IDrawContainer::IsHold
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	bool	true なら、登録継続を行っている
	//----------------------------------------------------------
	virtual bool IsHold(void) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
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
//	@memo	描画操作に関する登録方法を提供するインターフェース
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
	//	描画処理を開始する
	//
	//	@name	IDrawContainer::SetBeign
	//
	//	@memo	描画実行順番ごとに呼び出される、描画の実行呼び出し
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pRenderable	描画実行を行う処理
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void SetBeign( IRenderable* pRenderable ) = 0;

	//----------------------------------------------------------
	//	描画の後処理を実行する
	//
	//	@name	IDrawContainer::SetEnd
	//
	//	@memo	描画実行順番の逆から呼び出される、描画の後処理
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pRenderable	描画の後処理
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void SetEnd( IRenderable* pRenderable ) = 0;

	//----------------------------------------------------------
	//	描画実行の呼び出し有無を設定する
	//
	//	@name	IDrawContainer::Visible
	//
	//	@memo	実行ラインに登録していても、描画実行の有無を制御する
	//
	//	@attrib	public abstract
	//
	//	@param	(in)visible	true なら、描画実行処理を呼び出す
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Visible( bool visible ) = 0;

	//----------------------------------------------------------
	//	描画順番の優先度を設定する
	//
	//	@name	IDrawContainer::Priority
	//
	//	@memo	描画順番ソートのときの基準値
	//
	//	@attrib	public abstract
	//
	//	@param	(in)priority = 0.0f	順番ソート時の基準値
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Priority( float priority = 0.0f ) = 0;

	//----------------------------------------------------------
	//	格納情報維持の有無を設定
	//
	//	@name	IDrawContainer::Hold
	//
	//	@memo	維持する場合、描画実行ラインから外れない
	//
	//	@attrib	public abstract
	//
	//	@param	(in)enable	true なら、描画後も格納情報を維持し続ける
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Hold( bool enable = false ) = 0;

protected:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IDrawContainer::~IDrawContainer
	//
	//	@attrib	protected virtual
	//----------------------------------------------------------
	virtual ~IDrawContainer(void) {};
};
#endif

#endif