#ifndef CTHREADPOOLITEM_RET
#define CTHREADPOOLITEM_RET
#include<memory>	//unique_ptr
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.h"
#include"../../lib/header/thread/CSmartThread.h"
#include"../../lib/header/thread/CTask.h"
#include"CThreadPoolCommun.h"

namespace nThread
{
	template<class T>
	class CThreadPoolItemExecutorRet;

	template<class Ret>
	class CThreadPoolItem_Ret
	{
		std::unique_ptr<CThreadPoolCommunBase> commun_;	//communicate with CThreadPool
		bool destructor_;
		std::unique_ptr<CThreadPoolItemExecutorRet<Ret>> exec_;
		CSemaphore wait_;
		CSmartThread thr_;	//first destroying, no other data member could put under this one
		void loop_();
		inline void waiting_()
		{
			wait_.wait();
		}
		inline void wake_()
		{
			wait_.signal();
		}
	public:
		CThreadPoolItem_Ret();
		CThreadPoolItem_Ret(const CThreadPoolItem_Ret &)=delete;
		template<class Func,class ... Args>
		void assign_and_ret(Func &&,Args &&...);
		inline decltype(std::declval<CThreadPoolItemExecutorRet<Ret>>().get()) get()
		{
			return exec_->get();
		}
		void setCommun(std::unique_ptr<CThreadPoolCommunBase> &&commun)
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
		CThreadPoolItem_Ret& operator=(const CThreadPoolItem_Ret &)=delete;
		~CThreadPoolItem_Ret();
	};

	template<class Ret>
	class CThreadPoolItemExecutorRet
	{
		CThreadPoolCommunBase *commun_;
		CTask<Ret> task_;
	public:
		template<class Func,class ... Args>
		CThreadPoolItemExecutorRet(CThreadPoolCommunBase *,Func &&,Args &&...);
		CThreadPoolItemExecutorRet(const CThreadPoolItemExecutorRet &)=delete;
		void exec()
		{
			task_();
		}
		decltype(std::declval<CTask<Ret>>().get()) get();
		bool is_running() const noexcept
		{
			return task_.valid();
		}
		void wait()
		{
			task_.wait();
		}
		CThreadPoolItemExecutorRet& operator=(const CThreadPoolItemExecutorRet &)=delete;
	};
}

#include"CThreadPoolItem_Ret.cpp"

#endif