#include"../header/nbsdx.hpp"
#include<cstddef>
#include"../nbsdx/ThreadPool-master/ThreadPool.h"
using namespace std;

void test_nbsdx_fibonacci_10()
{
	nbsdx::concurrent::ThreadPool<constexpr_thread_count> tp;
	for(auto i{100000+1};--i;)
	{
		for(size_t j{0};j!=constexpr_thread_count;++j)
			tp.AddJob(fibonacci_10);
		tp.WaitAll();
	}
}

void test_nbsdx_fibonacci_47()
{
	nbsdx::concurrent::ThreadPool<constexpr_thread_count> tp;
	for(size_t i{0};i!=constexpr_thread_count;++i)
		tp.AddJob(fibonacci_47);
	tp.WaitAll();
}

void test_nbsdx_iterative_100000()
{
	nbsdx::concurrent::ThreadPool<constexpr_thread_count> tp;
	for(auto i{100000+1};--i;)
	{
		for(size_t j{0};j!=constexpr_thread_count;++j)
			tp.AddJob(iterative_100000);
		tp.WaitAll();
	}
}

void test_nbsdx_iterative_2000000000()
{
	nbsdx::concurrent::ThreadPool<constexpr_thread_count> tp;
	for(size_t i{0};i!=constexpr_thread_count;++i)
		tp.AddJob(iterative_2000000000);
	tp.WaitAll();
}