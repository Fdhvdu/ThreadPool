#include"../header/CThreadPoolCommun.h"
#include"../../lib/header/thread/CThreadList.h"
#include"../../lib/header/thread/CThreadQueue.h"
#include"../header/CThreadPoolItem.h"
using namespace std;

namespace nThread
{
	void CThreadPoolCommunBase::detach_(){}
	
	void CThreadPoolCommunBase::finish_(){}
	
	void CThreadPoolCommunBase::join_(){}

	void CThreadPoolCommunBase::communPoolDetach()
	{
		detach_();
	}

	void CThreadPoolCommunBase::communPoolFinish()
	{
		finish_();
	}

	void CThreadPoolCommunBase::communPoolJoin()
	{
		join_();
	}

	CThreadPoolCommunBase::~CThreadPoolCommunBase(){}

	struct CThreadPoolCommun::Impl
	{
		CThreadPoolItem *item;
		CThreadList<CThreadPoolItem*> &join_anyList;	//or use deque
		CThreadQueue<CThreadPoolItem*> &waitingQue;
		Impl(CThreadPoolItem *,CThreadList<CThreadPoolItem*> &,CThreadQueue<CThreadPoolItem*> &);
		inline void communPoolDetach()
		{
			waitingQue.emplace(item);
		}
		inline void communPoolFinish()
		{
			join_anyList.emplace_back(item);
		}
		void communPoolJoin();
	};

	CThreadPoolCommun::Impl::Impl(CThreadPoolItem *item_,CThreadList<CThreadPoolItem*> &join_anyList_,CThreadQueue<CThreadPoolItem*> &waitingQue_)
		:item{item_},join_anyList{join_anyList_},waitingQue{waitingQue_}{}

	void CThreadPoolCommun::Impl::communPoolJoin()
	{
		join_anyList.remove_if([&](const CThreadPoolItem *val){return val->get_id()==item->get_id();});
		//CThreadPoolItem::communPoolFinishing_ call CThreadPoolCommun::finishing
		//CThreadPoolCommun::finishing notify CThreadPool::join_any
		//if CThreadPool::join_any run first, this would not erase anything
		waitingQue.emplace(item);
	}

	CThreadPoolCommun::CThreadPoolCommun(CThreadPoolItem *item,CThreadList<CThreadPoolItem*> &join_anyList,CThreadQueue<CThreadPoolItem*> &waitingQue)
		:impl_{item,join_anyList,waitingQue}{}

	void CThreadPoolCommun::detach()
	{
		impl_.get().communPoolDetach();
	}

	void CThreadPoolCommun::finish()
	{
		impl_.get().communPoolFinish();
	}

	void CThreadPoolCommun::join()
	{
		impl_.get().communPoolJoin();
	}

	CThreadPoolCommun::~CThreadPoolCommun(){}
}