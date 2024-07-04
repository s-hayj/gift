
#include <stdio.h>
#include "gift.h"

//----------------------------------------------------------
//	非常に軽い（今回関数だけ）クラス
//----------------------------------------------------------
template<int v = 0>
class	FactoryMethod
{
public:
	enum
	{
		value = v
	};

public:
	int*& Create( int*& pValue )
	{
		printf("FactoryMethod::Create()\n");

		pValue = new int( value );

		return pValue;
	};

	int*& Release( int*& pValue )
	{
		printf("FactoryMethod::Release()\n");

		delete pValue;

		pValue = NULL;

		return pValue;
	};
};

//----------------------------------------------------------
//	int型を生成するグローバル関数
//----------------------------------------------------------
int*& CreateFunction( int*& pValue )
{
	printf("CreateFunction()\n");

	pValue = new int(5);

	return pValue;
};

//----------------------------------------------------------
//	int型を破棄するグローバル関数
//----------------------------------------------------------
int*& ReleaseFunction( int*& pValue )
{
	printf("ReleaseFunction()\n");

	delete pValue;

	pValue = NULL;

	return pValue;
};

//----------------------------------------------------------
//	int型を生成、破棄する静的メンバ関数を持ったクラス
//----------------------------------------------------------
class	StaticFactory
{
public:
	static int*& Create( int*& pValue )
	{
		printf("StaticFactory::Create()\n");

		pValue = new int(0);
		return pValue;
	};

	static int*& Release( int*& pValue )
	{
		printf("StaticFactory::Release()\n");

		delete pValue;

		pValue = NULL;

		return pValue;
	};
};

//----------------------------------------------------------
//	重い（今回はメンバ変数のみ）クラス
//----------------------------------------------------------
class	Factory
{
public:
	int _value;

public:
	Factory(void) : _value( 0 )
	{
	};

	int*& Create( int*& pValue )
	{
		printf("Factory::Create()\n");

		pValue = new int( _value );

		return pValue;
	};

	int*& Release( int*& pValue )
	{
		printf("Factory::Release()\n");

		delete pValue;

		pValue = NULL;

		return pValue;
	};
};

void Sample_NewDelManager(void)
{
	/*
	テンプレートパラメーターによって識別される、任意の型を
	ユーザー指定の生成方法、破棄方法で取り扱えるようにするクラス
	*/

	FactoryMethod<10> funObj;

	gift::NewDelManager<int*> fun(CreateFunction, ReleaseFunction);
	gift::NewDelManager<int*> Fun(StaticFactory::Create, StaticFactory::Release);
	gift::NewDelManager<int*> FunObj(funObj, FactoryMethod<10>::Create,
		funObj, FactoryMethod<10>::Release);

	/*
	テンプレートパラメーターには、生成・破棄処理時に引き渡す変数の型を示す。
	さらに、処理結果を返すときの戻り値の型にもなる。
	上記の記述は上から、関数ポインタの登録、静的メンバ関数による関数ポインタ、
	メンバ関数ポインタの登録による、それぞれ生成と破棄を委託している。

	生成、破棄時には、処理を施す対象への情報しか引数として渡すことができない。
	また、三つ目のようにオブジェクトと、メンバ関数ポインタを登録しているのは、
	オブジェクトをコピーしているのではなく、オブジェクトの型を識別している
	だけなので、これも生成時に独自のパラメーターを渡すことができていない。

	そこで、多少の改善策として、テンプレートに 10 という定数を定義し、生成時の
	初期値としている。しかし、これで解決したとはとても言い難い。
	*/

	int* pInt = 0;

	fun.Initialize( pInt );
	fun.Release( pInt );

	Fun.Initialize( pInt );
	Fun.Release( pInt );

	FunObj.Initialize( pInt );
	FunObj.Release( pInt );

	/*
	上記のように、それぞれ Initialize() で生成、Release() で破棄の実行を
	行っており、その引数には、生成結果を格納する引数と、破棄を行う引数が
	指定されている。
	*/

	Factory* pFactory = new Factory();

	pFactory->_value = 20;

	gift::NewDelManager<int*> ObjFun(pFactory, Factory::Create,
		pFactory, Factory::Release);

	/*
	上記のように、オブジェクトへのポインタと、そのメンバ関数ポインタを指定
	することで、オブジェクトの情報を利用した生成と破棄が行える可能性を提供
	している。当然、NewDelManager<> の生成、破棄処理が行われるまで、引数の
	オブジェクトが正しい値を保持していることが保障されていなければならない。
	*/

	FunObj = ObjFun;

	FunObj.Initialize( pInt );
	FunObj.Release( pInt );

	//	委託したので、生成・破棄は行われない
	ObjFun.Initialize( pInt );
	ObjFun.Release( pInt );

	delete pFactory;

	/*
	上記のように、同じパラメーターであるなら、責任を委託することができる。
	このとき、委託対象がすでに責任を保持していた場合。上書きされてしまう。
	また、委託した場合。処理の実行はスルーされてしまう。

	ここまででは、生成メソッド、破棄メソッドともに関数ポインタや、
	メンバ関数ポインタで、双方共に共通されていたが、そのような決まりは無い
	*/

	gift::NewDelManager<int*> Function_Method(CreateFunction,
		funObj, FactoryMethod<10>::Release);

	Function_Method.Initialize( pInt );
	Function_Method.Release( pInt );

	/*
	上記のように、自由な組み合わせが可能になっている。
	*/
}
