#ifndef __CCThreadPool
#define __CCThreadPool
#include<cstddef>	//size_t
#include"./CCThreadPool/Thread/Tool/CCID.h"
#include"./CCThreadPool/Thread/CCThreadList.h"
#include"./CCThreadPool/CCThreadPoolCommun.h"
#include"./CCThreadPool/CCThreadPoolItem.h"
#include"./CCThreadPool/Thread/CCThreadQueue.h"

namespace nTool
{
	template<class Func>
	class CThreadPool	//same job, different argument and no return value
						//with add, add_and_detach, join, joinable, join_all and join_any
						//every threads must call join, join_any or join_all after calling add
						//otherwise, there is no available thread even after threads complete their job
	{
		CID id_;
		CThreadList<typename CThreadPoolCommun<Func>::pair> join_anyList_;
		CThreadQueue<typename CThreadPoolCommun<Func>::pair> waitingQue_;
		const std::size_t size_;
		CThreadPoolItem<Func> *thr_;
	public:
		explicit CThreadPool(std::size_t);
		CThreadPool(const CThreadPool &)=delete;
		template<class ... Args>
		std::size_t add(Args &&...);
		template<class ... Args>
		inline void add_and_detach(Args &&...args)
		{
			waitingQue_.wait_and_pop().second->assign_and_detach(std::forward<Args>(args)...);
		}
		inline std::size_t available() const noexcept
		{
			return waitingQue_.size();
		}
		inline std::size_t count() const noexcept
		{
			return size_;
		}
		inline void join(const std::size_t id)	//do not combine join and join_any together in your code
												//it will make some join_any cannot get notification
		{
			thr_[id].join();
		}
		inline bool joinable(const std::size_t id) const noexcept
		{
			return thr_[id].joinable();
		}
		void join_all();	//it will not block assign, you have to control by yourself
		std::size_t join_any();	//do not combine join and join_any together in your code
								//it will make some join_any cannot get notification
								//join_any must return value, because I have implemented add_and_detach already
		CThreadPool& operator=(const CThreadPool &)=delete;
		~CThreadPool();
	};
} 

#include"CCThreadPoolT.cpp"

#endif