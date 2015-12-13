#ifndef __CCThreadPoolItem
#define __CCThreadPoolItem
#include<atomic>	//atomic<bool>
#include<functional>	//function
#include<memory>	//unique_ptr
#include<utility>	//move
#include"CCThreadPoolCommun.h"
#include"./Thread/CCTask.h"
#include"./Thread/CCSemaphore.h"
#include"./Thread/CCSmartThread.h"

namespace nTool
{
	template<class T>
	class CThreadPoolItemExecutorBase;
	template<class T>
	class CThreadPoolItemExecutorDetach;
	template<class T>
	class CThreadPoolItemExecutorJoin;
	template<class T>
	class CThreadPoolItemExecutorRet;

	template<class Func_t>
	class CThreadPoolItem
	{
		std::unique_ptr<ThreadPoolCommunBase<Func_t>> commun_;	//communicate with CThreadPool
		bool destructor_;
		std::unique_ptr<CThreadPoolItemExecutorBase<Func_t>> exec_;
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
		template<class ... Args>
		void assign(Args &&...);
		template<class ... Args>
		void assign_and_detach(Args &&...);
		template<class ... Args>
		void assign_and_ret(Args &&...);
		inline decltype(std::declval<CThreadPoolItemExecutorBase<Func_t>>().get()) get()
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
		void setCommun(std::unique_ptr<ThreadPoolCommunBase<Func_t>> &&commun)
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

	template<class Func_t>
	class CThreadPoolItemExecutorBase
	{
		virtual void exec_()=0;
		virtual bool is_running_() const noexcept=0;
		virtual decltype(std::declval<CTask<Func_t>>().get()) get_()	//detach and join will not call this
		{
			return CTask<Func_t>().get();
		}
		virtual void wait_()=0;
	public:
		inline void exec()
		{
			exec_();
		}
		inline bool is_running() const noexcept
		{
			return is_running_();
		}
		inline decltype(std::declval<CTask<Func_t>>().get()) get()	//detach and join will not call this
		{
			return get_();
		}
		inline void wait()
		{
			wait_();
		}
		virtual ~CThreadPoolItemExecutorBase()=0;
	};

	template<class Func_t>
	class CThreadPoolItemExecutorDetach:public CThreadPoolItemExecutorBase<Func_t>
	{
		ThreadPoolCommunBase<Func_t> *commun_;
		CSemaphore complete_;
		std::function<Func_t> func_;
		void exec_() override;
		bool is_running_() const noexcept override	//only the destructor of CThreadPoolItem will call this
		{
			return !complete_.count();
		}
		void wait_() override	//only the destructor of CThreadPoolItem will call this
		{
			complete_.wait();
		}
	public:
		template<class ... Args>
		CThreadPoolItemExecutorDetach(ThreadPoolCommunBase<Func_t> *,Args &&...);
		CThreadPoolItemExecutorDetach(const CThreadPoolItemExecutorDetach &)=delete;
		CThreadPoolItemExecutorDetach& operator=(const CThreadPoolItemExecutorDetach &)=delete;
	};

	template<class Func_t>
	class CThreadPoolItemExecutorJoin:public CThreadPoolItemExecutorBase<Func_t>
	{
		ThreadPoolCommunBase<Func_t> *commun_;
		CSemaphore complete_;
		std::function<Func_t> func_;
		std::atomic<bool> running_;
		void exec_() override;
		bool is_running_() const noexcept override
		{
			return running_;
		}
		void wait_() override;
	public:
		template<class ... Args>
		CThreadPoolItemExecutorJoin(ThreadPoolCommunBase<Func_t> *,Args &&...);
		CThreadPoolItemExecutorJoin(const CThreadPoolItemExecutorJoin &)=delete;
		CThreadPoolItemExecutorJoin& operator=(const CThreadPoolItemExecutorJoin &)=delete;
	};

	template<class Func_t>
	class CThreadPoolItemExecutorRet:public CThreadPoolItemExecutorBase<Func_t>
	{
		ThreadPoolCommunBase<Func_t> *commun_;
		CTask<Func_t> task_;
		void exec_() override
		{
			task_();
		}
		decltype(std::declval<CTask<Func_t>>().get()) get_() override;
		bool is_running_() const noexcept override
		{
			return task_.valid();
		}
		void wait_() override
		{
			task_.wait();
		}
	public:
		template<class ... Args>
		CThreadPoolItemExecutorRet(ThreadPoolCommunBase<Func_t> *,Args &&...);
		CThreadPoolItemExecutorRet(const CThreadPoolItemExecutorRet &)=delete;
		CThreadPoolItemExecutorRet& operator=(const CThreadPoolItemExecutorRet &)=delete;
	};
}

#include"CCThreadPoolItemT.cpp"

#endif