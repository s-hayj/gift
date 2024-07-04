//----------------------------------------------------------
// file name: RenderStates.h
//
// memo: レンダリングパイプライン等に転送する、描画パラメーター
//----------------------------------------------------------

#ifndef	__RENDER_STATES_H
#define	__RENDER_STATES_H


namespace gift
{

//----------------------------------------------------------
// name: gift::RenderStates
//
// attrib: final class
//
// memo: レンダーステート入出力管理
//----------------------------------------------------------
class	RenderStates
{
public:
	//----------------------------------------------------------
	//	コピーコンストラクタ
	//
	// parameter: (in)const RenderStates& states … コピー元への参照
	//----------------------------------------------------------
	RenderStates(const RenderStates& states)
	{
	};

	//----------------------------------------------------------
	//	コンストラクタ
	//----------------------------------------------------------
	RenderStates(void)
	{
	};

	//----------------------------------------------------------
	//	デストラクタ
	//----------------------------------------------------------
	~RenderStates(void)
	{
	};

	//----------------------------------------------------------
	//	代入演算子オーバーロード
	//
	// parameter: (in)const RenderStates& states … コピー元への参照
	//
	// return: RenderStates& … コピー後の自身への参照
	//----------------------------------------------------------
	RenderStates& operator = (const RenderStates& states)
	{
		return *this;
	};
};

};//namespace gift

#endif
