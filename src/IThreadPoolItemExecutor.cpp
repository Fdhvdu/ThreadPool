#include"../header/IThreadPoolItemExecutor.h"
#include<atomic>	//atomic<bool>
#include<utility>
#include"../../lib/header/thread/CSemaphore.h"
#include"../header/IThreadPoolCommun.h"
using namespace std;

namespace nThread
{
	struct CThreadPoolItemExecutorDetach::Impl
	{
		unique_ptr<IThreadPoolCommunBase> commun;
		CSemaphore complete;
		function<void()> func;
		Impl(unique_ptr<IThreadPoolCommunBase> &&,function<void()> &&);
		void exec();
	};

	struct CThreadPoolItemExecutorJoin::Impl
	{
		unique_ptr<IThreadPoolCommunBase> commun;
		CSemaphore complete;
		function<void()> func;
		atomic<bool> running;
		Impl(unique_ptr<IThreadPoolCommunBase> &&,function<void()> &&);
		void exec();
		void join();
	};

	CThreadPoolItemExecutorDetach::Impl::Impl(unique_ptr<IThreadPoolCommunBase> &&commun_,function<void()> &&func_)
		:commun{move(commun_)},complete{0},func{move(func_)}{}

	void CThreadPoolItemExecutorDetach::Impl::exec()
	{
		func();
		complete.signal();
		commun->func_is_completed();
	}

	CThreadPoolItemExecutorJoin::Impl::Impl(unique_ptr<IThreadPoolCommunBase> &&commun_,function<void()> &&func_)
		:commun{move(commun_)},complete{0},func{move(func_)},running{true}{}

	void CThreadPoolItemExecutorJoin::Impl::exec()
	{
		func();
		commun->func_is_completed();	//notify CThreadPool::join_any
		complete.signal();	//notify CThreadPool::join
	}

	void CThreadPoolItemExecutorJoin::Impl::join()
	{
		complete.wait();
		running=false;
		commun->destroy();
	}

	IThreadPoolItemExecutorBase::~IThreadPoolItemExecutorBase(){}

	CThreadPoolItemExecutorDetach::CThreadPoolItemExecutorDetach(unique_ptr<IThreadPoolCommunBase> &&commun,function<void()> &&func)
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

	CThreadPoolItemExecutorDetach::~CThreadPoolItemExecutorDetach(){}

	CThreadPoolItemExecutorJoin::CThreadPoolItemExecutorJoin(unique_ptr<IThreadPoolCommunBase> &&commun,function<void()> &&func)
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

	CThreadPoolItemExecutorJoin::~CThreadPoolItemExecutorJoin(){}
}