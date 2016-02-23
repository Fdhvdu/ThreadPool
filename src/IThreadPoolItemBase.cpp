#include"../header/IThreadPoolItemBase.hpp"
#include<utility>	//forward, move
#include"../../lib/header/thread/CSemaphore.hpp"
#include"../../lib/header/thread/CSmartThread.hpp"
using namespace std;

namespace nThread
{
	struct IThreadPoolItemBase::Impl
	{
		bool alive;
		CSemaphore wait;	//to wake up thr
		CSmartThread thr;	//must destroying before alive and wait
		function<void()> func;
		Impl();
		template<class FuncFwdRef>
		void exec(FuncFwdRef &&val)
		{
			func=forward<FuncFwdRef>(val);
			wake();
		}
		inline void wake()
		{
			wait.signal();
		}
		~Impl();
	};

	IThreadPoolItemBase::Impl::Impl()
		:alive{true},thr{[this]{
			while(wait.wait(),alive)
				func();
		}}{}

	IThreadPoolItemBase::Impl::~Impl()
	{
		alive=false;
		wake();
	}

	IThreadPoolItemBase::IThreadPoolItemBase()
		:impl_{}{}

	IThreadPoolItemBase::IThreadPoolItemBase(IThreadPoolItemBase &&xval) noexcept
		:impl_{move(xval.impl_)}{}

	IThreadPoolItemBase::id IThreadPoolItemBase::get_id() const noexcept
	{
		return impl_.get().thr.get_id();
	}

	IThreadPoolItemBase& IThreadPoolItemBase::operator=(IThreadPoolItemBase &&xval) noexcept
	{
		impl_=move(xval.impl_);
		return *this;
	}

	IThreadPoolItemBase::~IThreadPoolItemBase(){}

	void IThreadPoolItemBase::exec_(const function<void()> &val)
	{
		impl_.get().exec(val);
	}

	void IThreadPoolItemBase::exec_(function<void()> &&xval)
	{
		impl_.get().exec(move(xval));
	}
}