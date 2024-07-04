

#include <stdio.h>
#include "gift.h"

using namespace gift;

class	Player
{
public:
	void DrawHead(RenderStates* pStates)
	{
		printf("Start_PlayerHead\n");
	};

	void DrawBody(RenderStates* pStates)
	{
		printf("Start_PlayerBody\n");
	};

	void DrawLeg(RenderStates* pStates)
	{
		printf("Start_PlayerLeg\n");
	};

	void EndDraw(RenderStates* pStates)
	{
		printf("End_Player\n");
	};
};

class	Enemy
{
public:
	void DrawEnemy(RenderStates* pStates)
	{
		printf("Start_Enemy\n");
	};

	void DrawEnemyBullet(RenderStates* pStates)
	{
		printf("Start_EnemyBullet\n");
	};

	void EndDraw(RenderStates* pStates)
	{
		printf("End_Enemy\n");
	};
};

/*
今後フレームワークが描画の実行順番を制御することを前提に、
考案されたクラスのテスト
*/
void Sample_DrawDelegate(void)
{
	using namespace gift::Renderable;

	Player player;

	DrawDelegate DrawPlayer(&player, Player::DrawHead,
		&DrawDelegate::Null<Player>());

	/*
	DrawDelegate は、自身で描画の実行を呼び出すことはできない。
	本来ユーザーが ICommandインターフェースを継承して実装するものなのだが、
	DrawDelegate は、継承ではなくコンポジットで継承の肩代わりをし、
	フレームワークに、描画方法を登録する。
	*/

	DrawPlayer.Register(gift::WriteMode::Overwrite, &player,
		&DrawDelegate::Null<Player>(), &DrawDelegate::Null<Player>());

	/*
	上記のように、後から描画内容を変更することもできる。このときの第一引数は、
	すでに登録されている描画内容の上書き有無を指示する。
	肝心な描画内容だが、何もさせないとき、何もしないメンバ関数を登録するところ
	だが、NULLポインタを指定できるようにする。しかし、描画実行オブジェクトの
	メンバ関数でなければならないため、描画実行オブジェクトのメンバ関数ポインタ
	型にキャストしたNULLポインタを提供できるように、DrawDelete::Null<>を提供。
	テンプレートパラメーターは、描画実行オブジェクトの型を指定して一時的に生成
	する。&演算子をオーバーロードしているので、これで請求された型のNULLポインタ
	を引き渡せる。
	他の方法として、DRAWDELEGATE_NULL(T) というマクロ関数もある。
	*/

	DrawPlayer.Register(gift::WriteMode::Overwrite,
		&player, Player::DrawLeg, &DrawDelegate::Null<Player>());

	Command* pCommand = DrawPlayer;

	/*
	自身では実行できないため、IDrawCommand に委譲する。
	一度実行を委譲したら、もう委譲することはできない。
	また、IDrawCommnad の破棄も委譲したことを忘れないように
	*/

	pCommand->DrawBegin(NULL);
	pCommand->DrawEnd(NULL);

	delete pCommand;
}
