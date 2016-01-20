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
		CThreadList<CThreadPoolCommun::pair> &join_anyList;	//or use deque
		CThreadQueue<CThreadPoolCommun::pair> &waitingQue;
		const size_t id;
		Impl(CThreadPoolItem *,CThreadList<pair> &,CThreadQueue<pair> &,size_t id);
		inline void communPoolDetach()
		{
			waitingQue.emplace(id,item);
		}
		inline void communPoolFinish()
		{
			join_anyList.emplace_back(id,item);
		}
		void communPoolJoin();
	};

	CThreadPoolCommun::Impl::Impl(CThreadPoolItem *item_,CThreadList<pair> &join_anyList_,CThreadQueue<pair> &waitingQue_,const size_t id_)
		:item{item_},join_anyList{join_anyList_},waitingQue{waitingQue_},id{id_}{}

	void CThreadPoolCommun::Impl::communPoolJoin()
	{
		join_anyList.remove_if([=](const pair &val){return val.first==id;});
		//CThreadPoolItem::communPoolFinishing_ call CThreadPoolCommun::finishing
		//CThreadPoolCommun::finishing notify CThreadPool::join_any
		//if CThreadPool::join_any run first, this would not erase anything
		waitingQue.emplace(id,item);
	}

	CThreadPoolCommun::CThreadPoolCommun(CThreadPoolItem *item,CThreadList<pair> &join_anyList,CThreadQueue<pair> &waitingQue,const size_t id)
		:impl_{item,join_anyList,waitingQue,id}{}

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