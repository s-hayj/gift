//----------------------------------------------------------
//	@file	IComponent.h
//
//	@memo	コンポーネント制御用テンプレートインターフェース
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------

#ifndef	__ICOMPONENT_H
#define	__ICOMPONENT_H


//----------------------------------------------------------
//	@name	IComponent
//
//	@memo	ジェネリックコンポーネントインターフェース
//
//	@attrib	public template interface
//
//	@type	T	格納するデータ型
//
//	@author	sano-y
//	@data	2008-05-13
//----------------------------------------------------------
template<class T>
class	IComponent
{
public:
	//----------------------------------------------------------
	//	デストラクタ
	//
	//	@name	IComponent::~IComponent
	//
	//	@attrib	public virtual
	//----------------------------------------------------------
	virtual ~IComponent(void) {};

	//----------------------------------------------------------
	//	格納オブジェクトを転送
	//
	//	@name	IComponent::Set
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)obj	格納させるオブジェクトへの参照
	//
	//	@return	none
	//----------------------------------------------------------
	virtual void Set( T& obj ) = 0;

	//----------------------------------------------------------
	//	格納オブジェクトを取得
	//
	//	@name	IComponent::Get
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	T&	格納オブジェクトへの参照
	//----------------------------------------------------------
	virtual T& Get(void) = 0;

	//----------------------------------------------------------
	//	次の連結先を、ID指定で取得
	//
	//	@name	IComponent::Next
	//
	//	@memo	主に、子へのアクセスに利用する
	//
	//	@attrib	public abstract
	//
	//	@param	(in)id = 0	連結番号を指定する
	//
	//	@return	IComponent*	連結先のコンポーネント
	//----------------------------------------------------------
	virtual IComponent<T>* Next( int id = 0 ) = 0;

	//----------------------------------------------------------
	//	手前の連結先を取得する
	//
	//	@name	IComponent::Back
	//
	//	@memo	主に、親へのアクセスに利用する
	//
	//	@attrib	public abstract
	//
	//	@param	none
	//
	//	@return	IComponent*	連結先のコンポーネント
	//----------------------------------------------------------
	virtual IComponent<T>* Back(void) = 0;

	//----------------------------------------------------------
	//	IDを指定して、コンポーネントを連結させる
	//
	//	@name	IComponent::Connect
	//
	//	@memo	主に、子として連結させるときに利用する
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pComponent	連結させるコンポーネント
	//	@param	(in)id = 0		識別用の番号
	//
	//	@return	bool	true のとき、連結に成功
	//----------------------------------------------------------
	virtual bool Connect( IComponent<T>* pComponent, int id = 0 ) = 0;

	//----------------------------------------------------------
	//	親としてコンポーネントを連結させる
	//
	//	@name	IComponent::ConnectParent
	//
	//	@memo
	//
	//	@attrib	public abstract
	//
	//	@param	(in)pComponent	連結させるコンポーネント
	//
	//	@return	bool	true のとき、連結に成功
	//----------------------------------------------------------
	virtual bool ConnectParent( IComponent<T>* pParent ) = 0;
};

#endif
