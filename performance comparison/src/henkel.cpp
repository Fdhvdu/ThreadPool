#include"../header/henkel.hpp"
#include"../henkel/threadpool-threadpool-0.2.6/boost/threadpool.hpp"
using namespace std;

typedef boost::threadpool::thread_pool<
	boost::threadpool::task_func,
	boost::threadpool::fifo_scheduler,
	boost::threadpool::static_size,
	boost::threadpool::empty_controller,
	boost::threadpool::wait_for_all_tasks> thread_pool;

duration test_henkel_ctor_and_dtor()
{
	return nTool::calc_time([=]{
		for(auto i{iteration};i--;)
			thread_pool tp{thread_count};
	}).duration_nanoseconds();
}

duration test_henkel_all_N()
{
	thread_pool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count+1};--j;)
				tp.schedule(empty);
			tp.wait();
		}
	}).duration_nanoseconds();
}

duration test_henkel_billion()
{
	thread_pool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
			tp.schedule(empty);
		tp.wait();
	}).duration_nanoseconds();
}