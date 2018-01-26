#include"../header/Tyler-Hardin.hpp"
#include<future>
#include<queue>
#include"../../../../Tyler-Hardin/thread_pool/thread_pool.hpp"
using namespace std;

nTest::duration test_TylerHardin_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			thread_pool tp(nTest::thread_count);
	}).duration_nanoseconds();
}

nTest::duration test_TylerHardin_specific_N(unsigned long cnt)
{
	thread_pool tp(nTest::thread_count);
	queue<future<void>> que;
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				que.emplace(tp.async(nTest::empty));
			while(que.size())
			{
				que.front().get();
				que.pop();
			}
		}
	}).duration_nanoseconds();
}

nTest::duration test_TylerHardin_job(unsigned long cnt)
{
	thread_pool tp(nTest::thread_count);
	queue<future<void>> que;
	return nTool::calc_time([&]{
		while(cnt--)
			que.emplace(tp.async(nTest::empty));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}).duration_nanoseconds();
}