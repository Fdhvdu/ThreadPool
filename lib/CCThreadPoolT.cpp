#include"CCThreadPool.h"
#include<memory>	//unique_ptr

namespace nTool
{
	template<class Func>
	CThreadPool<Func>::CThreadPool(const std::size_t count)
		:size_(count),thr_(new CThreadPoolItem<Func>[count])
	{
		for(auto p(thr_);p!=thr_+count;++p)
		{
			p->setCommun(std::unique_ptr<ThreadPoolCommunBase<Func>>(new CThreadPoolCommun<Func>(p,join_anyList_,waitingQue_,id_++)));
			waitingQue_.push(typename CThreadPoolCommun<Func>::pair(id_.get(),p));
		}
	}

	template<class Func>
	template<class ... Args>
	std::size_t CThreadPool<Func>::add(Args &&...args)
	{
		auto temp(waitingQue_.wait_and_pop());
		const std::size_t id(temp.first);
		temp.second->assign(std::forward<Args>(args)...);
		return id;
	}

	template<class Func>
	void CThreadPool<Func>::join_all()
	{
		for(auto i(0);i!=count();++i)
			if(joinable(i))
				join(i);
	}

	template<class Func>
	std::size_t CThreadPool<Func>::join_any()
	{
		auto temp(join_anyList_.wait_and_pop());
		const std::size_t id(temp.first);
		temp.second->join();
		return id;
	}

	template<class Func>
	CThreadPool<Func>::~CThreadPool()
	{
		delete []thr_;	//CThreadPoolItem is RAII, you don't have to call join_all()
	}
}