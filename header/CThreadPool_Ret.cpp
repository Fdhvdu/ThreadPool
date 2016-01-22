#include"CThreadPool_Ret.h"
#include<memory>	//make_unique
#include<utility>
#include"CThreadPoolCommun_Ret.h"

namespace nThread
{
	template<class Ret>
	CThreadPool_Ret<Ret>::CThreadPool_Ret(std::size_t count)
	{
		while(count--)
		{
			CThreadPoolItem_Ret<Ret> item;
			const auto id{item.get_id()};
			thr_.emplace(id,std::move(item));
			waitingQue_.emplace(&thr_[id]);
		}
	}

	template<class Ret>
	template<class Func,class ... Args>
	typename CThreadPool_Ret<Ret>::thread_id CThreadPool_Ret<Ret>::add(Func &&func,Args &&...args)
	{
		auto temp{waitingQue_.wait_and_pop()};
		temp->assign(std::make_unique<CThreadPoolItemExecutor_Ret<Ret>>(std::make_unique<CThreadPoolCommun_Ret<Ret>>(temp,waitingQue_),std::forward<Func>(func),std::forward<Args>(args)...));
		return temp->get_id();
	}
}