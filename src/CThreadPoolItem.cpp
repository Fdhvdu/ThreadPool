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
		inline void wake()
		{
			wait.signal();
		}
		~Impl();
	};

	CThreadPoolItem::Impl::Impl()
		:destructor{false},wait{0},thr{[&]{
			while(wait.wait(),!destructor)
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
			exec->wait();
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

	bool CThreadPoolItem::is_running() const noexcept
	{
		return impl_.get().exec->is_running();
	}

	void CThreadPoolItem::wait()
	{
		impl_.get().exec->wait();
	}

	bool CThreadPoolItem::joinable() const noexcept
	{
		const auto p{dynamic_cast<CThreadPoolItemExecutorJoin*>(impl_.get().exec.get())};
		if(p)
			return p->is_running();
		return false;
	}

	CThreadPoolItem& CThreadPoolItem::operator=(CThreadPoolItem &&rVal) noexcept
	{
		impl_=move(rVal.impl_);
		return *this;
	}

	CThreadPoolItem::~CThreadPoolItem(){}
}