#include<chrono>
#include<iostream>
#include<mutex>
#include<random>
#include<queue>
#include<thread>
#include"../header/CThreadPool.hpp"

namespace
{
	std::mutex mut;

	size_t get()
	{
		using namespace std;
		static mt19937 mu{static_cast<mt19937::result_type>(chrono::high_resolution_clock::now().time_since_epoch().count())};
		return mu()%4;
	}

	std::size_t add_func(const std::size_t i)
	{
		using namespace std;
		const auto sec{get()};
		this_thread::sleep_for(chrono::seconds{sec});
		lock_guard<mutex> lock{mut};
		cout<<"add - thread "<<i<<" wait "<<sec<<" sec"<<endl;
		return i;
	}

	std::size_t add_and_detach_func(const std::size_t i)
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
	nThread::CThreadPool tp{4};
	queue<nThread::CThreadPool::thread_id> que;

	cout<<"stage 1"<<endl;
	for(size_t i{0};i!=tp.size();++i)
		tp.add_and_detach(add_and_detach_func,i);
	tp.join_all();	//this will not block, because you use add_and_detach
	
	cout<<"stage 2"<<endl;
	for(size_t i{0};i!=tp.size();++i)
		que.push(tp.add(add_func,i));	//tp will block here until add_and_detach_func complete
	for(size_t i{0};i!=tp.size();++i)
	{
		tp.join(que.front());	//tp will block here until the i of thread complete
		que.pop();
	}

	cout<<"stage 3"<<endl;
	for(size_t i{0};i!=tp.size();++i)
		tp.add_and_detach(add_and_detach_func,i);
	tp.wait_until_all_usable();	//this will block until all detach threads complete add_and_detach_func

	cout<<"stage 4"<<endl;
	for(size_t i{0};i!=tp.size();++i)
		tp.add(add_func,i);	//tp will not block here, because you join all thread
	tp.join_all();	//tp will block here until add_func complete, it is same as
					//for(size_t i(0);i!=tp.size();++i)
	
	cout<<"stage 5"<<endl;
	for(size_t i{0};i!=tp.size();++i)
		tp.add(add_func,i);

	//you don't need to call join_all to guarantee all threads are joining
	//the destructor of CThreadPool will deal with this

	//something else you have to notice
	//CThreadPool::join_all will not block CThreadPool::add, and vice versa
}