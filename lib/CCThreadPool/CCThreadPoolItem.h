#ifndef __CCThreadPoolItem
#define __CCThreadPoolItem
#include<memory>	//unique_ptr
#include<utility>	//move
#include"./Thread/CCAsyncExecutor.h"
#include"./Thread/CCSemaphore.h"
#include"./Thread/CCSmartThread.h"
#include"CCThreadPoolCommun.h"

namespace nTool
{
	template<class Func>
	class CThreadPoolItem
	{
		CSemaphore assign_;
		std::unique_ptr<ThreadPoolCommunBase<Func>> commun_;	//communicate with CThreadPool
		bool destructor_;
		CSemaphore detach_;
		CAsyncExecutor<Func> exec_;
		bool joinable_;
		CSemaphore wait_;
		CSmartThread thr_;	//first destroying, no other data member could put under this one
		void finishing_();
		void loop_();
		inline void running_()
		{
			exec_();
		}
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
		inline void assign_and_detach(Args &&...);
		decltype(std::declval<CAsyncExecutor<Func>>().get()) join();	//after calling this, CThreadPoolItem will be pushed into waitingQue_
																		//it also means assign will be called in the subsequent (if has)
		inline bool joinable() const noexcept	//return true after calling assign, return false after calling join
		{
			return joinable_;
		}
		void setCommun(std::unique_ptr<ThreadPoolCommunBase<Func>> &&commun)
		{
			commun_=std::move(commun);
		}
		inline void wait() const
		{
			exec_.wait();
		}
		CThreadPoolItem& operator=(const CThreadPoolItem &)=delete;
		~CThreadPoolItem();
	};
}

#include"CCThreadPoolItemT.cpp"

#endif