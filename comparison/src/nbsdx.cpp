#include"../header/nbsdx.hpp"
#include"../../../../nbsdx/ThreadPool/ThreadPool.h"
using namespace std;

nTest::duration test_nbsdx_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			nbsdx::concurrent::ThreadPool<nTest::thread_count> tp;
	}).duration_nanoseconds();
}

nTest::duration test_nbsdx_all_N(unsigned long cnt)
{
	nbsdx::concurrent::ThreadPool<nTest::thread_count> tp;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				tp.AddJob(nTest::empty);
			tp.WaitAll();
		}
	}).duration_nanoseconds();
}

nTest::duration test_nbsdx_job(unsigned long cnt)
{
	nbsdx::concurrent::ThreadPool<nTest::thread_count> tp;
	return nTool::calc_time([&]{
		while(cnt--)
			tp.AddJob(nTest::empty);
		tp.WaitAll();
	}).duration_nanoseconds();
}