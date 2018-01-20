#include"../header/nbsdx.hpp"
#include"../../../../nbsdx/ThreadPool/ThreadPool.h"
using namespace std;

duration test_nbsdx_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			nbsdx::concurrent::ThreadPool<thread_count> tp;
	}).duration_nanoseconds();
}

duration test_nbsdx_all_N(unsigned long cnt)
{
	nbsdx::concurrent::ThreadPool<thread_count> tp;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(thread_count);i--;)
				tp.AddJob(empty);
			tp.WaitAll();
		}
	}).duration_nanoseconds();
}

duration test_nbsdx_job(unsigned long cnt)
{
	nbsdx::concurrent::ThreadPool<thread_count> tp;
	return nTool::calc_time([&]{
		while(cnt--)
			tp.AddJob(empty);
		tp.WaitAll();
	}).duration_nanoseconds();
}