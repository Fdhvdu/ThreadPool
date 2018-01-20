#include"../header/progschj.hpp"
#include<future>
#include<queue>
#include"../../../../progschj/ThreadPool/ThreadPool.h"
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
			for(auto j{thread_count};j--;)
				que.emplace(tp.enqueue(empty));
			while(que.size())
			{
				que.front().get();
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

duration test_progschj_10_million()
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