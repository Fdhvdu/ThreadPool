#include"../header/progschj.hpp"
#include<future>
#include<queue>
#include"../progschj/ThreadPool-master/ThreadPool.h"
using namespace std;

duration test_progschj_ctor_and_dtor()
{
	return nTool::calc_time([=]{
		for(auto i{iteration};i--;)
			ThreadPool tp{thread_count};
	}).duration_nanoseconds();
}

duration test_progschj_specific_N()
{
	ThreadPool tp{thread_count};
	queue<future<void>> que;
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count+1};--j;)
				que.emplace(tp.enqueue(empty));
			while(que.size())
			{
				que.front().get();
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

duration test_progschj_billion()
{
	ThreadPool tp{thread_count};
	queue<future<void>> que;
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
			que.emplace(tp.enqueue(empty));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}).duration_nanoseconds();
}