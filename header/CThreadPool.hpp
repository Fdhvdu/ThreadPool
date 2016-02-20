#ifndef CTHREADPOOL
#define CTHREADPOOL
#include<functional>	//bind, function
#include<thread>	//thread::hardware_concurrency
#include<type_traits>	//result_of
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
		typedef std::result_of<decltype(std::thread::hardware_concurrency)&()>::type size_type;
		typedef IThreadPoolItemBase::id thread_id;
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
		//1. block until CThreadPool::available is not zero and execute the func
		//2. after returning from add, CThreadPool::available will reduce 1
		//3. after returning from add, CThreadPool::joinable(thread_id) will return true
		//4.
		//you must call CThreadPool::join, CThreadPool::join_any or CThreadPool::join_all after returning from add at some moment
		//otherwise, CThreadPool::available cannot increase 1
		template<class Func,class ... Args>
		inline thread_id add(Func &&func,Args &&...args)
		{
			return add_(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		}
		//1. block until CThreadPool::available is not zero and execute the func
		//2. after returning from add_and_detach, CThreadPool::available will reduce 1
		//3. after the func is completed, CThreadPool::available will increase 1 automatically
		template<class Func,class ... Args>
		inline void add_and_detach(Func &&func,Args &&...args)
		{
			add_and_detach_(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		}
		//1. return the total of usable threads at that moment
		//2. reduce 1 after returning from CThreadPool::add or CThreadPool::add_and_detach
		//3. increase 1 automatically after the func of CThreadPool::add_and_detach is completed
		//4. increase 1 after returning from CThreadPool::join or CThreadPool::join_any
		//5. equal to CThreadPool::size after returning from CThreadPool::join_all or CThreadPool::wait_until_all_available at that moment
		//6. non-block
		size_type available() const noexcept;
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
		//1. block until any threads complete the func
		//2. return the thread_id of the thread which completes the func
		//3. after returning from join_any, CThreadPool::joinable(thread_id) will return false
		thread_id join_any();
		//1. return whether the thread_id has been join yet
		//2. return true for the thread_id which was returned by CThreadPool::add
		//3. return false for the thread_id which was used by CThreadPool::join
		//4. return false for the thread_id which was returned by CThreadPool::join_any
		//5. return false for the thread_id which was used by CThreadPool::add_and_detach
		//6. non-block
		bool joinable(thread_id) const noexcept;
		//1. return the total of usable threads
		//2. is fixed after constructing
		//3. non-block
		size_type size() const noexcept;
		//1. block until CThreadPool::available equal to CThreadPool::size
		//2. will block wait_until_all_available
		void wait_until_all_available() const;
		//of course, why do you need to copy or move CThreadPool?
		CThreadPool& operator=(const CThreadPool &)=delete;
		//1. join all the threads which were used by CThreadPool::add in destructor
		//2. block until all the threads which were used by CThreadPool::add_and_detach is completed in destructor
		~CThreadPool();
	};
}

#endif
