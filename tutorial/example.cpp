#include<chrono>
#include<iostream>
#include<mutex>
#include<random>
#include<thread>
#include"../lib/CCThreadPool.h"

namespace
{
	std::mutex mut;

	size_t get()
	{
		using namespace std;
		static mt19937 mu{static_cast<mt19937::result_type>(chrono::high_resolution_clock::now().time_since_epoch().count())};
		return mu()%4+1;
	}

	int add_func(int i)
	{
		using namespace std;
		const auto sec{get()};
		this_thread::sleep_for(chrono::seconds{sec});
		lock_guard<mutex> lock{mut};
		cout<<"add - thread "<<i<<" wait "<<sec<<" sec"<<endl;
		return i;
	}

	int add_and_detach_func(int i)
	{
		using namespace std;
		const auto sec{get()};
		this_thread::sleep_for(chrono::seconds{sec});
		lock_guard<mutex> lock{mut};
		cout<<"add_and_detach - thread "<<i<<" wait "<<sec<<" sec"<<endl;
		return i;
	}
}

int main()
{
	using namespace std;
	nTool::CThreadPool tp{4};

	cout<<"stage 1"<<endl;
	for(size_t i{0};i!=tp.count();++i)
		tp.add_and_detach(add_and_detach_func,i);
	tp.join_all();	//this will not block, because you use add_and_detach

	cout<<"stage 2"<<endl;
	for(size_t i{0};i!=tp.count();++i)
		tp.add(add_func,i);	//tp will block here until add_and_detach_func complete
	for(size_t i{0};i!=tp.count();++i)
		tp.join(i);	//tp will block here until the i of thread complete

	cout<<"stage 3"<<endl;
	for(size_t i{0};i!=tp.count();++i)
		tp.add_and_detach(add_and_detach_func,i);
	tp.wait_until_all_available();	//this will block until all detach threads complete add_and_detach_func

	cout<<"stage 4"<<endl;
	for(size_t i{0};i!=tp.count();++i)
		tp.add(add_func,i);	//tp will not block here, because you join all thread
	tp.join_all();	//tp will block here until add_func complete, it is same as
					//for(size_t i(0);i!=tp.count();++i)
					//	tp.join(i);

	cout<<"stage 5"<<endl;
	for(size_t i{0};i!=tp.count();++i)
		tp.add(add_func,i);
	cout<<"thread "<<tp.join_any()<<" complete"<<endl;	//join any thread without specify which one
	tp.join_all();

	cout<<"stage 6"<<endl;
	for(size_t i{0};i!=tp.count();++i)
		tp.add(add_func,i);
	tp.join(0);
	tp.join_any();	//calling join prior to join_any is ok
					//but calling join_any with join (or join_all) is not ok when using multi-thread, such as the code below

	//here is an incorrect example
	//for(size_t i(0);i!=tp.count();++i)
	//	tp.add(add_func,i);
	//thread thr([&]{tp.join(0);});
	//tp.join_any();	//please, don't do this
	//					//do not combine these function together in multi-thread
	//					//use join or join_any each time
	//					//otherwise, it will make some threads which are calling join_any cannot get notification
	//thr.join();

	//however, here is an correct example
	tp.join_any();
	tp.join_all();	//because, this is in single thread

	cout<<"stage 7"<<endl;
	for(size_t i{0};i!=tp.count();++i)
		tp.add(add_func,i);
	thread thr([&]{tp.join_any();});
	tp.join_any();	//ok, no problem
	thr.join();
	tp.join_all();

	//in short, do not call join_any with join and join_all in 2 (or higher) threads
	//the user has to guarantee that
	//every threads' join can be called only once after calling assign

	cout<<"stage 8"<<endl;
	for(size_t i{0};i!=tp.count();++i)
		tp.add(add_func,i);
	tp.join_any();
	//you don't need to call join_all to guarantee all threads are joining
	//the destructor of CThreadPool will deal with this

	//something else you have to notice
	//CThreadPool::join_all will not block CThreadPool::add, and vice versa
}