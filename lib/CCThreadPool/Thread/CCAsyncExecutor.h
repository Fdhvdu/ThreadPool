#ifndef __CCAsyncExecutor
#define __CCAsyncExecutor
#include<future>
#include<utility>

namespace nTool
{
	template<class Func_t>
	class CAsyncExecutor
	{
		std::packaged_task<Func_t> task_;
		decltype(std::declval<decltype(task_)>().get_future()) fut_;
	public:
		CAsyncExecutor() noexcept=default;
		template<class Func,class ... Args>
		explicit CAsyncExecutor(Func &&,Args &&...);
		CAsyncExecutor(const CAsyncExecutor &)=delete;
		CAsyncExecutor(CAsyncExecutor &&) noexcept=default;
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
		CAsyncExecutor& operator=(const CAsyncExecutor &)=delete;
		CAsyncExecutor& operator=(CAsyncExecutor &&) noexcept=default;
	};
}

#include"CCAsyncExecutorT.cpp"

#endif