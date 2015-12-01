#include"CCThreadPoolCommun.h"
#include"./Thread/CCThreadList.h"
#include"CCThreadPoolItem.h"
#include"./Thread/CCThreadQueue.h"

namespace nTool
{
	template<class Func>
	ThreadPoolCommunBase<Func>::ThreadPoolCommunBase(){}

	template<class Func>
	void ThreadPoolCommunBase<Func>::communPoolFinish(){}

	template<class Func>
	void ThreadPoolCommunBase<Func>::communPoolDetach(){}

	template<class Func>
	void ThreadPoolCommunBase<Func>::communPoolJoin(){}

	template<class Func>
	ThreadPoolCommunBase<Func>::~ThreadPoolCommunBase(){}

	template<class Func>
	CThreadPoolCommun<Func>::CThreadPoolCommun(CThreadPoolItem<Func> *item,CThreadList<pair> &join_anyList,CThreadQueue<pair> &waitingQue,const std::size_t &id)
		:item_(item),join_anyList_(join_anyList),waitingQue_(waitingQue),id_(id){}

	template<class Func>
	void CThreadPoolCommun<Func>::communPoolFinish()
	{
		join_anyList_.push_back(pair(id(),item_));
	}

	template<class Func>
	void CThreadPoolCommun<Func>::communPoolDetach()
	{
		waitingQue_.push(pair(id(),item_));
	}

	template<class Func>
	void CThreadPoolCommun<Func>::communPoolJoin()
	{
		join_anyList_.erase([&](const pair &val){return val.first==id();});	//CThreadPoolItem::communPoolFinishing_ call CThreadPoolCommun::finishing
																			//CThreadPoolCommun::finishing notify CThreadPool::join_any
																			//if CThreadPool::join_any run first, this would not erase anything
		waitingQue_.push(pair(id(),item_));
	}

	template<class Func>
	CThreadPoolCommun_Ret<Func>::CThreadPoolCommun_Ret(CThreadPoolItem<Func> *item,CThreadQueue<pair> &waitingQue,const std::size_t &id)
		:item_(item),waitingQue_(waitingQue),id_(id){}

	template<class Func>
	void CThreadPoolCommun_Ret<Func>::communPoolJoin()
	{
		waitingQue_.push(pair(id(),item_));
	}
}