#include"../header/IThreadPoolItemBase.hpp"
#include<future>
#include<utility>	//forward, move
#include"../../lib/header/thread/CSemaphore.hpp"
using namespace std;

namespace nThread
{
	struct IThreadPoolItemBase::Impl
	{
		static IThreadPoolItemBase::id class_id;
		bool alive;
		CSemaphore wait;	//to wake up thr
		future<void> fut;	//must destroying before alive and wait
		const IThreadPoolItemBase::id id;
		function<void()> func;
		Impl();
		template<class FuncFwdRef>
		void exec(FuncFwdRef &&val)
		{
			func=forward<decltype(val)>(val);
			wake();
		}
		inline void wake()
		{
			wait.signal();
		}
		~Impl();
	};

	IThreadPoolItemBase::Impl::Impl()
		:alive{true},fut{async(launch::async,[this]{
			while(wait.wait(),alive)
				func();
		})},id{class_id++}{}

	IThreadPoolItemBase::Impl::~Impl()
	{
		alive=false;
		wake();
	}

	IThreadPoolItemBase::IThreadPoolItemBase()=default;

	IThreadPoolItemBase::IThreadPoolItemBase(IThreadPoolItemBase &&val) noexcept=default;

	IThreadPoolItemBase::id IThreadPoolItemBase::get_id() const noexcept
	{
		return impl_->id;
	}

	void IThreadPoolItemBase::exec_(const function<void()> &val)
	{
		impl_->exec(val);
	}

	void IThreadPoolItemBase::exec_(function<void()> &&val)
	{
		impl_->exec(move(val));
	}

	IThreadPoolItemBase& IThreadPoolItemBase::operator=(IThreadPoolItemBase &&) noexcept=default;

	IThreadPoolItemBase::~IThreadPoolItemBase()=default;

	IThreadPoolItemBase::id IThreadPoolItemBase::Impl::class_id{0};
}