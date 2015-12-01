#include"CCAsyncExecutor.h"

namespace nTool
{
	namespace CAsyncExecutorImpl
	{
		template<class Func>
		void execute(std::promise<void> &prom,const Func &func)
		{
			func();
			prom.set_value();
		}
	}

	template<class Func>
	template<class ... Args>
	void CAsyncExecutor<Func>::init(Args &&...args)
	{
		prom_=std::promise<result_type>();
		fut_=prom_.get_future();
		func_=std::bind(std::forward<Args>(args)...);
	}
}