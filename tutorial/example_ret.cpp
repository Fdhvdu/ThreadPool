#include<chrono>
#include<iostream>
#include<mutex>
#include<queue>
#include<random>
#include<thread>
#include"../header/CThreadPool_Ret.hpp"

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
		cout<<"thread "<<i<<" wait "<<sec<<" sec"<<endl;
		return i;
	}
}

int main()
{
	using namespace std;
	nThread::CThreadPool_Ret<size_t> tp{4};	//merely size_t, not size_t()
	queue<nThread::CThreadPool_Ret<size_t>::thread_id> que;
	for(size_t i{0};i!=tp.size();++i)
		que.emplace(tp.add(add_func,size_t(i)));
	tp.wait(que.front());	//tp will block here until thread[que.front()] complete
	cout<<tp.get(que.front())<<" complete"<<endl;	//get the return value from lambda
	//tp.get(que.front());	//do not call same id twice
	que.pop();

	if(tp.valid(que.front()))	//it means thread[que.front()] has a function, and thread[que.front()] is running
		cout<<tp.get(que.front())<<" complete"<<endl;	//tp will block here until thread[que.front()] complete and return value from lambda
	if(tp.valid(que.front()))	//this will return false, because you call tp.get(que.front())
		cout<<"hi, something must wrong"<<endl;

	//you don't need to call every get to guarantee all threads are not valid
	//the destructor of CThreadPool_Ret will deal with this
}