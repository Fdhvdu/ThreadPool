#include"CThreadPoolItemExecutor_Ret.h"
#include<utility>	//forward, move

namespace nThread
{
	template<class Ret>
	template<class Func,class ... Args>
	CThreadPoolItemExecutor_Ret<Ret>::CThreadPoolItemExecutor_Ret(Func &&func,Args &&...args)
		:task_{std::forward<Func>(func),std::forward<Args>(args)...}{}
}
