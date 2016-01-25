#include<algorithm>
#include<iostream>
#include<thread>
#include<type_traits>
#include"../../lib/header/tool/CChrono_timer.hpp"
#include"threadpool11-2.0/threadpool11/include/threadpool11/threadpool11.hpp"
#include"../header/CThreadPool.hpp"
#include"header/test.h"

int main()
{
	using namespace std;
	const auto thread_count{max<result_of<decltype(thread::hardware_concurrency)&()>::type>(4,thread::hardware_concurrency())};
	//threadpool11::Pool pool{thread_count};
	nTool::CChrono_timer timer;
	timer.start();
	iterative_1000000000();
	timer.stop();
	cout<<timer.duration_nanoseconds()<<endl;
}