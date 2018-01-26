#include"../header/progschj.hpp"
#include<future>
#include<queue>
#include"../../../../progschj/ThreadPool/ThreadPool.h"
using namespace std;

nTest::duration test_progschj_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			ThreadPool tp(nTest::thread_count);
	}).duration_nanoseconds();
}

nTest::duration test_progschj_specific_N(unsigned long cnt)
{
	ThreadPool tp(nTest::thread_count);
	queue<future<void>> que;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				que.emplace(tp.enqueue(nTest::empty));
			while(que.size())
			{
				que.front().get();
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

nTest::duration test_progschj_job(unsigned long cnt)
{
	ThreadPool tp(nTest::thread_count);
	queue<future<void>> que;
	return nTool::calc_time([&]{
		while(cnt--)
			que.emplace(tp.enqueue(nTest::empty));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}).duration_nanoseconds();
}