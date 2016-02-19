#include"../header/tghosgor.hpp"
#include<functional>
#include<future>
#include<queue>
#include"../tghosgor/threadpool11-2.0/threadpool11/include/threadpool11/threadpool11.hpp"
using namespace std;

duration test_tghosgor_ctor_and_dtor()
{
	return nTool::calc_time([=]{
		for(auto i{iteration};i--;)
			threadpool11::Pool tp{thread_count};
	}).duration_nanoseconds();
}

duration test_tghosgor_specific_N()
{
	threadpool11::Pool tp{thread_count};
	queue<future<void>> que;
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count};j--;)
				que.emplace(tp.postWork(function<void()>(empty)));
			while(que.size())
			{
				que.front().get();
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

duration test_tghosgor_all_N()
{
	threadpool11::Pool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count};j--;)
				tp.postWork(function<void()>(empty));
			tp.waitAll();
		}
	}).duration_nanoseconds();
}

duration test_tghosgor_billion()
{
	threadpool11::Pool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
			tp.postWork(function<void()>(empty));
		tp.waitAll();
	}).duration_nanoseconds();
}