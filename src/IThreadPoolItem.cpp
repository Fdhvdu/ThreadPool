#include"../header/IThreadPoolItem.h"
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.h"
#include"../../lib/header/thread/CSmartThread.h"
#include"../header/IThreadPoolItemExecutor.h"
using namespace std;

namespace nThread
{
	struct IThreadPoolItemBase::Impl
	{
		bool destructor;
		function<void()> func;
		CSemaphore wait;
		CSmartThread thr;	//first destroying, no other data member could put under this one
		Impl();
		void exec(const function<void()> &);
		inline void wake()
		{
			wait.signal();
		}
		~Impl();
	};

	IThreadPoolItemBase::Impl::Impl()
		:destructor{false},wait{0},thr{[&]{
			while(wait.wait(),!destructor)
				func();
		}}{}

	void IThreadPoolItemBase::Impl::exec(const function<void()> &func_)
	{
		func=func_;
		wake();
	}

	IThreadPoolItemBase::Impl::~Impl()
	{
		destructor=true;
		wake();
	}

	IThreadPoolItemBase::IThreadPoolItemBase()
		:impl_{}{}

	IThreadPoolItemBase::IThreadPoolItemBase(IThreadPoolItemBase &&rVal) noexcept
		:impl_{move(rVal.impl_)}{}

	void IThreadPoolItemBase::exec(const function<void()> &func)
	{
		impl_.get().exec(func);
	}
	
	thread::id IThreadPoolItemBase::get_id() const noexcept
	{
		return impl_.get().thr.get_id();
	}

	IThreadPoolItemBase& IThreadPoolItemBase::operator=(IThreadPoolItemBase &&rVal) noexcept
	{
		impl_=move(rVal.impl_);
		return *this;
	}

	IThreadPoolItemBase::~IThreadPoolItemBase(){}

	void CThreadPoolItem::assign(unique_ptr<IThreadPoolItemExecutorBase> &&exec)
	{
		exec_=move(exec);
		IThreadPoolItemBase::exec(bind(&IThreadPoolItemExecutorBase::exec,exec_.get()));
	}

	bool CThreadPoolItem::is_running() const noexcept
	{
		return exec_->is_running();
	}

	void CThreadPoolItem::wait()
	{
		exec_->wait();
	}

	CThreadPoolItem::~CThreadPoolItem()
	{
		if(exec_&&is_running())
			wait();
	}
}