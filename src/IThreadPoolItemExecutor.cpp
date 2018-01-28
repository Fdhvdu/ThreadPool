#include"../header/IThreadPoolItemExecutor.hpp"
#include<atomic>
#include<exception>
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.hpp"
#include"../../lib/header/thread/CWait_bounded_queue.hpp"
using namespace std;

namespace nThread
{
	struct CThreadPoolItemExecutorDetach::Impl
	{
		CSemaphore complete;
		function<void()> func;
		CThreadPoolItem *item;
		CWait_bounded_queue<CThreadPoolItem*,Do_not_use_pop_if_exist> &waiting_queue;
		Impl(CThreadPoolItem *,CWait_bounded_queue<CThreadPoolItem*,Do_not_use_pop_if_exist> &,function<void()> &&);
		void exec();
	};

	struct CThreadPoolItemExecutorJoin::Impl
	{
		CSemaphore complete;
		exception_ptr except;
		function<void()> func;
		CThreadPoolItem *item;
		atomic<bool> running;
		CWait_bounded_queue<CThreadPoolItem*,Do_not_use_pop_if_exist> &waiting_queue;
		Impl(CThreadPoolItem *,CWait_bounded_queue<CThreadPoolItem*,Do_not_use_pop_if_exist> &,function<void()> &&);
		void exec();
		void join();
	};

	CThreadPoolItemExecutorDetach::Impl::Impl(CThreadPoolItem *item_,CWait_bounded_queue<CThreadPoolItem*,Do_not_use_pop_if_exist> &waiting_queue_,function<void()> &&func_)
		:func{move(func_)},item{item_},waiting_queue{waiting_queue_}{}

	void CThreadPoolItemExecutorDetach::Impl::exec()
	{
		try
		{
			func();
		}catch(...){}	//yes, do nothing
		complete.signal();
		waiting_queue.emplace_and_notify(item);
	}

	CThreadPoolItemExecutorJoin::Impl::Impl(CThreadPoolItem *item_,CWait_bounded_queue<CThreadPoolItem*,Do_not_use_pop_if_exist> &waiting_queue_,function<void()> &&func_)
		:func{move(func_)},item{item_},running{true},waiting_queue{waiting_queue_}{}

	void CThreadPoolItemExecutorJoin::Impl::exec()
	{
		try
		{
			func();
		}catch(...)
		{
			except=current_exception();
		}
		complete.signal();	//notify CThreadPool::join
	}

	void CThreadPoolItemExecutorJoin::Impl::join()
	{
		complete.wait();
		running=false;
		waiting_queue.emplace_and_notify(item);
		if(except)	//must check
			rethrow_exception(except);
	}

	IThreadPoolItemExecutorBase::~IThreadPoolItemExecutorBase()=default;

	CThreadPoolItemExecutorDetach::CThreadPoolItemExecutorDetach(CThreadPoolItem *item,CWait_bounded_queue<CThreadPoolItem*,Do_not_use_pop_if_exist> &waiting_queue,function<void()> &&func)
		:impl_{item,waiting_queue,move(func)}{}

	void CThreadPoolItemExecutorDetach::exec()
	{
		impl_->exec();
	}

	bool CThreadPoolItemExecutorDetach::is_running() const noexcept
	{
		return !impl_->complete.count();
	}

	void CThreadPoolItemExecutorDetach::wait()
	{
		impl_->complete.wait();
	}

	CThreadPoolItemExecutorDetach::~CThreadPoolItemExecutorDetach()=default;

	CThreadPoolItemExecutorJoin::CThreadPoolItemExecutorJoin(CThreadPoolItem *item,CWait_bounded_queue<CThreadPoolItem*,Do_not_use_pop_if_exist> &waiting_queue,function<void()> &&func)
		:impl_{item,waiting_queue,move(func)}{}

	void CThreadPoolItemExecutorJoin::exec()
	{
		impl_->exec();
	}

	bool CThreadPoolItemExecutorJoin::is_running() const noexcept
	{
		return impl_->running;
	}

	void CThreadPoolItemExecutorJoin::wait()
	{
		impl_->join();
	}

	CThreadPoolItemExecutorJoin::~CThreadPoolItemExecutorJoin()=default;
}