#include"CCThreadPoolCommun.h"
#include"CCThreadPoolItem.h"
#include"Thread/CCThreadQueue.h"

namespace nTool
{
	template<class Ret>
	void CThreadPoolCommun_Ret<Ret>::detach_()
	{
		waitingQue_.emplace(id_,item_);
	}

	template<class Ret>
	CThreadPoolCommun_Ret<Ret>::CThreadPoolCommun_Ret(CThreadPoolItem<Ret> *item,CThreadQueue<pair> &waitingQue,const std::size_t id)
		:item_{item},waitingQue_{waitingQue},id_{id}{}
}