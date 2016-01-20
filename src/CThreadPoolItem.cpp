#include"../header/CThreadPoolItem.h"
#include<utility>	//move
#include"../../lib/header/thread/CSmartThread.h"
using namespace std;

namespace nThread
{
	struct CThreadPoolItem::Impl
	{
		unique_ptr<CThreadPoolCommunBase> commun;	//communicate with CThreadPool
		bool destructor;
		unique_ptr<IThreadPoolItemExecutorBase> exec;
		CSemaphore wait;
		CSmartThread thr;	//first destroying, no other data member could put under this one
		Impl();
		void assign(function<void()> &&);
		void assign_and_detach(function<void()> &&);
		void loop();
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
			exec->wait();
		destructor=true;
		wake();
	}

	CThreadPoolItem::CThreadPoolItem()
		:impl_{}{}

	void CThreadPoolItem::assign(function<void()> &&func)
	{
		impl_.get().assign(move(func));
	}

	void CThreadPoolItem::assign_and_detach(function<void()> &&func)
	{
		impl_.get().assign_and_detach(move(func));
	}

	void CThreadPoolItem::join()
	{
		impl_.get().exec->wait();
	}

	bool CThreadPoolItem::joinable() const noexcept
	{
		return impl_.get().exec->joinable();
	}

	void CThreadPoolItem::setCommun(unique_ptr<CThreadPoolCommunBase> &&commun)
	{
		impl_.get().commun=move(commun);
	}

	CThreadPoolItem::~CThreadPoolItem(){}

	IThreadPoolItemExecutorBase::~IThreadPoolItemExecutorBase(){}

	void CThreadPoolItemExecutorDetach::exec()
	{
		func_();
		complete_.signal();
		commun_->communPoolDetach();
	}
	
	void CThreadPoolItemExecutorJoin::exec()
	{
		func_();
		commun_->communPoolFinish();
		complete_.signal();
	}

	void CThreadPoolItemExecutorJoin::wait()
	{
		complete_.wait();
		running_=false;
		commun_->communPoolJoin();
	}

	CThreadPoolItemExecutorDetach::CThreadPoolItemExecutorDetach(CThreadPoolCommunBase *commun,function<void()> &&func)
		:commun_{commun},complete_{0},func_{move(func)}{}

	CThreadPoolItemExecutorJoin::CThreadPoolItemExecutorJoin(CThreadPoolCommunBase *commun,function<void()> &&func)
		:commun_{commun},complete_{0},func_{move(func)},running_{true}{}
}