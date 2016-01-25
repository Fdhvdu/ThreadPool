#include"../header/test.h"

namespace
{
	unsigned long fibonacci(const unsigned long i)
	{
		if(i<2)
			return i;
		return fibonacci(i-1)+fibonacci(i-2);
	}
}

void fibonacci_10()
{
	fibonacci(10);
}

void fibonacci_47()
{
	fibonacci(47);
}

void iterative_100000()
{
	volatile auto i{100000+1};
	while(--i)
		;
}

void iterative_1000000000()
{
	volatile auto i{1000000000+1};
	while(--i)
		;
}