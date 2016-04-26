#ifndef CTHREADPOOL_RET
#define CTHREADPOOL_RET
#include<thread>	//thread::hardware_concurrency
#include<type_traits>	//result_of_t
#include<unordered_map>
#include<utility>	//forward, move
#include"../../lib/header/thread/CWait_bounded_queue.hpp"
#include"CThreadPoolItem_Ret.hpp"

namespace nThread
{
	//1. a fixed-sized threadpool
	//2. can return value
	template<class Ret>
	class CThreadPool_Ret
	{
	public:
		using size_type=std::result_of_t<decltype(std::thread::hardware_concurrency)&()>;
		using thread_id=IThreadPoolItemBase::id;
	private:
		CWait_bounded_queue<CThreadPoolItem_Ret<Ret>*> waiting_queue_;
		std::unordered_map<thread_id,CThreadPoolItem_Ret<Ret>> thr_;
	public:
		CThreadPool_Ret()
			:CThreadPool_Ret{std::thread::hardware_concurrency()}{}
		//1. determine the total of usable threads
		//2. the value you pass will always equal to CThreadPool_Ret::size
		explicit CThreadPool_Ret(size_type size)
			:waiting_queue_{size},thr_{size}
		{
			while(size--)
			{
				CThreadPoolItem_Ret<Ret> item{&waiting_queue_};
				const auto id{item.get_id()};
				waiting_queue_.emplace_not_ts(&thr_.emplace(id,std::move(item)).first->second);
			}
		}
		//of course, why do you need to copy or move CThreadPool_Ret?
		CThreadPool_Ret(const CThreadPool_Ret &)=delete;
		//1. block until CThreadPool_Ret::available is not zero and execute the func
		//2. after returning from add, CThreadPool_Ret::available will reduce 1
		//3. after returning from add, CThreadPool_Ret::valid(thread_id) will return true
		//4.
		//you must call CThreadPool_Ret::get after returning from add at some moment
		//otherwise, CThreadPool_Ret::available cannot increase 1
		template<class Func,class ... Args>
		thread_id add(Func &&func,Args &&...args)
		{
			const auto temp{waiting_queue_.wait_and_pop()};
			try
			{
				temp->assign(std::forward<Func>(func),std::forward<Args>(args)...);
			}catch(...)
			{
				waiting_queue_.emplace_and_notify(temp);
				throw ;
			}
			return temp->get_id();
		}
		////1. return the total of usable threads at that moment
		////2. reduce 1 after returning from CThreadPool_Ret::add
		////3. increase 1 after returning from CThreadPool_Ret::get
		////4. non-block
		//inline size_type available() const noexcept
		//{
		//	return static_cast<size_type>(waiting_queue_.size());
		//}
		//1. block until the thread_id completes the func
		//2. after returning from get, CThreadPool_Ret::valid(thread_id) will return false
		//3. if the thread_id is not valid, do not get the thread_id
		inline Ret get(const thread_id id)
		{
			return thr_.at(id).get();
		}
		//1. return the total of usable threads
		//2. is fixed after constructing
		//3. non-block
		inline size_type size() const noexcept
		{
			return static_cast<size_type>(thr_.size());
		}
		//1. return whether the thread_id has been get yet
		//2. return true for the thread_id which was returned by CThreadPool_Ret::add
		//3. return false for the thread_id which was used by CThreadPool_Ret::get
		//4. non-block
		inline bool valid(const thread_id id) const noexcept
		{
			return thr_.at(id).is_running();
		}
		//block until the thread_id completes the func
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
		//get all the threads in destructor
	};
}

#endif
