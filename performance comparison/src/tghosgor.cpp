#include"../header/tghosgor.hpp"
#include<functional>
#include<future>
#include<queue>
#include"../../../../tghosgor/threadpool11/threadpool11/include/threadpool11/threadpool11.hpp"
using namespace std;

nTest::duration test_tghosgor_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			threadpool11::Pool tp(nTest::thread_count);
	}).duration_nanoseconds();
}

nTest::duration test_tghosgor_specific_N(unsigned long cnt)
{
	threadpool11::Pool tp(nTest::thread_count);
	queue<future<void>> que;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				que.emplace(tp.postWork(function<void()>(nTest::empty)));
			while(que.size())
			{
				que.front().get();
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

nTest::duration test_tghosgor_all_N(unsigned long cnt)
{
	threadpool11::Pool tp(nTest::thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				tp.postWork(function<void()>(nTest::empty));
			tp.waitAll();
		}
	}).duration_nanoseconds();
}

nTest::duration test_tghosgor_job(unsigned long cnt)
{
	threadpool11::Pool tp(nTest::thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
			tp.postWork(function<void()>(nTest::empty));
		tp.waitAll();
	}).duration_nanoseconds();
}