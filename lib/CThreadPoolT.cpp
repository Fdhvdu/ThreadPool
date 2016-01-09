#include"CThreadPool.h"
#include<utility>

namespace nTool
{
	template<class Func,class ... Args>
	std::size_t CThreadPool::add(Func &&func,Args &&...args)
	{
		auto temp{waitingQue_.wait_and_pop()};
		const auto id{temp.first};
		temp.second->assign(std::forward<Func>(func),std::forward<Args>(args)...);
		return id;
	}
}