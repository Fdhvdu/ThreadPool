#include"../header/IThreadPoolCommun.h"
#include"../../lib/header/thread/CThreadList.h"
#include"../../lib/header/thread/CThreadQueue.h"
#include"../header/IThreadPoolItem.h"
using namespace std;

namespace nThread
{
	IThreadPoolCommunBase::~IThreadPoolCommunBase(){}

	CThreadPoolCommunDetach::CThreadPoolCommunDetach(CThreadPoolItem *item,CThreadQueue<CThreadPoolItem*> &waitingQue)
		:item_{item},waitingQue_{waitingQue}{}

	void CThreadPoolCommunDetach::destroy()
	{
		waitingQue_.emplace(item_);
	}

	void CThreadPoolCommunDetach::func_is_completed()
	{
		destroy();
	}

	CThreadPoolCommunJoin::CThreadPoolCommunJoin(CThreadPoolItem *item,CThreadList<CThreadPoolItem*> &join_anyList,CThreadQueue<CThreadPoolItem*> &waitingQue)
		:item_{item},join_anyList_{join_anyList},waitingQue_{waitingQue}{}

	void CThreadPoolCommunJoin::destroy()
	{
		join_anyList_.remove_if([=](const CThreadPoolItem *val){return val->get_id()==item_->get_id();});
		//if CThreadPool::join_any run first, this would not erase anything (it's ok)
		waitingQue_.emplace(item_);
	}

	void CThreadPoolCommunJoin::func_is_completed()
	{
		join_anyList_.emplace_back(item_);
	}
}