#ifndef CTHREADPOOL_RET
#define CTHREADPOOL_RET
#include<cstddef>	//size_t
#include<thread>	//thread::id
#include<unordered_map>
#include<utility>	//forward, move
#include"../../lib/header/thread/CThreadQueue.hpp"
#include"CThreadPoolItem_Ret.hpp"

namespace nThread
{
	//1. a fixed-sized threadpool
	//2. can return value
	template<class Ret>
	class CThreadPool_Ret
	{
	public:
		typedef std::thread::id thread_id;
	private:
		CThreadQueue<CThreadPoolItem_Ret<Ret>*> waitingQue_;
		std::unordered_map<thread_id,CThreadPoolItem_Ret<Ret>> thr_;
	public:
		//1. determine how many threads you want to use
		//2. the value you pass will always equal to count
		explicit CThreadPool_Ret(std::size_t count)
		{
			while(count--)
			{
				CThreadPoolItem_Ret<Ret> item{&waitingQue_};
				const auto id{item.get_id()};
				waitingQue_.init_emplace(&thr_.emplace(id,std::move(item)).first->second);
			}
		}
		//of course, why do you need to copy or move CThreadPool_Ret?
		CThreadPool_Ret(const CThreadPool_Ret &)=delete;
		//1.
		//execute func if available!=0
		//otherwise, waiting until 0<available and execute
		//2.
		//after calling add, available reduce 1
		//3.
		//you have to call get after calling add
		//otherwise, there is no available threads even after threads complete the job
		template<class Func,class ... Args>
		thread_id add(Func &&func,Args &&...args)
		{
			auto temp{waitingQue_.wait_and_pop()};
			temp->assign(std::forward<Func>(func),std::forward<Args>(args)...);
			return temp->get_id();
		}
		//1. return how many threads can be used now
		//2. reduce 1 after calling add or add_and_detach
		inline std::size_t available() const noexcept
		{
			return waitingQue_.size();
		}
		//1. return total threads can be used
		//2. the count is fixed after constructing
		inline std::size_t count() const noexcept
		{
			return thr_.size();
		}
		//1. get thr_[id] return value
		//2. after calling this, thr_[id] is not ready
		inline Ret get(const thread_id id)
		{
			return thr_.at(id).get();
		}
		//1. check whether thr_[id] is ready
		//2. after calling add, the id return by add, will make thr_[id] ready
		inline bool valid(const thread_id id) const noexcept
		{
			return thr_.at(id).is_running();
		}
		//1. block until thr_[id] ready
		//2. before calling this, thr_[id] should be already ready
		inline void wait(const thread_id id) const
		{
			thr_.at(id).wait();
		}
		void wait_all() const
		{
			for(const auto &val:thr_)
				if(valid(val.first))
					wait(val.first);
		}
		//of course, why do you need to copy or move CThreadPool_Ret?
		CThreadPool_Ret& operator=(const CThreadPool_Ret &)=delete;
		
		//don't worry, the desturctor will wait all threads completing the job
	};
}

#endif