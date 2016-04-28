#include"../header/Fdhvdu.hpp"
#include<queue>
#include"../../header/CThreadPool.hpp"
#include"../../header/CThreadPool_Ret.hpp"
using namespace std;

duration test_Fdhvdu_CThreadPool_ctor_and_dtor()
{
	return nTool::calc_time([=]{
		for(auto i{iteration};i--;)
			nThread::CThreadPool tp{thread_count};
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor()
{
	return nTool::calc_time([=]{
		for(auto i{iteration};i--;)
			nThread::CThreadPool_Ret<void> tp{thread_count};
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_join_specific_N()
{
	nThread::CThreadPool tp{thread_count};
	queue<nThread::CThreadPool::thread_id> que;
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count};j--;)
				que.emplace(tp.add(empty));
			while(que.size())
			{
				tp.join(que.front());
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_join_all_N()
{
	nThread::CThreadPool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count};j--;)
				tp.add(empty);
			tp.join_all();
		}
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_detach_all_N()
{
	nThread::CThreadPool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count};j--;)
				tp.add_and_detach(empty);
			tp.wait_until_all_usable();
		}
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_Ret_specific_N()
{
	nThread::CThreadPool_Ret<void> tp{thread_count};
	queue<nThread::CThreadPool::thread_id> que;
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count};j--;)
				que.emplace(tp.add(empty));
			while(que.size())
			{
				tp.get(que.front());
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_detach_billion()
{
	nThread::CThreadPool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
			tp.add_and_detach(empty);
		tp.wait_until_all_usable();
	}).duration_nanoseconds();
}