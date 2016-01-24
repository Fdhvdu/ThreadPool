#include"CThreadPoolItem_Ret.h"
#include<functional>	//bind
#include<utility>	//forward, move

namespace nThread
{
	template<class Ret>
	CThreadPoolItem_Ret<Ret>::CThreadPoolItem_Ret(CThreadQueue<CThreadPoolItem_Ret<Ret>*> *waitingQue)
		:waitingQue_{waitingQue}{}

	template<class Ret>
	template<class Func,class ... Args>
	void CThreadPoolItem_Ret<Ret>::assign(Func &&func,Args &&...args)
	{
		exec_=CTask<Ret>{std::forward<Func>(func),std::forward<Args>(args)...};
		IThreadPoolItemBase::exec_(std::bind(&CTask<Ret>::operator(),&exec_));
	}

	template<class Ret>
	CThreadPoolItem_Ret<Ret>::~CThreadPoolItem_Ret()
	{
		if(is_running())
			wait();
	}
}