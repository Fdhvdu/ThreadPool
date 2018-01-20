#include"../header/progschj.hpp"
#include<future>
#include<queue>
#include"../../../../progschj/ThreadPool/ThreadPool.h"
using namespace std;

duration test_progschj_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			ThreadPool tp(thread_count);
	}).duration_nanoseconds();
}

duration test_progschj_specific_N(unsigned long cnt)
{
	ThreadPool tp(thread_count);
	queue<future<void>> que;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(thread_count);i--;)
				que.emplace(tp.enqueue(empty));
			while(que.size())
			{
				que.front().get();
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

duration test_progschj_job(unsigned long cnt)
{
	ThreadPool tp(thread_count);
	queue<future<void>> que;
	return nTool::calc_time([&]{
		while(cnt--)
			que.emplace(tp.enqueue(empty));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}).duration_nanoseconds();
}