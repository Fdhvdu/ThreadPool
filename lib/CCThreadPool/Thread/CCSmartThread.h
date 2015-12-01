#ifndef __CCSmartThread
#define __CCSmartThread
#include<thread>

namespace nTool
{
	class CSmartThread
	{
		std::thread thr_;
	public:
		template<class Func,class ... Args>
		explicit CSmartThread(Func &&,Args &&...);
		CSmartThread(const CSmartThread &)=delete;
		CSmartThread& operator=(const CSmartThread &)=delete;
		~CSmartThread();
	};
}

#include"CCSmartThreadT.cpp"

#endif