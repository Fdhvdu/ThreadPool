#include"CThreadPool.h"
#include<utility>

namespace nThread
{
	template<class Func,class ... Args>
	CThreadPool::thread_id CThreadPool::add(Func &&func,Args &&...args)
	{
		auto temp{waitingQue_.wait_and_pop()};
		const auto id{temp->get_id()};
		temp->assign(std::bind(std::forward<Func>(func),std::forward<Args>(args)...));
		return id;
	}
}