#include"CThreadPool_Ret.h"
#include<memory>	//make_unique
#include<utility>

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
			thr_[id].setCommun(std::make_unique<CThreadPoolCommun_Ret<Ret>>(&thr_[id],waitingQue_));
			waitingQue_.emplace(&thr_[id]);
		}
	}

	template<class Ret>
	template<class Func,class ... Args>
	typename CThreadPool_Ret<Ret>::thread_id CThreadPool_Ret<Ret>::add(Func &&func,Args &&...args)
	{
		auto temp{waitingQue_.wait_and_pop()};
		temp->assign(std::forward<Func>(func),std::forward<Args>(args)...);
		return temp->get_id();
	}
}