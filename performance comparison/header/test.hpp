#ifndef TEST
#define TEST
#include<queue>
#include"../../header/CThreadPool.hpp"
#include"../../header/CThreadPool_Ret.hpp"

unsigned long fibonacci_10();
unsigned long fibonacci_47();
void iterative_100000();
void iterative_2000000000();

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
template<class T>
void test_Fdhvdu_CThreadPool_Detach_fibonacci_10(const T thread_count)
{
	nThread::CThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		std::vector<unsigned long> vec(tp.count());
		for(size_t j{0};j!=tp.count();++j)
			tp.add_and_detach([&,j]{vec[j]=fibonacci_10();});
		tp.wait_until_all_available();
	}
}

template<class T>
void test_Fdhvdu_CThreadPool_Detach_fibonacci_47(const T thread_count)
{
	std::vector<unsigned long> vec(thread_count);
	nThread::CThreadPool tp{thread_count};
	for(size_t i{0};i!=tp.count();++i)
		tp.add_and_detach([&,i]{vec[i]=fibonacci_47();});
}

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
template<class T>
void test_Fdhvdu_CThreadPool_Detach_iterative_100000(const T thread_count)
{
	nThread::CThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
		for(size_t j{0};j!=tp.count();++j)
			tp.add_and_detach(iterative_100000);
}

template<class T>
void test_Fdhvdu_CThreadPool_Detach_iterative_2000000000(const T thread_count)
{
	nThread::CThreadPool tp{thread_count};
	for(size_t i{0};i!=tp.count();++i)
		tp.add_and_detach(iterative_2000000000);
}

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
template<class T>
void test_Fdhvdu_CThreadPool_Join_fibonacci_10(const T thread_count)
{
	nThread::CThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		std::vector<unsigned long> vec(tp.count());
		for(size_t j{0};j!=tp.count();++j)
			tp.add([&,j]{vec[j]=fibonacci_10();});
		tp.join_all();
	}
}

template<class T>
void test_Fdhvdu_CThreadPool_Join_fibonacci_47(const T thread_count)
{
	std::vector<unsigned long> vec(thread_count);
	nThread::CThreadPool tp{thread_count};
	for(size_t i{0};i!=tp.count();++i)
		tp.add([&,i]{vec[i]=fibonacci_47();});
}

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
template<class T>
void test_Fdhvdu_CThreadPool_Join_iterative_100000(const T thread_count)
{
	nThread::CThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		for(size_t j{0};j!=tp.count();++j)
			tp.add(iterative_100000);
		tp.join_all();
	}
}

template<class T>
void test_Fdhvdu_CThreadPool_Join_iterative_2000000000(const T thread_count)
{
	nThread::CThreadPool tp{thread_count};
	for(size_t i{0};i!=tp.count();++i)
		tp.add(iterative_2000000000);
}

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
template<class T>
void test_Fdhvdu_CThreadPool_Ret_fibonacci_10(const T thread_count)
{
	nThread::CThreadPool_Ret<unsigned long> tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		std::queue<nThread::CThreadPool_Ret<unsigned long>::thread_id> que;
		for(size_t j{0};j!=tp.count();++j)
			que.emplace(tp.add(fibonacci_10));
		while(que.size())
		{
			tp.get(que.front());
			que.pop();
		}
	}
}

template<class T>
void test_Fdhvdu_CThreadPool_Ret_fibonacci_47(const T thread_count)
{
	nThread::CThreadPool_Ret<unsigned long> tp{thread_count};
	std::queue<nThread::CThreadPool_Ret<unsigned long>::thread_id> que;
	for(size_t i{0};i!=tp.count();++i)
		que.emplace(tp.add(fibonacci_47));
	while(que.size())
	{
		tp.get(que.front());
		que.pop();
	}
}

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
template<class T>
void test_Fdhvdu_CThreadPool_Ret_iterative_100000(const T thread_count)
{
	nThread::CThreadPool_Ret<void> tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		std::queue<nThread::CThreadPool_Ret<void>::thread_id> que;
		for(size_t j{0};j!=tp.count();++j)
			que.emplace(tp.add(iterative_100000));
		while(que.size())
		{
			tp.get(que.front());
			que.pop();
		}
	}
}

template<class T>
void test_Fdhvdu_CThreadPool_Ret_iterative_2000000000(const T thread_count)
{
	nThread::CThreadPool_Ret<void> tp{thread_count};
	std::queue<nThread::CThreadPool_Ret<void>::thread_id> que;
	for(size_t i{0};i!=tp.count();++i)
		que.emplace(tp.add(iterative_2000000000));
	while(que.size())
	{
		tp.get(que.front());
		que.pop();
	}
}

#endif