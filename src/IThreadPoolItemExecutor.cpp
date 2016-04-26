#include"../header/IThreadPoolItemExecutor.hpp"
#include<atomic>
#include<exception>
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.hpp"
#include"../header/CThreadPoolCommun.hpp"
using namespace std;

namespace nThread
{
	struct CThreadPoolItemExecutorDetach::Impl
	{
		CThreadPoolCommunDetach commun;
		CSemaphore complete;
		function<void()> func;
		Impl(CThreadPoolCommunDetach &&,function<void()> &&);
		void exec();
	};

	struct CThreadPoolItemExecutorJoin::Impl
	{
		CThreadPoolCommunJoin commun;
		CSemaphore complete;
		exception_ptr except;
		function<void()> func;
		atomic<bool> running;
		Impl(CThreadPoolCommunJoin &&,function<void()> &&);
		void exec();
		void join();
	};

	CThreadPoolItemExecutorDetach::Impl::Impl(CThreadPoolCommunDetach &&commun_,function<void()> &&func_)
		:commun{move(commun_)},func{move(func_)}{}

	void CThreadPoolItemExecutorDetach::Impl::exec()
	{
		try
		{
			func();
		}catch(...){}	//yes, do nothing
		complete.signal();
		commun.func_is_completed();
	}

	CThreadPoolItemExecutorJoin::Impl::Impl(CThreadPoolCommunJoin &&commun_,function<void()> &&func_)
		:commun{move(commun_)},func{move(func_)},running{true}{}

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
		commun.destroy();
		if(except)	//must check
			rethrow_exception(except);
	}

	IThreadPoolItemExecutorBase::~IThreadPoolItemExecutorBase()=default;

	CThreadPoolItemExecutorDetach::CThreadPoolItemExecutorDetach(CThreadPoolCommunDetach &&commun,function<void()> &&func)
		:impl_{move(commun),move(func)}{}

	void CThreadPoolItemExecutorDetach::exec()
	{
		impl_.get().exec();
	}

	bool CThreadPoolItemExecutorDetach::is_running() const noexcept
	{
		return !impl_.get().complete.count();
	}

	void CThreadPoolItemExecutorDetach::wait()
	{
		impl_.get().complete.wait();
	}

	CThreadPoolItemExecutorDetach::~CThreadPoolItemExecutorDetach()=default;

	CThreadPoolItemExecutorJoin::CThreadPoolItemExecutorJoin(CThreadPoolCommunJoin &&commun,function<void()> &&func)
		:impl_{move(commun),move(func)}{}

	void CThreadPoolItemExecutorJoin::exec()
	{
		impl_.get().exec();
	}

	bool CThreadPoolItemExecutorJoin::is_running() const noexcept
	{
		return impl_.get().running;
	}

	void CThreadPoolItemExecutorJoin::wait()
	{
		impl_.get().join();
	}

	CThreadPoolItemExecutorJoin::~CThreadPoolItemExecutorJoin()=default;
}