#include"../header/IThreadPoolItemExecutor.h"
#include<utility>
#include"../../lib/header/thread/CSemaphore.h"
#include"../header/IThreadPoolCommun.h"
using namespace std;

namespace nThread
{
	struct CThreadPoolItemExecutor::Impl
	{
		unique_ptr<IThreadPoolCommunBase> commun;
		CSemaphore complete;
		function<void()> func;
		Impl(unique_ptr<IThreadPoolCommunBase> &&,function<void()> &&);
		void exec();
		void wait();
	};

	CThreadPoolItemExecutor::Impl::Impl(unique_ptr<IThreadPoolCommunBase> &&commun_,function<void()> &&func_)
		:commun{move(commun_)},complete{0},func{move(func_)}{}

	void CThreadPoolItemExecutor::Impl::exec()
	{
		func();
		complete.signal();
		commun->func_is_completed();
	}

	void CThreadPoolItemExecutor::Impl::wait()
	{
		complete.wait();
		commun->destroy();
	}

	IThreadPoolItemExecutorBase::~IThreadPoolItemExecutorBase(){}

	CThreadPoolItemExecutor::CThreadPoolItemExecutor(unique_ptr<IThreadPoolCommunBase> &&commun,function<void()> &&func)
		:impl_{move(commun),move(func)}{}

	void CThreadPoolItemExecutor::exec()
	{
		impl_.get().exec();
	}
	
	bool CThreadPoolItemExecutor::is_running() const noexcept
	{
		return !impl_.get().complete.count();
	}

	void CThreadPoolItemExecutor::wait()
	{
		impl_.get().wait();
	}

	CThreadPoolItemExecutor::~CThreadPoolItemExecutor(){}
}