#include"../header/tghosgor.hpp"
#include<cstddef>
#include<functional>
#include<future>
#include<queue>
#include"../tghosgor/threadpool11-2.0/threadpool11/include/threadpool11/threadpool11.hpp"
using namespace std;

void test_tghosgor_fibonacci_10()
{
	threadpool11::Pool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		queue<future<unsigned long>> que;
		for(size_t j{0};j!=thread_count;++j)
			que.emplace(tp.postWork(function<unsigned long()>(fibonacci_10)));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}
}

void test_tghosgor_fibonacci_47()
{
	threadpool11::Pool tp{thread_count};
	queue<future<unsigned long>> que;
	for(size_t i{0};i!=thread_count;++i)
		que.emplace(tp.postWork(function<unsigned long()>(fibonacci_47)));
	while(que.size())
	{
		que.front().get();
		que.pop();
	}
}

void test_tghosgor_iterative_100000()
{
	threadpool11::Pool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		queue<future<void>> que;
		for(size_t j{0};j!=thread_count;++j)
			que.emplace(tp.postWork(function<void()>(iterative_100000)));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}
}

void test_tghosgor_iterative_2000000000()
{
	threadpool11::Pool tp{thread_count};
	queue<future<void>> que;
	for(size_t i{0};i!=thread_count;++i)
		que.emplace(tp.postWork(function<void()>(iterative_2000000000)));
	while(que.size())
	{
		que.front().get();
		que.pop();
	}
}