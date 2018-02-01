#include"../header/mtrebi.hpp"
#include<future>
#include<queue>
#include"../../../../mtrebi/thread-pool/include/ThreadPool.h"
using namespace std;

nTest::duration test_mtrebi_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			ThreadPool tp(nTest::thread_count);
	}).duration_nanoseconds();
}

nTest::duration test_mtrebi_init_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
		{
			ThreadPool tp(nTest::thread_count);
			tp.init();
			tp.shutdown();
		}
	}).duration_nanoseconds();
}

nTest::duration test_mtrebi_specific_N(unsigned long cnt)
{
	ThreadPool tp(nTest::thread_count);
	tp.init();
	queue<future<void>> que;
	const auto dur(nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				que.emplace(tp.submit(nTest::empty));
			while(que.size())
			{
				que.front().get();
				que.pop();
			}
		}
	}).duration_nanoseconds());
	tp.shutdown();
	return dur;
}

nTest::duration test_mtrebi_job(unsigned long cnt)
{
	ThreadPool tp(nTest::thread_count);
	tp.init();
	queue<future<void>> que;
	const auto dur(nTool::calc_time([&]{
		while(cnt--)
			que.emplace(tp.submit(nTest::empty));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}).duration_nanoseconds());
	tp.shutdown();
	return dur;
}