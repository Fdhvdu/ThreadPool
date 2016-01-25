#ifndef CTHREADPOOL
#define CTHREADPOOL
#include<cstddef>	//size_t
#include<functional>	//bind, function
#include<thread>	//thread::id
#include<utility>	//forward
#include"../../lib/header/tool/CPimpl.hpp"

namespace nThread
{
	class CThreadPool	//cannot return value
	{
	public:
		typedef std::thread::id thread_id;
	private:
		struct Impl;
		nTool::CPimpl<Impl> impl_;
		thread_id add_(std::function<void()> &&);
		void add_and_detach_(std::function<void()> &&);
	public:
		//1. determine how many threads you want to use
		//2. the value you pass will always equal to count
		explicit CThreadPool(std::size_t);
		//of course, why do you need to copy or move CThreadPool?
		CThreadPool(const CThreadPool &)=delete;
		//1.
		//execute func if available!=0
		//otherwise, waiting until 0<available and execute
		//2.
		//after calling add, available reduce 1
		//3.
		//you have to call join, join_any or join_all after calling add
		//otherwise, there is no available threads even after threads complete the job
		template<class Func,class ... Args>
		inline thread_id add(Func &&func,Args &&...args)
		{
			return add_(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		}
		//1.
		//execute func if available!=0
		//otherwise, waiting until 0<available and execute
		//2. after calling add, available reduce 1
		//3. when the func is completed, available increase 1
		//4. if you don't know what "detach" means, you should look std::thread::detach
		template<class Func,class ... Args>
		inline void add_and_detach(Func &&func,Args &&...args)
		{
			add_and_detach_(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		}
		//1. return how many threads can be used now
		//2. reduce 1 after calling add or add_and_detach
		std::size_t available() const noexcept;
		//1. return total threads can be used
		//2. the return value is what you pass to constructor
		std::size_t count() const noexcept;
		//do not combine join and join_any together in your code
		//it will make some join_any cannot get notification
		//for more details, see example.cpp
		void join(thread_id);
		//1. check whether the thread_id of thread is joinable
		//2. after calling add, the id return by add, will make the thread_id of thread joinable
		//3. only when you call join, join_all or join_any (or destructor) will make the thread_id of thread not joinable
		bool joinable(thread_id) const noexcept;
		//1.
		//join_all and wait_until_all_available are different
		//join_all will not wait any threads which are belong to detach
		//2. it will not block add, you have to control by yourself
		void join_all();
		//1.
		//do not combine join and join_any together in your code
		//it will make some join_any cannot get notification
		//for more details, see example.cpp
		//2. join_any must return value, because I have implemented add_and_detach already
		thread_id join_any();
		//1. wait until available equal to count
		//2.
		//wait_until_all_available and join_all and are different
		//join_all will not wait any threads which are belong to detach
		void wait_until_all_available() const;
		//of course, why do you need to copy or move CThreadPool?
		CThreadPool& operator=(const CThreadPool &)=delete;
		//will join all thread when destroying
		~CThreadPool();
	};
}

#endif