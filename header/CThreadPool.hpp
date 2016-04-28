#ifndef CTHREADPOOL
#define CTHREADPOOL
#include<functional>	//function
#include<thread>	//thread::hardware_concurrency
#include<type_traits>	//result_of_t
#include<utility>	//forward
#include"../../lib/header/tool/CPimpl.hpp"
#include"IThreadPoolItemBase.hpp"

namespace nThread
{
	//1. a fixed-sized threadpool
	//2. cannot return value
	class CThreadPool
	{
	public:
		using size_type=std::result_of_t<decltype(std::thread::hardware_concurrency)&()>;
		using thread_id=IThreadPoolItemBase::id;
	private:
		struct Impl;
		nTool::CPimpl<Impl> impl_;
		thread_id add_(std::function<void()> &&);
		void add_and_detach_(std::function<void()> &&);
	public:
		//CThreadPool::CThreadPool()
		//	:CThreadPool(std::thread::hardware_concurrency()){}
		CThreadPool();
		//1. determine the total of usable threads
		//2. the value you pass will always equal to CThreadPool::size
		explicit CThreadPool(size_type);
		//of course, why do you need to copy or move CThreadPool?
		CThreadPool(const CThreadPool &)=delete;
		//1. block until CThreadPool::empty is false and execute the func
		//2. after returning from add, CThreadPool::joinable(thread_id) will return true
		//3. after returning from add, usable threads will reduce 1
		//4. you must call CThreadPool::join or CThreadPool::join_all after returning from add
		template<class Func,class ... Args>
		inline thread_id add(Func &&func,Args &&...args)
		{
			return add_([&]() noexcept(noexcept(std::forward<decltype(func)>(func)(std::forward<decltype(args)>(args)...))){
				std::forward<decltype(func)>(func)(std::forward<decltype(args)>(args)...);
			});
		}
		//1. block until CThreadPool::empty is false and execute the func
		//2. after the func is completed, usable threads will increase 1
		template<class Func,class ... Args>
		inline void add_and_detach(Func &&func,Args &&...args)
		{
			add_and_detach_([&]() noexcept(noexcept(std::forward<decltype(func)>(func)(std::forward<decltype(args)>(args)...))){
				std::forward<decltype(func)>(func)(std::forward<decltype(args)>(args)...);
			});
		}
		//1. return true if there does not have usable threads at that moment
		//2. return false if there has usable threads at that moment
		//3. non-block
		bool empty() const noexcept;
		//1. block until the thread_id completes the func
		//2. after returning from join, CThreadPool::joinable(thread_id) will return false
		//3. if the thread_id is not joinable, do not join the thread_id
		void join(thread_id);
		//1.
		//for(all the threads)
		//	if(joinable(the thread))
		//		join(the thread);
		//2. will block join_all
		void join_all();
		//1. return whether the thread_id has been join yet
		//2. return true for the thread_id which was returned by CThreadPool::add
		//3. return false for the thread_id which was used by CThreadPool::join
		//4. return false for the thread_id which was used by CThreadPool::add_and_detach
		//5. non-block
		bool joinable(thread_id) const;
		//1. return the total of usable threads
		//2. is fixed after constructing
		//3. non-block
		size_type size() const noexcept;
		//1. block until usable threads equal to CThreadPool::size
		//2. if no any threads block inside CThreadPool::add and CThreadPool::add_and_detach during the execution of wait_until_all_usable, it guarantees usable threads equals to CThreadPool::size at the moment of returning from wait_until_all_usable
		//3. will block wait_until_all_usable
		void wait_until_all_usable() const;
		//of course, why do you need to copy or move CThreadPool?
		CThreadPool& operator=(const CThreadPool &)=delete;
		//1. join all the threads which were used by CThreadPool::add in destructor
		//2. block until all the threads which were used by CThreadPool::add_and_detach is completed in destructor
		~CThreadPool();
	};
}

#endif
