//----------------------------------------------------------
// file name: DeleteHelper.h
//
// memo: インスタンスの破棄方法を指定して委譲するクラス
//----------------------------------------------------------

#ifndef	__DELETE_HELPER_H
#define	__DELETE_HELPER_H

#include <assert.h>
#include "ICommand.h"

namespace gift
{

//----------------------------------------------------------
// name: gift::DeleteHelper
//
// attrib: template final class
//
// memo: インスタンスの破棄方法を指定して、実行する
//----------------------------------------------------------
template<bool is_Delete_ReleaseMethod = false>
class DeleteHelper
{
private:
	//----------------------------------------------------------
	// name: gift::DeleteHelper::Select
	//
	// attrib: private template sub class
	//
	// base: gift::ICommand is interface
	//
	// typename: bool … true のとき、このオブジェクトが生成される
	// typename: T … 破棄するオブジェクトの型
	//
	// memo: Release() メンバ関数によって、オブジェクト破棄を実行する
	//----------------------------------------------------------
	template<bool flag, class T>
	class Select
		: public ICommand
	{
	private:
		T* _pObj;	//	破棄するオブジェクトへのポインタ

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		// parameter: (in)T* pObj … 破棄するオブジェクトへのポインタ
		//----------------------------------------------------------
		Select(T* pObj)
		{
			_pObj = pObj;
		};

		//----------------------------------------------------------
		//	デストラクタ
		//----------------------------------------------------------
		~Select(void)
		{
			//	まだ破棄されていなかった
			if (_pObj != NULL)
			{
				this->Execute();
			}
		};

		//----------------------------------------------------------
		//	破棄処理を実行する
		//
		// attrib: override
		//----------------------------------------------------------
		void Execute(void)
		{
			_pObj->Release();
			_pObj = NULL;
		};
	};

	//----------------------------------------------------------
	// name: gift::DeleteHelper::Select
	//
	// attrib: private template sub class
	//
	// base: gift::ICommand is interface
	//
	// typename: T … 破棄するオブジェクトの型
	//
	// memo: delete 演算子によって、オブジェクトを破棄する
	//----------------------------------------------------------
	template<class T>
	class Select<false, T>
		: public ICommand
	{
	private:
		T* _pObj;	//	破棄するオブジェクトへのポインタ

	public:
		//----------------------------------------------------------
		//	コンストラクタ
		//
		// parameter: (in)T* pObj … 破棄するオブジェクトへのポインタ
		//----------------------------------------------------------
		Select(T* pObj)
		{
			_pObj = pObj;
		};

		//----------------------------------------------------------
		//	デストラクタ
		//----------------------------------------------------------
		~Select(void)
		{
			//	まだ破棄されていなかった
			if (_pObj != NULL)
			{
				this->Execute();
			}
		};

		//----------------------------------------------------------
		//	破棄処理を実行する
		//
		// attrib: override
		//----------------------------------------------------------
		void Execute(void)
		{
			delete _pObj;
			_pObj = NULL;
		};
	};

private:
	ICommand* _pCommand;	//	オブジェクト破棄処理呼び出し用

public:
	//----------------------------------------------------------
	//	コピーコンストラクタ
	//
	// parameter: (in)DeleteHelper<is_Delete_ReleaseMethod>& obj … コピー元への参照
	//----------------------------------------------------------
	DeleteHelper(DeleteHelper<is_Delete_ReleaseMethod>& obj)
	{
		_pCommand = obj._pCommand;

		_pCommand = NULL;
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//
	// parameter: (in)T* pObj … 破棄するオブジェクトへのポインタ
	//----------------------------------------------------------
	template<class T>
		DeleteHelper(T* pObj)
		: _pCommand(NULL)
	{
		assert(pObj != NULL);

		_pCommand = new Select<is_Delete_ReleaseMethod, T>(pObj);
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~DeleteHelper(void)
	{
		//	破棄処理を呼び出す
		(*this)();
	};

	//----------------------------------------------------------
	//	破棄処理を実行する
	//----------------------------------------------------------
	void operator ()(void)
	{
		//	まだオブジェクトが破棄されていない
		if (_pCommand != NULL)
		{
			//	独自のオブジェクト破棄処理を実行
			_pCommand->Execute();

			//	破棄処理オブジェクトの破棄
			delete _pCommand;

			_pCommand = NULL;
		}
	};

	//----------------------------------------------------------
	//	破棄処理実行オブジェクトを受け渡す
	//
	// return: ICommand* … 破棄処理を実行するオブジェクトへのポインタ
	//
	// memo: 暗黙的型変換により、破棄処理オブジェクトを外部に委譲する
	//　　　委譲された者は、ICommand オブジェクトの破棄を必ずすること
	//----------------------------------------------------------
	operator ICommand* (void)
	{
		ICommand* pTemp = _pCommand;

		_pCommand = NULL;

		return pTemp;
	};
};

};//namespace gift

#endif
