//----------------------------------------------------------
// file name: GenericLibrary.h
//
// memo: 特に利用用途が定まっていないオブジェクト群
//----------------------------------------------------------

#ifndef	__GENERIC_LIBRARY_H
#define	__GENERIC_LIBRARY_H

namespace gift
{

const class MultiNull{				//	この const オブジェクトは
public:
	MultiNull(){};
	template<class T>				//	あらゆる型の非メンバへの
		operator T*() const{		//		ポインタに変換できて
			return 0;
	}
#ifndef	__MWERKS__
	template<class C, class T>		//	あらゆる型のメンバへの
		operator T C::*() const{	//		ポインタにも変換できる
			return 0;
	}
#endif	__MWERKS__
private:
	void operator &() const;		//	アドレスは取得できない
} Null;								//	Null という名前を持つ

//----------------------------------------------------------
// name: gift::NullType
//
// attrib: final class
//
// memo: null 識別用の型
//----------------------------------------------------------
class	NullType
{
};

//----------------------------------------------------------
// name: gift::Int2Type
//
// attrib: template final struct
//
// memo: 数値別の型を生成する
//----------------------------------------------------------
template<int v>
struct	Int2Type
{
	enum { value = v;};
};

//----------------------------------------------------------
// name: gift::WriteMode
//
// attrib: final class
//
// memo: データ書き込み時の動作を識別する
//----------------------------------------------------------
class	WriteMode
{
public:
	//----------------------------------------------------------
	// name: gift::WriteMode::MODE
	//
	// attrib: public enumerated
	//
	// memo: データ書き込み時の動作指定
	//----------------------------------------------------------
	enum	MODE
	{
		Once,		//	一度だけの書き込み（上書きを禁止する）
		Overwrite,	//	上書きを許可する
	};
};

};//namespace gift

#endif
