#include"CCThreadPoolCommun.h"
#include"CCThreadPoolItem.h"
#include"Thread/CCThreadQueue.h"

namespace nTool
{
	template<class Func_t>
	void CThreadPoolCommun_Ret<Func_t>::detach_()
	{
		waitingQue_.emplace(id_,item_);
	}

	template<class Func_t>
	CThreadPoolCommun_Ret<Func_t>::CThreadPoolCommun_Ret(CThreadPoolItem<Func_t> *item,CThreadQueue<pair> &waitingQue,const std::size_t id)
		:item_{item},waitingQue_{waitingQue},id_{id}{}
}