#include"../header/IThreadPoolItemExecutor.h"
#include<atomic>	//atomic<bool>
#include<utility>
#include"../../lib/header/thread/CSemaphore.h"
#include"../header/CThreadPoolCommun.h"
using namespace std;

namespace nThread
{
	struct CThreadPoolItemExecutorDetach::Impl
	{
		CThreadPoolCommun commun;
		CSemaphore complete;
		function<void()> func;
		Impl(CThreadPoolCommun &&,function<void()> &&);
		void exec();
	};

	struct CThreadPoolItemExecutorJoin::Impl
	{
		CThreadPoolCommun commun;
		CSemaphore complete;
		function<void()> func;
		atomic<bool> running;
		Impl(CThreadPoolCommun &&,function<void()> &&);
		void exec();
		void join();
	};

	CThreadPoolItemExecutorJoin::Impl::Impl(CThreadPoolCommun &&commun_,function<void()> &&func_)
		:commun{move(commun_)},complete{0},func{move(func_)},running{true}{}

	void CThreadPoolItemExecutorJoin::Impl::exec()
	{
		func();
		commun.finish();	//notify join_any
		complete.signal();	//notify join
	}

	void CThreadPoolItemExecutorJoin::Impl::join()
	{
		complete.wait();
		running=false;
		commun.join();
	}

	CThreadPoolItemExecutorDetach::Impl::Impl(CThreadPoolCommun &&commun_,function<void()> &&func_)
		:commun{move(commun_)},complete{0},func{move(func_)}{}

	void CThreadPoolItemExecutorDetach::Impl::exec()
	{
		func();
		complete.signal();
		commun.detach();
	}

	IThreadPoolItemExecutorBase::~IThreadPoolItemExecutorBase(){}

	CThreadPoolItemExecutorDetach::CThreadPoolItemExecutorDetach(CThreadPoolCommun &&commun,function<void()> &&func)
		:impl_{move(commun),move(func)}{}

	void CThreadPoolItemExecutorDetach::exec()
	{
		impl_.get().exec();
	}

	bool CThreadPoolItemExecutorDetach::is_running() const noexcept
	{
		return !impl_.get().complete.count();
	}

	void CThreadPoolItemExecutorDetach::join()
	{
		impl_.get().complete.wait();
	}

	CThreadPoolItemExecutorDetach::~CThreadPoolItemExecutorDetach(){}

	CThreadPoolItemExecutorJoin::CThreadPoolItemExecutorJoin(CThreadPoolCommun &&commun,function<void()> &&func)
		:impl_{move(commun),move(func)}{}

	void CThreadPoolItemExecutorJoin::exec()
	{
		impl_.get().exec();
	}

	bool CThreadPoolItemExecutorJoin::is_running() const noexcept
	{
		return impl_.get().running;
	}

	void CThreadPoolItemExecutorJoin::join()
	{
		impl_.get().join();
	}

	CThreadPoolItemExecutorJoin::~CThreadPoolItemExecutorJoin(){}
}