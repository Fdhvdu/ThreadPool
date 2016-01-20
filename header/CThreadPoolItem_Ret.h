#ifndef CTHREADPOOLITEM_RET
#define CTHREADPOOLITEM_RET
#include<atomic>	//atomic<bool>
#include<functional>	//function
#include<memory>	//unique_ptr
#include<utility>	//move
#include"../../lib/header/thread/CSemaphore.h"
#include"../../lib/header/thread/CSmartThread.h"
#include"../../lib/header/thread/CTask.h"
#include"CThreadPoolCommun.h"

namespace nThread
{
	template<class T>
	struct IThreadPoolItemExecutorBase;
	template<class T>
	class CThreadPoolItemExecutorRet;

	template<class Ret>
	class CThreadPoolItem_Ret
	{
		std::unique_ptr<CThreadPoolCommunBase> commun_;	//communicate with CThreadPool
		bool destructor_;
		std::unique_ptr<IThreadPoolItemExecutorBase<Ret>> exec_;
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
		void assign(Func &&,Args &&...);
		template<class Func,class ... Args>
		void assign_and_detach(Func &&,Args &&...);
		template<class Func,class ... Args>
		void assign_and_ret(Func &&,Args &&...);
		inline decltype(std::declval<IThreadPoolItemExecutorBase<Ret>>().get()) get()
		{
			return exec_->get();
		}
		inline void join()	//for CThreadPool::join
							//after calling this, CThreadPoolItem_Ret will be pushed into waitingQue_
							//it also means assign will be called in the subsequent (if has)
		{
			exec_->wait();
		}
		inline bool joinable() const noexcept	//return true after calling assign, return false after calling join
		{
			return exec_->joinable();
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
	struct IThreadPoolItemExecutorBase	//I give up to use Non-Virtual Interface Idiom here
										//because this is a abstract base struct
	{
		virtual void exec()=0;
		virtual bool is_running() const noexcept=0;
		decltype(std::declval<CTask<Ret>>().get()) get()	//detach and join will not call this
		{
			return get_();
		}
		bool joinable() const noexcept
		{
			return joinable_();
		}
		virtual void wait()=0;
		virtual ~IThreadPoolItemExecutorBase()=0;
	protected:
		virtual decltype(std::declval<CTask<Ret>>().get()) get_()	//detach and join will not call this
		{
			return CTask<Ret>().get();
		}
		virtual bool joinable_() const noexcept
		{
			return false;
		}
	};

	class CThreadPoolItemExecutorDetach:public IThreadPoolItemExecutorBase<void>
	{
		CThreadPoolCommunBase *commun_;
		CSemaphore complete_;
		std::function<void()> func_;
	public:
		template<class Func,class ... Args>
		CThreadPoolItemExecutorDetach(CThreadPoolCommunBase *,Func &&,Args &&...);
		CThreadPoolItemExecutorDetach(const CThreadPoolItemExecutorDetach &)=delete;
		void exec() override;
		bool is_running() const noexcept override	//only the destructor of CThreadPoolItem_Ret will call this
		{
			return !complete_.count();
		}
		void wait() override	//only the destructor of CThreadPoolItem_Ret will call this
		{
			complete_.wait();
		}
		CThreadPoolItemExecutorDetach& operator=(const CThreadPoolItemExecutorDetach &)=delete;
	};

	class CThreadPoolItemExecutorJoin:public IThreadPoolItemExecutorBase<void>
	{
		CThreadPoolCommunBase *commun_;
		CSemaphore complete_;
		std::function<void()> func_;
		std::atomic<bool> running_;
	protected:
		bool joinable_() const noexcept override
		{
			return true;
		}
	public:
		template<class Func,class ... Args>
		CThreadPoolItemExecutorJoin(CThreadPoolCommunBase *,Func &&,Args &&...);
		CThreadPoolItemExecutorJoin(const CThreadPoolItemExecutorJoin &)=delete;
		void exec() override;
		bool is_running() const noexcept override
		{
			return running_;
		}
		void wait() override;
		CThreadPoolItemExecutorJoin& operator=(const CThreadPoolItemExecutorJoin &)=delete;
	};

	template<class Ret>
	class CThreadPoolItemExecutorRet:public IThreadPoolItemExecutorBase<Ret>
	{
		CThreadPoolCommunBase *commun_;
		CTask<Ret> task_;
	protected:
		decltype(std::declval<CTask<Ret>>().get()) get_() override;
	public:
		template<class Func,class ... Args>
		CThreadPoolItemExecutorRet(CThreadPoolCommunBase *,Func &&,Args &&...);
		CThreadPoolItemExecutorRet(const CThreadPoolItemExecutorRet &)=delete;
		void exec() override
		{
			task_();
		}
		bool is_running() const noexcept override
		{
			return task_.valid();
		}
		void wait() override
		{
			task_.wait();
		}
		CThreadPoolItemExecutorRet& operator=(const CThreadPoolItemExecutorRet &)=delete;
	};
}

#include"CThreadPoolItem_Ret.cpp"

#endif