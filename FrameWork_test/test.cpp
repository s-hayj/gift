

#include <stdio.h>
#include "gift.h"

using namespace gift;


class TestRelease
{
public:
	void Release(void)
	{
		printf("cull Release()\n");

		delete this;
	};

private:
	~TestRelease(void)
	{
		printf("破棄完了\n");
	};
};

class TestDelete
{
public:
	~TestDelete(void)
	{
		printf("破棄完了\n");
	};
};

//----------------------------------------------------------
//	DeleteHelper の使用例
//----------------------------------------------------------
void Sample_DeleteHelper(void)
{
	/*
	DeleteHelper<> は ICommand を継承しており、
	破棄の責任を ICommand へ委託することができる。
	*/

	gift::ICommand* pCommand = gift::DeleteHelper<true>(new TestRelease());

	/*
	上記では、DeleteHelper のパラメーターに true を直接指定する。
	これにより、引数の TestRelease のインスタンスは、Release() メンバ関数
	によって破棄されるようになる。
	当然、TestRelease に Release() メンバ関数が実装されていなければならない。
	*/

	pCommand->Execute();
	delete pCommand;

	/*
	ICommand に委託した場合。上記のように必ず delete演算子で破棄する必要がある。
	このときに、登録された TestRelease の Release() メンバ関数が呼び出される。
	また、ICommand::Execute() でも、同様の結果が得られる。
	しかし、TestRelease の Release() を呼び出すのは、どちらか一回のみである。
	*/

	DeleteHelper<false> test(new int(5));

	/*
	int 型のように、Release() メンバ関数を持たないインスタンスの場合。
	テンプレートパラメーターに false を指定することで、delete演算子によって
	破棄処理を行うようになる。
	*/

	DeleteHelper<false> hoge( test );

	/*
	コピーコンストラクタによって、破棄の責任を委託することができる。
	この場合、責任を失った test が、破棄処理を行おうとしてもスルーされる。
	*/

	test();
	hoge();

	/*
	上記では、test() の振る舞いはスルーされ、hoge() によって、int型の
	インスタンスは、delete演算子を通して破棄されます。
	また、破棄の責任をだれにも委託せず、破棄処理を実行しなかった場合。
	DeleteHelper<> は自身の破棄と共に、格納されたインスタンスの破棄を
	実行します。
	*/

	DeleteHelper<false>* pHoge = new DeleteHelper<false>(new TestDelete());

	delete pHoge;

	DeleteHelper<true> hige(new TestRelease());

	/*
	DeleteHelper<> によって、インスタンスの破棄を委託する場合。
	コンストラクタのオーバーロードによって、格納する型を選択しています。
	よって、以下のような方法を取らなければならない場合がある。
	*/

	int* pInt = new int(10);

	DeleteHelper<>((int*)pInt);

	/*
	テンプレートパラメーターはデフォルトで false を指定しているので、
	今回は省略しています。
	何らかの型へのポインタ型を指定する場合。
	何の型なのか、明示的にしなければならない。
	*/
}

