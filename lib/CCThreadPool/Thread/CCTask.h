#ifndef __CCTask
#define __CCTask
#include<future>
#include<utility>	//declval

namespace nTool
{
	template<class Func_t>
	class CTask
	{
		std::packaged_task<Func_t> task_;
		decltype(std::declval<decltype(task_)>().get_future()) fut_;
	public:
		CTask() noexcept=default;
		template<class Func,class ... Args>
		explicit CTask(Func &&,Args &&...);
		CTask(const CTask &)=delete;
		CTask(CTask &&) noexcept=default;
		inline decltype(std::declval<decltype(fut_)>().get()) get()
		{
			return fut_.get();
		}
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
		CTask& operator=(const CTask &)=delete;
		CTask& operator=(CTask &&) noexcept=default;
	};
}

#include"CCTaskT.cpp"

#endif