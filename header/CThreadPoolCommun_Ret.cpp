#include"CThreadPoolCommun_Ret.h"
#include"CThreadPoolItem_Ret.h"

namespace nThread
{
	template<class Ret>
	CThreadPoolCommun_Ret<Ret>::CThreadPoolCommun_Ret(CThreadPoolItem_Ret<Ret> *item,CThreadQueue<CThreadPoolItem_Ret<Ret>*> &waitingQue)
		:item_{item},waitingQue_{waitingQue}{}

	template<class Ret>
	void CThreadPoolCommun_Ret<Ret>::destroy()
	{
		waitingQue_.emplace(item_);
	}
}