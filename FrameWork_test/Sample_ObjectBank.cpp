

#include <stdio.h>
#include "gift.h"

class	Object
{
public:
	int	_id;

	static int s_count;

public:
	Object(void)
	{
	};

	~Object(void)
	{
	};

	//	生成されるごとに、回数を刻んでいく
	static Object*& Create(Object*& pValue)
	{
		pValue = new Object();

		pValue->_id = Object::s_count;

		Object::s_count++;

		return pValue;
	};

	static Object*& Release(Object*& pValue)
	{
		delete pValue;

		pValue = NULL;

		return pValue;
	};
};

int Object::s_count = 0;


void Sample_ObjectBank(void)
{
	/*
	テンプレートパラメーターの型（主にポインタ型）のオブジェクトを再利用する
	ために、在庫管理をするクラス。
	出荷した数を管理するのではなく、生成済みで出荷していないオブジェクトの
	管理をする。
	*/

	gift::ObjectBank<Object*> bank;

	/*
	ユーザーはテンプレートパラメーター（今回は Object* 型）を発行してもらう。
	また、必要なくなったときは、それを返却することができる。
	これにより、返却されたものを再度出荷し、在庫がなくなった場合に初めて、
	新しく生成する。
	これは、動的なメモリ確保が必要でいて、生成と破棄が頻繁に行われる処理に
	特に効果を期待するものである。
	よって、ObjectBank<> はパラメーターの初期化と破棄方法を知っている必要がある
	*/

	bank.Register(gift::NewDelManager<Object*>(Object::Create, Object::Release));

	/*
	生成と破棄時に受け渡される型は、ObjectBank<> のパラメーターなので、
	NewDelManager<> のパラメーターと一致していなくてはならない。
	これは、コンストラクタの引数として渡しても、同様の結果を得る。
	*/

	Object* pTemp[20];

	//	10個Objectを発行してもらう
	for (int i = 0; i < 10; i++)
	{
		pTemp[i] = bank.Order();

		printf("%d\n", pTemp[i]->_id);
	}

	//	使い終わったので返却
	for (int i = 0; i < 10; i++)
	{
		//	スタックのように溜めていく
		bank.Return(pTemp[i]);
	}

	//	20個発行してもらう
	for (int i = 0; i < 20; i++)
	{
		pTemp[i] = bank.Order();

		printf("%d\n", pTemp[i]->_id);
	}

	//	使い終わったので返却
	for (int i = 0; i < 20; i++)
	{
		bank.Return(pTemp[i]);
	}

	/*
	0～9 がもう一度使われているように、返却されたものから再度使っていく
	要になります。
	残念な点として、登録した生成、破棄処理は、初めて発行したときと、管理を
	破棄したときにのみ呼び出されるため、再利用する際の初期化処理は、
	利用者が任意で行うことになります。
	*/

	bank.Release();

	/*
	上記のメンバ関数により、在庫を全て破棄します。
	*/
}
