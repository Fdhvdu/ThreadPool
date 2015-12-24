#ifndef __CCThreadPoolItem
#define __CCThreadPoolItem
#include<atomic>	//atomic<bool>
#include<functional>	//function
#include<memory>	//unique_ptr
#include<utility>	//move
#include"CCThreadPoolCommun.h"
#include"Thread/CCTask.h"
#include"Thread/CCSemaphore.h"
#include"Thread/CCSmartThread.h"

namespace nTool
{
	template<class T>
	struct IThreadPoolItemExecutorBase;
	template<class T>
	class CThreadPoolItemExecutorRet;

	template<class Ret>
	class CThreadPoolItem
	{
		std::unique_ptr<CThreadPoolCommunBase> commun_;	//communicate with CThreadPool
		bool destructor_;
		std::unique_ptr<IThreadPoolItemExecutorBase<Ret>> exec_;
		bool joinable_;
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
		CThreadPoolItem();
		CThreadPoolItem(const CThreadPoolItem &)=delete;
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
							//after calling this, CThreadPoolItem will be pushed into waitingQue_
							//it also means assign will be called in the subsequent (if has)
		{
			exec_->wait();
		}
		inline bool joinable() const noexcept	//return true after calling assign, return false after calling join
		{
			return joinable_&&exec_->is_running();
		}
		void setCommun(std::unique_ptr<CThreadPoolCommunBase> &&commun)
		{
			commun_=std::move(commun);
		}
		inline bool valid() const noexcept
		{
			return exec_->is_running();
		}
		inline void wait()	//for CThreadPool_Ret::wait
		{
			exec_->wait();
		}
		CThreadPoolItem& operator=(const CThreadPoolItem &)=delete;
		~CThreadPoolItem();
	};

	template<class Ret>
	struct IThreadPoolItemExecutorBase	//I give up to use Non-Virtual Interface Idiom here
										//because this is a abstract base struct
	{
		virtual void exec()=0;
		virtual bool is_running() const noexcept=0;
		virtual decltype(std::declval<CTask<Ret>>().get()) get()	//detach and join will not call this
		{
			return CTask<Ret>().get();
		}
		virtual void wait()=0;
		virtual ~IThreadPoolItemExecutorBase()=0;
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
		bool is_running() const noexcept override	//only the destructor of CThreadPoolItem will call this
		{
			return !complete_.count();
		}
		void wait() override	//only the destructor of CThreadPoolItem will call this
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
	public:
		template<class Func,class ... Args>
		CThreadPoolItemExecutorRet(CThreadPoolCommunBase *,Func &&,Args &&...);
		CThreadPoolItemExecutorRet(const CThreadPoolItemExecutorRet &)=delete;
		void exec() override
		{
			task_();
		}
		decltype(std::declval<CTask<Ret>>().get()) get() override;
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

#include"CCThreadPoolItemT.cpp"

#endif