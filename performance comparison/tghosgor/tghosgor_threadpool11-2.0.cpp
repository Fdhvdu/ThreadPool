#include<algorithm>	//max
#include<fstream>
#include<thread>	//thread::hardware_concurrency
#include<type_traits>	//result_of
#include"../../lib/header/tool/CChrono_timer.hpp"
#include"../header/test.hpp"
#include"threadpool11-2.0/threadpool11/include/threadpool11/threadpool11.hpp"

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
template<class T>
void test_tghosgor_fibonacci_10(const T thread_count)
{
	threadpool11::Pool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		std::queue<std::future<unsigned long>> que;
		for(size_t j{0};j!=tp.getWorkerCount();++j)
			que.emplace(tp.postWork(std::function<unsigned long()>(fibonacci_10)));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}
}

template<class T>
void test_tghosgor_fibonacci_47(const T thread_count)
{
	threadpool11::Pool tp{thread_count};
	std::queue<std::future<unsigned long>> que;
	for(size_t j{0};j!=tp.getWorkerCount();++j)
		que.emplace(tp.postWork(std::function<unsigned long()>(fibonacci_47)));
	while(que.size())
	{
		que.front().get();
		que.pop();
	}
}

//execute 100000 times
//to test how fast the threadpool can take a new job and execute
template<class T>
void test_tghosgor_iterative_100000(const T thread_count)
{
	threadpool11::Pool tp{thread_count};
	for(auto i{100000+1};--i;)
	{
		std::queue<std::future<void>> que;
		for(size_t j{0};j!=tp.getWorkerCount();++j)
			que.emplace(tp.postWork(std::function<void()>(iterative_100000)));
		while(que.size())
		{
			que.front().get();
			que.pop();
		}
	}
}

template<class T>
void test_tghosgor_iterative_2000000000(const T thread_count)
{
	threadpool11::Pool tp{thread_count};
	std::queue<std::future<void>> que;
	for(size_t j{0};j!=tp.getWorkerCount();++j)
		que.emplace(tp.postWork(std::function<void()>(iterative_2000000000)));
	while(que.size())
	{
		que.front().get();
		que.pop();
	}
}

int main()
{
	using namespace std;
	const auto thread_count{max<result_of<decltype(thread::hardware_concurrency)&()>::type>(4,thread::hardware_concurrency())};

	ofstream ofs{"Fdhvdu vs tghosgor.txt"};

	ofs<<"Fdhvdu's CThreadPool_Ret"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Ret_fibonacci_10<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on fibonacci_10 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Ret_fibonacci_47<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on fibonacci_47"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Ret_iterative_100000<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on iterative_100000 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Ret_iterative_2000000000<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on iterative_2000000000"<<endl;

	ofs<<"Fdhvdu's CThreadPool (Detach)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Detach_fibonacci_10<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on fibonacci_10 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Detach_fibonacci_47<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on fibonacci_47"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Detach_iterative_100000<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on iterative_100000 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Detach_iterative_2000000000<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on iterative_2000000000"<<endl;

	ofs<<"Fdhvdu's CThreadPool (Join)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Join_fibonacci_10<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on fibonacci_10 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Join_fibonacci_47<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on fibonacci_47"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Join_iterative_100000<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on iterative_100000 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_Fdhvdu_CThreadPool_Join_iterative_2000000000<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on iterative_2000000000"<<endl;

	ofs<<"tghosgor"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_tghosgor_fibonacci_10<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on fibonacci_10 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_tghosgor_fibonacci_47<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on fibonacci_47"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_tghosgor_iterative_100000<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on iterative_100000 (execute 100000 times)"<<endl
		<<"\tspends "<<
		nTool::calc_time(test_tghosgor_iterative_2000000000<decltype(thread_count)>,thread_count).duration_milliseconds()
		<<" milliseconds on iterative_2000000000"<<endl;
}