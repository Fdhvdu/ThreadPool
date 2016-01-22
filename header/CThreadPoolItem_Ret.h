#ifndef CTHREADPOOLITEM_RET
#define CTHREADPOOLITEM_RET
#include<memory>	//unique_ptr
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.h"
#include"../../lib/header/thread/CSmartThread.h"
#include"CThreadPoolItemExecutor_Ret.h"
#include"IThreadPoolCommun.h"

namespace nThread
{
	template<class Ret>
	class CThreadPoolItem_Ret
	{
		std::unique_ptr<IThreadPoolCommunBase> commun_;	//communicate with CThreadPool
		bool destructor_;
		std::unique_ptr<CThreadPoolItemExecutor_Ret<Ret>> exec_;
		CSemaphore wait_;
		CSmartThread thr_;	//first destroying, no other data member could put under this one
		void loop_();
		inline void wake_()
		{
			wait_.signal();
		}
	public:
		CThreadPoolItem_Ret();
		template<class Func,class ... Args>
		void assign(Func &&,Args &&...);
		inline Ret get()
		{
			return exec_->get();
		}
		inline std::thread::id get_id() const noexcept
		{
			return thr_.get_id();
		}
		void setCommun(std::unique_ptr<IThreadPoolCommunBase> &&commun)
		{
			commun_=std::move(commun);
		}
		inline bool valid() const noexcept
		{
			return exec_->is_running();
		}
		inline void wait() const	//only for CThreadPool_Ret::wait
		{
			exec_->wait();
		}
		~CThreadPoolItem_Ret();
	};
}

#include"CThreadPoolItem_Ret.cpp"

#endif