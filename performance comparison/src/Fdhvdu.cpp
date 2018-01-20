#include"../header/Fdhvdu.hpp"
#include<queue>
#include"../../header/CThreadPool.hpp"
#include"../../header/CThreadPool_Ret.hpp"
using namespace std;

duration test_Fdhvdu_CThreadPool_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			nThread::CThreadPool tp(thread_count);
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			nThread::CThreadPool_Ret<void> tp(thread_count);
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_join_specific_N(unsigned long cnt)
{
	nThread::CThreadPool tp(thread_count);
	queue<nThread::CThreadPool::thread_id> que;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(thread_count);i--;)
				que.emplace(tp.add(empty));
			while(que.size())
			{
				tp.join(que.front());
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_join_all_N(unsigned long cnt)
{
	nThread::CThreadPool tp(thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(thread_count);i--;)
				tp.add(empty);
			tp.join_all();
		}
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_detach_all_N(unsigned long cnt)
{
	nThread::CThreadPool tp(thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(thread_count);i--;)
				tp.add_and_detach(empty);
			tp.wait_until_all_usable();
		}
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_Ret_specific_N(unsigned long cnt)
{
	nThread::CThreadPool_Ret<void> tp(thread_count);
	queue<nThread::CThreadPool::thread_id> que;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(thread_count);i--;)
				que.emplace(tp.add(empty));
			while(que.size())
			{
				tp.get(que.front());
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

duration test_Fdhvdu_CThreadPool_detach_job(unsigned long cnt)
{
	nThread::CThreadPool tp(thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
			tp.add_and_detach(empty);
		tp.wait_until_all_usable();
	}).duration_nanoseconds();
}