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
	template<class Ret>
	class CThreadPool_Ret	//can return value
	{
	public:
		typedef std::thread::id thread_id;
	private:
		CThreadQueue<CThreadPoolItem_Ret<Ret>*> waitingQue_;
		std::unordered_map<thread_id,CThreadPoolItem_Ret<Ret>> thr_;
	public:
		explicit CThreadPool_Ret(std::size_t count)
		{
			while(count--)
			{
				CThreadPoolItem_Ret<Ret> item{&waitingQue_};
				const auto id{item.get_id()};
				thr_.emplace(id,std::move(item));
				waitingQue_.emplace(&thr_.at(id));
			}
		}
		CThreadPool_Ret(const CThreadPool_Ret &)=delete;
		template<class Func,class ... Args>
		thread_id add(Func &&func,Args &&...args)
		{
			auto temp{waitingQue_.wait_and_pop()};
			temp->assign(std::forward<Func>(func),std::forward<Args>(args)...);
			return temp->get_id();
		}
		inline std::size_t available() const noexcept	//how many threads can use now
		{
			return waitingQue_.size();
		}
		inline std::size_t count() const noexcept	//total threads can use
		{
			return thr_.size();
		}
		inline Ret get(const thread_id id)
		{
			return thr_.at(id).get();
		}
		inline bool valid(const thread_id id) const noexcept
		{
			return thr_.at(id).is_running();
		}
		inline void wait(const thread_id id) const	//block until thr_[id] ready
		{
			thr_.at(id).wait();
		}
		void wait_all() const
		{
			for(const auto &val:thr_)
				if(valid(val.first))
					wait(val.first);
		}
		CThreadPool_Ret& operator=(const CThreadPool_Ret &)=delete;
	};
}

#endif