#include"CCAsyncExecutor.h"
#include<functional>	//bind

namespace nTool
{
	template<class Func>
	template<class ... Args>
	void CAsyncExecutor<Func>::init(Args &&...args)
	{
		task_=std::packaged_task<Func>(std::bind(std::forward<Args>(args)...));
		fut_=task_.get_future();
	}
}