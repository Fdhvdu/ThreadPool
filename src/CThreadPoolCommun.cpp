#include"../header/CThreadPoolCommun.hpp"
#include"../../lib/header/thread/CThreadForward_list.hpp"
#include"../../lib/header/thread/CThreadQueue.hpp"
#include"../header/CThreadPoolItem.hpp"
using namespace std;

namespace nThread
{
	CThreadPoolCommunDetach::CThreadPoolCommunDetach(CThreadPoolItem *item,CThreadQueue<CThreadPoolItem*> *waitingQue)
		:item_{item},waitingQue_{waitingQue}{}

	void CThreadPoolCommunDetach::func_is_completed()
	{
		waitingQue_->emplace(item_);
	}

	CThreadPoolCommunJoin::CThreadPoolCommunJoin(CThreadPoolItem *item,CThreadForward_list<CThreadPoolItem*> *join_anyList,CThreadQueue<CThreadPoolItem*> *waitingQue)
		:item_{item},join_anyList_{join_anyList},waitingQue_{waitingQue}{}

	void CThreadPoolCommunJoin::destroy()
	{
		join_anyList_->remove_if([this](const CThreadPoolItem *val){return val->get_id()==item_->get_id();});
		//if CThreadPool::join_any run first, this would not erase anything (it's ok)
		waitingQue_->emplace(item_);
	}

	void CThreadPoolCommunJoin::func_is_completed()
	{
		join_anyList_->emplace_front(item_);
	}
}