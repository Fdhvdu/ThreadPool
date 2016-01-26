#include"../header/progschj.hpp"
#include<cstddef>
#include<future>
#include<queue>
#include"../progschj/ThreadPool-master/ThreadPool.h"
using namespace std;

void test_progschj_fibonacci_10()
{
	ThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		queue<future<unsigned long>> que;
		for(size_t j{0};j!=thread_count;++j)
			que.emplace(tp.enqueue(fibonacci_10));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}
}

void test_progschj_fibonacci_47()
{
	ThreadPool tp{thread_count};
	queue<future<unsigned long>> que;
	for(size_t i{0};i!=thread_count;++i)
		que.emplace(tp.enqueue(fibonacci_47));
	while(que.size())
	{
		que.front().get();
		que.pop();
	}
}

void test_progschj_iterative_100000()
{
	ThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		queue<future<void>> que;
		for(size_t j{0};j!=thread_count;++j)
			que.emplace(tp.enqueue(iterative_100000));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}
}

void test_progschj_iterative_2000000000()
{
	ThreadPool tp{thread_count};
	queue<future<void>> que;
	for(size_t i{0};i!=thread_count;++i)
		que.emplace(tp.enqueue(iterative_2000000000));
	while(que.size())
	{
		que.front().get();
		que.pop();
	}
}