#include"../header/CThreadPoolCommun.h"
#include<utility>	//move
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
		CThreadList<CThreadPoolItem*> *join_anyList;	//or use deque
		CThreadQueue<CThreadPoolItem*> *waitingQue;
		Impl(CThreadPoolItem *,CThreadList<CThreadPoolItem*> *,CThreadQueue<CThreadPoolItem*> *);
		inline void detach()
		{
			waitingQue->emplace(item);
		}
		inline void finish()
		{
			join_anyList->emplace_back(item);
		}
		void join();
	};

	CThreadPoolCommun::Impl::Impl(CThreadPoolItem *item_,CThreadList<CThreadPoolItem*> *join_anyList_,CThreadQueue<CThreadPoolItem*> *waitingQue_)
		:item{item_},join_anyList{join_anyList_},waitingQue{waitingQue_}{}

	void CThreadPoolCommun::Impl::join()
	{
		join_anyList->remove_if([&](const CThreadPoolItem *val){return val->get_id()==item->get_id();});
		//CThreadPoolItem::communPoolFinishing_ call CThreadPoolCommun::finishing
		//CThreadPoolCommun::finishing notify CThreadPool::join_any
		//if CThreadPool::join_any run first, this would not erase anything
		waitingQue->emplace(item);
	}

	CThreadPoolCommun::CThreadPoolCommun(CThreadPoolItem *item,CThreadList<CThreadPoolItem*> *join_anyList,CThreadQueue<CThreadPoolItem*> *waitingQue)
		:impl_{item,join_anyList,waitingQue}{}

	CThreadPoolCommun::CThreadPoolCommun(CThreadPoolCommun &&rVal) noexcept
		:impl_{move(rVal.impl_)}{}

	void CThreadPoolCommun::detach()
	{
		impl_.get().detach();
	}

	void CThreadPoolCommun::finish()
	{
		impl_.get().finish();
	}

	void CThreadPoolCommun::join()
	{
		impl_.get().join();
	}

	CThreadPoolCommun& CThreadPoolCommun::operator=(CThreadPoolCommun &&rVal) noexcept
	{
		impl_=move(rVal.impl_);
		return *this;
	}

	CThreadPoolCommun::~CThreadPoolCommun(){}
}