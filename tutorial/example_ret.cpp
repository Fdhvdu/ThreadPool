#include<chrono>
#include<iostream>
#include<mutex>
#include<random>
#include"../lib/CCThreadPool_Ret.h"

namespace
{
	std::mutex mut;

	size_t get()
	{
		using namespace std;
		static mt19937 mu(static_cast<mt19937::result_type>(chrono::high_resolution_clock::now().time_since_epoch().count()));
		return mu()%4+1;
	}
}

int main()
{
	using namespace std;
	nTool::CThreadPool_Ret<size_t()> tp(4);
	for(int i(0);i!=tp.count();++i)
		tp.add([&,i]{
			using namespace std;
			const auto sec(get());
			this_thread::sleep_for(chrono::seconds(sec));
			lock_guard<mutex> lock(mut);
			cout<<"thread "<<i<<" wait "<<sec<<" sec"<<endl;
			return i;
		;});
	tp.wait(0);	//tp will block here until thread[0] complete
	cout<<tp.get(0)<<" complete"<<endl;	//get the return value from lambda
	//tp.get(0);	//do not call same id twice

	if(tp.valid(1))	//it means thread[1] has a function, and thread[1] is running
		cout<<tp.get(1)<<" complete"<<endl;	//tp will block here until thread[1] complete and return value from lambda
	if(tp.valid(1))	//this will return false, because you call tp.get(1)
		cout<<"hi, something must wrong"<<endl;

	//you don't need to call every get to guarantee all threads are not valid
	//the destructor of CThreadPool_Ret will deal with this
}