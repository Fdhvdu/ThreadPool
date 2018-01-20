#include"../header/Fdhvdu.hpp"
#include<queue>
#include"../../header/CThreadPool.hpp"
#include"../../header/CThreadPool_Ret.hpp"
using namespace std;

nTest::duration test_Fdhvdu_CThreadPool_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			nThread::CThreadPool tp(nTest::thread_count);
	}).duration_nanoseconds();
}

nTest::duration test_Fdhvdu_CThreadPool_Ret_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			nThread::CThreadPool_Ret<void> tp(nTest::thread_count);
	}).duration_nanoseconds();
}

nTest::duration test_Fdhvdu_CThreadPool_join_specific_N(unsigned long cnt)
{
	nThread::CThreadPool tp(nTest::thread_count);
	queue<nThread::CThreadPool::thread_id> que;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				que.emplace(tp.add(nTest::empty));
			while(que.size())
			{
				tp.join(que.front());
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

nTest::duration test_Fdhvdu_CThreadPool_join_all_N(unsigned long cnt)
{
	nThread::CThreadPool tp(nTest::thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				tp.add(nTest::empty);
			tp.join_all();
		}
	}).duration_nanoseconds();
}

nTest::duration test_Fdhvdu_CThreadPool_detach_all_N(unsigned long cnt)
{
	nThread::CThreadPool tp(nTest::thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				tp.add_and_detach(nTest::empty);
			tp.wait_until_all_usable();
		}
	}).duration_nanoseconds();
}

nTest::duration test_Fdhvdu_CThreadPool_Ret_specific_N(unsigned long cnt)
{
	nThread::CThreadPool_Ret<void> tp(nTest::thread_count);
	queue<nThread::CThreadPool::thread_id> que;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				que.emplace(tp.add(nTest::empty));
			while(que.size())
			{
				tp.get(que.front());
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

nTest::duration test_Fdhvdu_CThreadPool_detach_job(unsigned long cnt)
{
	nThread::CThreadPool tp(nTest::thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
			tp.add_and_detach(nTest::empty);
		tp.wait_until_all_usable();
	}).duration_nanoseconds();
}