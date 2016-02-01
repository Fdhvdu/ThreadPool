#include"../header/CThreadPoolCommun.hpp"
#include"../../lib/header/thread/CThreadForward_list.hpp"
#include"../../lib/header/thread/CThreadRingBuf.hpp"
#include"../header/CThreadPoolItem.hpp"
using namespace std;

namespace nThread
{
	CThreadPoolCommunDetach::CThreadPoolCommunDetach(CThreadPoolItem *item,CThreadRingBuf<CThreadPoolItem*> *waiting_buf)
		:item_{item},waiting_buf_{waiting_buf}{}

	void CThreadPoolCommunDetach::func_is_completed()
	{
		waiting_buf_->write(item_);
	}

	CThreadPoolCommunJoin::CThreadPoolCommunJoin(CThreadPoolItem *item,CThreadForward_list<CThreadPoolItem*> *join_anyList,CThreadRingBuf<CThreadPoolItem*> *waiting_buf)
		:item_{item},join_anyList_{join_anyList},waiting_buf_{waiting_buf}{}

	void CThreadPoolCommunJoin::destroy()
	{
		join_anyList_->remove_if([this](const CThreadPoolItem *val){return val->get_id()==item_->get_id();});
		//if CThreadPool::join_any run first, this would not erase anything (it's ok)
		waiting_buf_->write(item_);
	}

	void CThreadPoolCommunJoin::func_is_completed()
	{
		join_anyList_->emplace_front(item_);
	}
}