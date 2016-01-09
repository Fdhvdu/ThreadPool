#ifndef CTASK
#define CTASK
#include<future>
#include<utility>	//declval

namespace nTool
{
	template<class Ret>
	Ret make_function();

	template<class Ret>
	class CTask
	{
		std::packaged_task<decltype(make_function<Ret>)> task_;
		std::future<Ret> fut_;
	public:
		CTask() noexcept=default;
		template<class Func,class ... Args>
		explicit CTask(Func &&,Args &&...);
		CTask(const CTask &)=delete;
		CTask(CTask &&) noexcept=default;
		inline Ret get()
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

#include"CTaskT.cpp"

#endif