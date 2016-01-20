#ifndef CTHREADPOOL
#define CTHREADPOOL
#include<cstddef>	//size_t
#include"../../lib/header/thread/CThreadQueue.h"
#include"../../lib/header/tool/CPimpl.h"
#include"CThreadPoolCommun.h"
#include"CThreadPoolItem.h"

namespace nThread
{
	class CThreadPool	//same job, different argument and no return value
						//with add, add_and_detach, join, joinable, join_all and join_any
						//every threads must call join, join_any or join_all after calling add
						//otherwise, there is no available thread even after threads complete their job
	{
		struct Impl;
		mutable CThreadQueue<typename CThreadPoolCommun::pair> waitingQue_;
		nTool::CPimpl<Impl> impl_;
	public:
		explicit CThreadPool(std::size_t);
		CThreadPool(const CThreadPool &)=delete;
		template<class Func,class ... Args>
		std::size_t add(Func &&,Args &&...);
		template<class Func,class ... Args>
		inline void add_and_detach(Func &&func,Args &&...args)
		{
			waitingQue_.wait_and_pop().second->assign_and_detach(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		}
		inline std::size_t available() const noexcept
		{
			return waitingQue_.size();
		}
		std::size_t count() const noexcept;
		void join(std::size_t);	//do not combine join and join_any together in your code
								//it will make some join_any cannot get notification
		bool joinable(std::size_t) const noexcept;
		void join_all();	//it will not block assign, you have to control by yourself
		std::size_t join_any();	//do not combine join and join_any together in your code
								//it will make some join_any cannot get notification
								//join_any must return value, because I have implemented add_and_detach already
		void wait_until_all_available() const;
		CThreadPool& operator=(const CThreadPool &)=delete;
		~CThreadPool();
	};
}

#include"CThreadPool.cpp"

#endif