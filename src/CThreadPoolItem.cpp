#include"../header/CThreadPoolItem.h"
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.h"
#include"../../lib/header/thread/CSmartThread.h"
#include"../header/IThreadPoolItemExecutor.h"
using namespace std;

namespace nThread
{
	struct CThreadPoolItem::Impl
	{
		bool destructor;
		unique_ptr<IThreadPoolItemExecutorBase> exec;
		CSemaphore wait;
		CSmartThread thr;	//first destroying, no other data member could put under this one
		Impl();
		void assign(unique_ptr<IThreadPoolItemExecutorBase> &&);
		inline bool joinable_and_is_running() const noexcept
		{
			return exec->joinable()&&exec->is_running();
		}
		inline void waiting()
		{
			wait.wait();
		}
		inline void wake()
		{
			wait.signal();
		}
		~Impl();
	};

	CThreadPoolItem::Impl::Impl()
		:destructor{false},wait{0},thr{[&]{
			while(waiting(),!destructor)
				exec->exec();
		}}{}

	void CThreadPoolItem::Impl::assign(unique_ptr<IThreadPoolItemExecutorBase> &&exec_)
	{
		exec=move(exec_);
		wake();
	}

	CThreadPoolItem::Impl::~Impl()
	{
		if(exec&&exec->is_running())
			exec->join();
		destructor=true;
		wake();
	}

	CThreadPoolItem::CThreadPoolItem()
		:impl_{}{}

	CThreadPoolItem::CThreadPoolItem(CThreadPoolItem &&rVal) noexcept
		:impl_{move(rVal.impl_)}{}
	
	void CThreadPoolItem::assign(unique_ptr<IThreadPoolItemExecutorBase> &&exec)
	{
		impl_.get().assign(move(exec));
	}

	thread::id CThreadPoolItem::get_id() const noexcept
	{
		return impl_.get().thr.get_id();
	}

	void CThreadPoolItem::join()
	{
		impl_.get().exec->join();
	}

	bool CThreadPoolItem::joinable() const noexcept
	{
		return impl_.get().joinable_and_is_running();
	}

	CThreadPoolItem& CThreadPoolItem::operator=(CThreadPoolItem &&rVal) noexcept
	{
		impl_=move(rVal.impl_);
		return *this;
	}

	CThreadPoolItem::~CThreadPoolItem(){}
}