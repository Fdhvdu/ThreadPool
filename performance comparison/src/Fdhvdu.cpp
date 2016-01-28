#include"../header/Fdhvdu.hpp"
#include<cstddef>
#include<thread>
#include<queue>
#include<vector>
#include"../../header/CThreadPool.hpp"
#include"../../header/CThreadPool_Ret.hpp"
using namespace std;

void test_Fdhvdu_CThreadPool_Detach_fibonacci_10()
{
	nThread::CThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		vector<unsigned long> vec(thread_count);
		for(size_t j{0};j!=thread_count;++j)
			tp.add_and_detach([&,j]{vec[j]=fibonacci_10();});
		tp.wait_until_all_available();
	}
}

void test_Fdhvdu_CThreadPool_Detach_fibonacci_47()
{
	vector<unsigned long> vec(thread_count);
	nThread::CThreadPool tp{thread_count};
	for(size_t i{0};i!=thread_count;++i)
		tp.add_and_detach([&,i]{vec[i]=fibonacci_47();});
}

void test_Fdhvdu_CThreadPool_Detach_iterative_100000()
{
	nThread::CThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
		for(size_t j{0};j!=thread_count;++j)
			tp.add_and_detach(iterative_100000);
}

void test_Fdhvdu_CThreadPool_Detach_iterative_2000000000()
{
	nThread::CThreadPool tp{thread_count};
	for(size_t i{0};i!=thread_count;++i)
		tp.add_and_detach(iterative_2000000000);
}

void test_Fdhvdu_CThreadPool_Join_fibonacci_10()
{
	nThread::CThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		vector<unsigned long> vec(thread_count);
		for(size_t j{0};j!=thread_count;++j)
			tp.add([&,j]{vec[j]=fibonacci_10();});
		tp.join_all();
	}
}

void test_Fdhvdu_CThreadPool_Join_fibonacci_47()
{
	vector<unsigned long> vec(thread_count);
	nThread::CThreadPool tp{thread_count};
	for(size_t i{0};i!=thread_count;++i)
		tp.add([&,i]{vec[i]=fibonacci_47();});
}

void test_Fdhvdu_CThreadPool_Join_iterative_100000()
{
	nThread::CThreadPool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		for(size_t j{0};j!=thread_count;++j)
			tp.add(iterative_100000);
		tp.join_all();
	}
}

void test_Fdhvdu_CThreadPool_Join_iterative_2000000000()
{
	nThread::CThreadPool tp{thread_count};
	for(size_t i{0};i!=thread_count;++i)
		tp.add(iterative_2000000000);
}

void test_Fdhvdu_CThreadPool_Ret_fibonacci_10()
{
	nThread::CThreadPool_Ret<unsigned long> tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		queue<nThread::CThreadPool_Ret<unsigned long>::thread_id> que;
		for(size_t j{0};j!=thread_count;++j)
			que.emplace(tp.add(fibonacci_10));
		while(que.size())
		{
			tp.get(que.front());
			que.pop();
		}
	}
}

void test_Fdhvdu_CThreadPool_Ret_fibonacci_47()
{
	nThread::CThreadPool_Ret<unsigned long> tp{thread_count};
	queue<nThread::CThreadPool_Ret<unsigned long>::thread_id> que;
	for(size_t i{0};i!=thread_count;++i)
		que.emplace(tp.add(fibonacci_47));
	while(que.size())
	{
		tp.get(que.front());
		que.pop();
	}
}

void test_Fdhvdu_CThreadPool_Ret_iterative_100000()
{
	nThread::CThreadPool_Ret<void> tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		queue<nThread::CThreadPool_Ret<void>::thread_id> que;
		for(size_t j{0};j!=thread_count;++j)
			que.emplace(tp.add(iterative_100000));
		while(que.size())
		{
			tp.get(que.front());
			que.pop();
		}
	}
}

void test_Fdhvdu_CThreadPool_Ret_iterative_2000000000()
{
	nThread::CThreadPool_Ret<void> tp{thread_count};
	queue<nThread::CThreadPool_Ret<void>::thread_id> que;
	for(size_t i{0};i!=thread_count;++i)
		que.emplace(tp.add(iterative_2000000000));
	while(que.size())
	{
		tp.get(que.front());
		que.pop();
	}
}


void test_Fdhvdu_CThreadPool_Detach_fibonacci_10_constexpr()
{
	nThread::CThreadPool tp{constexpr_thread_count};
	for(auto i{100000+1};--i;)
	{
		vector<unsigned long> vec(constexpr_thread_count);
		for(size_t j{0};j!=constexpr_thread_count;++j)
			tp.add_and_detach([&,j]{vec[j]=fibonacci_10();});
		tp.wait_until_all_available();
	}
}

void test_Fdhvdu_CThreadPool_Detach_fibonacci_47_constexpr()
{
	vector<unsigned long> vec(constexpr_thread_count);
	nThread::CThreadPool tp{constexpr_thread_count};
	for(size_t i{0};i!=constexpr_thread_count;++i)
		tp.add_and_detach([&,i]{vec[i]=fibonacci_47();});
}

void test_Fdhvdu_CThreadPool_Detach_iterative_100000_constexpr()
{
	nThread::CThreadPool tp{constexpr_thread_count};
	for(auto i{100000+1};--i;)
		for(size_t j{0};j!=constexpr_thread_count;++j)
			tp.add_and_detach(iterative_100000);
}

void test_Fdhvdu_CThreadPool_Detach_iterative_2000000000_constexpr()
{
	nThread::CThreadPool tp{constexpr_thread_count};
	for(size_t i{0};i!=constexpr_thread_count;++i)
		tp.add_and_detach(iterative_2000000000);
}

void test_Fdhvdu_CThreadPool_Join_fibonacci_10_constexpr()
{
	nThread::CThreadPool tp{constexpr_thread_count};
	for(auto i{100000+1};--i;)
	{
		vector<unsigned long> vec(constexpr_thread_count);
		for(size_t j{0};j!=constexpr_thread_count;++j)
			tp.add([&,j]{vec[j]=fibonacci_10();});
		tp.join_all();
	}
}

void test_Fdhvdu_CThreadPool_Join_fibonacci_47_constexpr()
{
	vector<unsigned long> vec(constexpr_thread_count);
	nThread::CThreadPool tp{constexpr_thread_count};
	for(size_t i{0};i!=constexpr_thread_count;++i)
		tp.add([&,i]{vec[i]=fibonacci_47();});
}

void test_Fdhvdu_CThreadPool_Join_iterative_100000_constexpr()
{
	nThread::CThreadPool tp{constexpr_thread_count};
	for(auto i{100000+1};--i;)
	{
		for(size_t j{0};j!=constexpr_thread_count;++j)
			tp.add(iterative_100000);
		tp.join_all();
	}
}

void test_Fdhvdu_CThreadPool_Join_iterative_2000000000_constexpr()
{
	nThread::CThreadPool tp{constexpr_thread_count};
	for(size_t i{0};i!=constexpr_thread_count;++i)
		tp.add(iterative_2000000000);
}

void test_Fdhvdu_CThreadPool_Ret_fibonacci_10_constexpr()
{
	nThread::CThreadPool_Ret<unsigned long> tp{constexpr_thread_count};
	for(auto i{100000+1};--i;)
	{
		queue<nThread::CThreadPool_Ret<unsigned long>::thread_id> que;
		for(size_t j{0};j!=constexpr_thread_count;++j)
			que.emplace(tp.add(fibonacci_10));
		while(que.size())
		{
			tp.get(que.front());
			que.pop();
		}
	}
}

void test_Fdhvdu_CThreadPool_Ret_fibonacci_47_constexpr()
{
	nThread::CThreadPool_Ret<unsigned long> tp{constexpr_thread_count};
	queue<nThread::CThreadPool_Ret<unsigned long>::thread_id> que;
	for(size_t i{0};i!=constexpr_thread_count;++i)
		que.emplace(tp.add(fibonacci_47));
	while(que.size())
	{
		tp.get(que.front());
		que.pop();
	}
}

void test_Fdhvdu_CThreadPool_Ret_iterative_100000_constexpr()
{
	nThread::CThreadPool_Ret<void> tp{constexpr_thread_count};
	for(auto i{100000+1};--i;)
	{
		queue<nThread::CThreadPool_Ret<void>::thread_id> que;
		for(size_t j{0};j!=constexpr_thread_count;++j)
			que.emplace(tp.add(iterative_100000));
		while(que.size())
		{
			tp.get(que.front());
			que.pop();
		}
	}
}

void test_Fdhvdu_CThreadPool_Ret_iterative_2000000000_constexpr()
{
	nThread::CThreadPool_Ret<void> tp{constexpr_thread_count};
	queue<nThread::CThreadPool_Ret<void>::thread_id> que;
	for(size_t i{0};i!=constexpr_thread_count;++i)
		que.emplace(tp.add(iterative_2000000000));
	while(que.size())
	{
		tp.get(que.front());
		que.pop();
	}
}