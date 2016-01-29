#include"../header/nbsdx.hpp"
#include"../nbsdx/ThreadPool-master/ThreadPool.h"
using namespace std;

duration test_nbsdx_ctor_and_dtor()
{
	return nTool::calc_time([=]{
		for(auto i{iteration};i--;)
			nbsdx::concurrent::ThreadPool<thread_count> tp;
	}).duration_nanoseconds();
}

duration test_nbsdx_all_N()
{
	nbsdx::concurrent::ThreadPool<thread_count> tp;
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count+1};--j;)
				tp.AddJob(empty);
			tp.WaitAll();
		}
	}).duration_nanoseconds();
}

duration test_nbsdx_billion()
{
	nbsdx::concurrent::ThreadPool<thread_count> tp;
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
			tp.AddJob(empty);
		tp.WaitAll();
	}).duration_nanoseconds();
}