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
		explicit CThreadPool(std::size_t);
		CThreadPool(const CThreadPool &)=delete;
		template<class Func,class ... Args>
		inline thread_id add(Func &&func,Args &&...args)	//execute func immediately
															//you have to call join, join_any or join_all after calling add
															//otherwise, there is no available threads even after threads complete the job
		{
			return add_(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		}
		template<class Func,class ... Args>
		inline void add_and_detach(Func &&func,Args &&...args)	//execute func immediately
																//if you don't know what "detach" means
																//you should look std::thread::detach
		{
			add_and_detach_(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		}
		std::size_t available() const noexcept;	//how many threads can use now
		std::size_t count() const noexcept;	//total threads can use
		void join(thread_id);	//do not combine join and join_any together in your code
								//it will make some join_any cannot get notification
		bool joinable(thread_id) const noexcept;
		void join_all();	//it will not block add, you have to control by yourself
		thread_id join_any();	//do not combine join and join_any together in your code
								//it will make some join_any cannot get notification
								//join_any must return value, because I have implemented add_and_detach already
		void wait_until_all_available() const;
		CThreadPool& operator=(const CThreadPool &)=delete;
		~CThreadPool();
	};
}

#endif