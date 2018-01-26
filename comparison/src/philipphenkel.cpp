#include"../header/philipphenkel.hpp"
#include"../../../../philipphenkel/threadpool/boost/threadpool.hpp"
using namespace std;

using thread_pool=boost::threadpool::thread_pool<
	boost::threadpool::task_func,
	boost::threadpool::fifo_scheduler,
	boost::threadpool::static_size,
	boost::threadpool::empty_controller,
	boost::threadpool::wait_for_all_tasks>;

nTest::duration test_philipphenkel_ctor_and_dtor(unsigned long cnt)
{
	return nTool::calc_time([&]{
		while(cnt--)
			thread_pool tp(nTest::thread_count);
	}).duration_nanoseconds();
}

nTest::duration test_philipphenkel_all_N(unsigned long cnt)
{
	thread_pool tp(nTest::thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
		{
			for(auto i(nTest::thread_count);i--;)
				tp.schedule(nTest::empty);
			tp.wait();
		}
	}).duration_nanoseconds();
}

nTest::duration test_philipphenkel_job(unsigned long cnt)
{
	thread_pool tp(nTest::thread_count);
	return nTool::calc_time([&]{
		while(cnt--)
			tp.schedule(nTest::empty);
		tp.wait();
	}).duration_nanoseconds();
}