

#ifndef	__TEST_H
#define	__TEST_H

#include <string.h>

class	Math
{
public:
	enum add { Add };
	enum sub { Sub };
	enum mul { Mul };
	enum div { Div };

public:
	template<class A, class B>
		A operator ()(Math::add mode, A a, B b)
	{
		return a + b;
	};

	template<class A, class B>
		A operator ()(Math::sub mode, A a, B b)
	{
		return a - b;
	};

	template<class A, class B>
		A operator ()(Math::mul mode, A a, B b)
	{
		return a * b;
	};

	template<class A, class B>
		A operator ()(Math::div mode, A a, B b)
	{
		return a / b;
	};
};

#endif
