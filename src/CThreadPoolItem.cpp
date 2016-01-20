#include"../header/CThreadPoolItem.h"
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.h"
#include"../../lib/header/thread/CSmartThread.h"
#include"../header/CThreadPoolCommun.h"
#include"../header/IThreadPoolItemExecutor.h"
using namespace std;

namespace nThread
{
	struct CThreadPoolItem::Impl
	{
		unique_ptr<CThreadPoolCommun> commun;	//communicate with CThreadPool
		bool destructor;
		unique_ptr<IThreadPoolItemExecutorBase> exec;
		CSemaphore wait;
		CSmartThread thr;	//first destroying, no other data member could put under this one
		Impl();
		void assign(function<void()> &&);
		void assign_and_detach(function<void()> &&);
		void loop();
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
		:destructor{false},wait{0},thr{&CThreadPoolItem::Impl::loop,this}{}

	void CThreadPoolItem::Impl::assign(function<void()> &&func)
	{
		exec=make_unique<CThreadPoolItemExecutorJoin>(commun.get(),move(func));
		wake();
	}

	void CThreadPoolItem::Impl::assign_and_detach(function<void()> &&func)
	{
		exec=make_unique<CThreadPoolItemExecutorDetach>(commun.get(),move(func));
		wake();
	}

	void CThreadPoolItem::Impl::loop()
	{
		while(waiting(),!destructor)
			exec->exec();
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

	void CThreadPoolItem::assign(function<void()> &&func)
	{
		impl_.get().assign(move(func));
	}

	void CThreadPoolItem::assign_and_detach(function<void()> &&func)
	{
		impl_.get().assign_and_detach(move(func));
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

	void CThreadPoolItem::setCommun(unique_ptr<CThreadPoolCommun> &&commun)
	{
		impl_.get().commun=move(commun);
	}

	CThreadPoolItem& CThreadPoolItem::operator=(CThreadPoolItem &&rVal) noexcept
	{
		impl_=move(rVal.impl_);
		return *this;
	}

	CThreadPoolItem::~CThreadPoolItem(){}
}