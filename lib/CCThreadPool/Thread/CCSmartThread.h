#ifndef __CCSmartThread
#define __CCSmartThread
#include<thread>

namespace nTool
{
	class CSmartThread
	{
		std::thread thr_;
	public:
		CSmartThread();
		template<class Func,class ... Args>
		explicit CSmartThread(Func &&,Args &&...);
		CSmartThread(const CSmartThread &)=delete;
		CSmartThread& operator=(const CSmartThread &)=delete;
		CSmartThread& operator=(CSmartThread &&) noexcept;
		~CSmartThread();
	};
}

#include"CCSmartThreadT.cpp"

#endif