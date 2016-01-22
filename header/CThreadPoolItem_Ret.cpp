#include"CThreadPoolItem_Ret.h"
#include<functional>	//bind
#include<utility>	//forward

namespace nThread
{
	template<class Ret>
	template<class Func,class ... Args>
	void CThreadPoolItem_Ret<Ret>::assign(Func &&func,Args &&...args)
	{
		exec_=std::make_unique<CThreadPoolItemExecutor_Ret<Ret>>(commun_,std::forward<Func>(func),std::forward<Args>(args)...);
		exec(std::bind(&IThreadPoolItemExecutorBase::exec,exec_.get()));
	}

	template<class Ret>
	CThreadPoolItem_Ret<Ret>::~CThreadPoolItem_Ret()
	{
		if(exec_&&is_running())
			wait();
	}
}