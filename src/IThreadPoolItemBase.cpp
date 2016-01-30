#include"../header/IThreadPoolItemBase.hpp"
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.hpp"
#include"../../lib/header/thread/CSmartThread.hpp"
using namespace std;

namespace nThread
{
	struct IThreadPoolItemBase::Impl
	{
		bool destructor;
		CSemaphore wait;	//to wake up thr
		CSmartThread thr;	//must destroying before destructor and wait
		function<void()> func;
		Impl();
		void exec(const function<void()> &);
		void exec(function<void()> &&);
		inline void wake()
		{
			wait.signal();
		}
		~Impl();
	};

	IThreadPoolItemBase::Impl::Impl()
		:destructor{false},wait{0},thr{[this]{
			while(wait.wait(),!destructor)
				func();
		}}{}

	void IThreadPoolItemBase::Impl::exec(const function<void()> &func_)
	{
		func=func_;
		wake();
	}

	void IThreadPoolItemBase::Impl::exec(function<void()> &&func_)
	{
		func=move(func_);
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

	void IThreadPoolItemBase::exec_(const function<void()> &func)
	{
		impl_.get().exec(func);
	}

	void IThreadPoolItemBase::exec_(function<void()> &&func_)
	{
		impl_.get().exec(move(func_));
	}
}