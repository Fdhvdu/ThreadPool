#include"CThreadPool_Ret.h"
#include<utility>	//forward, move

namespace nThread
{
	template<class Ret>
	CThreadPool_Ret<Ret>::CThreadPool_Ret(std::size_t count)
	{
		while(count--)
		{
			CThreadPoolItem_Ret<Ret> item{&waitingQue_};
			const auto id{item.get_id()};
			thr_.emplace(id,std::move(item));
			waitingQue_.emplace(&thr_.at(id));
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

	template<class Ret>
	void CThreadPool_Ret<Ret>::wait_all() const
	{
		for(const auto &val:thr_)
			if(valid(val.first))
				wait(val.first);
	}
}