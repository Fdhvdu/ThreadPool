#include"CCSmartThread.h"
#include<utility>

namespace nTool
{
	template<class Func,class ... Args>
	CSmartThread::CSmartThread(Func &&func,Args &&... args)
		:thr_{std::forward<Func>(func),std::forward<Args>(args)...}{}
}