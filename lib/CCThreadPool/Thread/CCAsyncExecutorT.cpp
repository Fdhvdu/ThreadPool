#include"CCAsyncExecutor.h"
#include<functional>	//bind

namespace nTool
{
	template<class Func>
	CAsyncExecutor<Func>::CAsyncExecutor(CAsyncExecutor &&rVal) noexcept
		:task_(std::move(rVal.task_)),fut_(std::move(rVal.fut_)){}

	template<class Func>
	template<class ... Args>
	void CAsyncExecutor<Func>::init(Args &&...args)
	{
		task_=std::packaged_task<Func>(std::bind(std::forward<Args>(args)...));
		fut_=task_.get_future();
	}

	template<class Func>
	CAsyncExecutor<Func>& CAsyncExecutor<Func>::operator=(CAsyncExecutor &&rVal) noexcept
	{
		std::swap(task_,rVal.task_);
		std::swap(fut_,rVal.fut_);
		return *this;
	}
}