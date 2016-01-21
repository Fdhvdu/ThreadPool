#ifndef CTHREADPOOL
#define CTHREADPOOL
#include<cstddef>	//size_t
#include<type_traits>	//declval
#include"../../lib/header/tool/CPimpl.h"
#include"CThreadPoolItem.h"

namespace nThread
{
	class CThreadPool	//same job, different argument and no return value
						//with add, add_and_detach, join, joinable, join_all and join_any
						//every threads must call join, join_any or join_all after calling add
						//otherwise, there is no available thread even after threads complete their job
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
		CThreadPoolItem* wait_and_pop_();
	public:
		typedef decltype(std::declval<CThreadPoolItem>().get_id()) thread_id;
		explicit CThreadPool(std::size_t);
		CThreadPool(const CThreadPool &)=delete;
		template<class Func,class ... Args>
		thread_id add(Func &&,Args &&...);
		template<class Func,class ... Args>
		inline void add_and_detach(Func &&func,Args &&...args)
		{
			wait_and_pop_()->assign_and_detach(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		}
		std::size_t available() const noexcept;
		std::size_t count() const noexcept;
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

#include"CThreadPool.cpp"

#endif