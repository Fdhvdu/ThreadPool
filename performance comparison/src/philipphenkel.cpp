#include"../header/philipphenkel.hpp"
#include"../../../../philipphenkel/threadpool/boost/threadpool.hpp"
using namespace std;

using thread_pool=boost::threadpool::thread_pool<
	boost::threadpool::task_func,
	boost::threadpool::fifo_scheduler,
	boost::threadpool::static_size,
	boost::threadpool::empty_controller,
	boost::threadpool::wait_for_all_tasks>;

duration test_philipphenkel_ctor_and_dtor()
{
	return nTool::calc_time([=]{
		for(auto i{iteration};i--;)
			thread_pool tp{thread_count};
	}).duration_nanoseconds();
}

duration test_philipphenkel_all_N()
{
	thread_pool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
		{
			for(auto j{thread_count};j--;)
				tp.schedule(empty);
			tp.wait();
		}
	}).duration_nanoseconds();
}

duration test_philipphenkel_10_million()
{
	thread_pool tp{thread_count};
	return nTool::calc_time([&]{
		for(auto i{iteration};i--;)
			tp.schedule(empty);
		tp.wait();
	}).duration_nanoseconds();
}