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

unsigned long fibonacci_10()
{
	return fibonacci(10);
}

unsigned long fibonacci_47()
{
	return fibonacci(47);
}

void iterative_100000()
{
	volatile unsigned long i{100000+1};
	while(--i)
		;
}

void iterative_2000000000()
{
	volatile unsigned long i{2000000000+1};
	while(--i)
		;
}