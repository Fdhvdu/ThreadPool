#include"CThreadPoolItem_Ret.h"
#include<functional>	//bind
#include<utility>	//move

namespace nThread
{
	template<class Ret>
	CThreadPoolItem_Ret<Ret>::CThreadPoolItem_Ret(CThreadQueue<CThreadPoolItem_Ret<Ret>*> *waitingQue)
		:waitingQue_{waitingQue}{}

	template<class Ret>
	void CThreadPoolItem_Ret<Ret>::assign(std::unique_ptr<CThreadPoolItemExecutor_Ret<Ret>> &&exec)
	{
		exec_=std::move(exec);
		IThreadPoolItemBase::exec(std::bind(&CThreadPoolItemExecutor_Ret<Ret>::exec,exec_.get()));
	}

	template<class Ret>
	CThreadPoolItem_Ret<Ret>::~CThreadPoolItem_Ret()
	{
		if(exec_&&is_running())
			wait();
	}
}