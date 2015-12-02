#ifndef __CCAsyncExecutor
#define __CCAsyncExecutor
#include<future>
#include<utility>

namespace nTool
{
	template<class Func>
	class CAsyncExecutor
	{
		std::packaged_task<Func> task_;
		decltype(std::declval<decltype(task_)>().get_future()) fut_;
	public:
		inline decltype(std::declval<decltype(fut_)>().get()) get()
		{
			return fut_.get();
		}
		template<class ... Args>
		void init(Args &&...);
		inline bool valid() const noexcept	//return true after calling init; otherwise, return false
											//for default constructor, it returns false
		{
			return fut_.valid();
		}
		inline void wait() const
		{
			fut_.wait();
		}
		inline void operator()()
		{
			task_();
		}
	};
}

#include"CCAsyncExecutorT.cpp"

#endif