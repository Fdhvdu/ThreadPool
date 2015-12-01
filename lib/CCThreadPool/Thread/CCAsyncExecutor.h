#ifndef __CCAsyncExecutor
#define __CCAsyncExecutor
#include<functional>
#include<future>

namespace nTool
{
	namespace CAsyncExecutorImpl
	{
		template<class Ret,class Func>
		inline void execute(std::promise<Ret> &prom,const Func &func)
		{
			prom.set_value(func());
		}

		template<class Func>
		void execute(std::promise<void> &,const Func &);
	}

	template<class Func>
	class CAsyncExecutor
	{
		typedef typename std::function<Func>::result_type result_type;
		std::function<Func> func_;
		std::promise<result_type> prom_;
		std::future<result_type> fut_;
	public:
		inline void execute()
		{
			nTool::CAsyncExecutorImpl::execute<result_type>(prom_,func_);
		}
		inline typename CAsyncExecutor<Func>::result_type get()
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
	};
}

#include"CCAsyncExecutorT.cpp"

#endif