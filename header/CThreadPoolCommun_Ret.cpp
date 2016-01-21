#include"CThreadPoolCommun_Ret.h"
#include"CThreadPoolItem_Ret.h"

namespace nThread
{
	template<class Ret>
	CThreadPoolCommun_Ret<Ret>::CThreadPoolCommun_Ret(CThreadPoolItem_Ret<Ret> *item,CThreadQueue<pair> &waitingQue,const std::size_t id)
		:item_{item},waitingQue_{waitingQue},id_{id}{}

	template<class Ret>
	void CThreadPoolCommun_Ret<Ret>::destroy()
	{
		waitingQue_.emplace(id_,item_);
	}
}