#include"../header/CThreadPoolCommun.hpp"
#include"../../lib/header/thread/CWait_bounded_queue.hpp"
using namespace std;

namespace nThread
{
	CThreadPoolCommunDetach::CThreadPoolCommunDetach(CThreadPoolItem *item,CWait_bounded_queue<CThreadPoolItem*> *waiting_queue) noexcept
		:item_{item},waiting_queue_{waiting_queue}{}

	void CThreadPoolCommunDetach::func_is_completed()
	{
		waiting_queue_->emplace_and_notify(item_);
	}

	CThreadPoolCommunJoin::CThreadPoolCommunJoin(CThreadPoolItem *item,CWait_bounded_queue<CThreadPoolItem*> *waiting_queue) noexcept
		:item_{item},waiting_queue_{waiting_queue}{}

	void CThreadPoolCommunJoin::destroy()
	{
		waiting_queue_->emplace_and_notify(item_);
	}
}