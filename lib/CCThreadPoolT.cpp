#include"CCThreadPool.h"
#include<memory>	//make_unique

namespace nTool
{
	template<class Func_t>
	CThreadPool<Func_t>::CThreadPool(const std::size_t count)
		:size_{count},thr_{new CThreadPoolItem<Func_t>[count]}
	{
		for(auto p{thr_};p!=thr_+count;++p)
		{
			p->setCommun(std::make_unique<CThreadPoolCommun<Func_t>>(p,join_anyList_,waitingQue_,id_++));
			waitingQue_.emplace(id_.get(),p);
		}
	}

	template<class Func_t>
	template<class Func,class ... Args>
	std::size_t CThreadPool<Func_t>::add(Func &&func,Args &&...args)
	{
		auto temp{waitingQue_.wait_and_pop()};
		const auto id{temp.first};
		temp.second->assign(std::forward<Func>(func),std::forward<Args>(args)...);
		return id;
	}

	template<class Func_t>
	void CThreadPool<Func_t>::join_all()
	{
		for(auto i{0};i!=count();++i)
			if(joinable(i))
				join(i);
	}

	template<class Func_t>
	std::size_t CThreadPool<Func_t>::join_any()
	{
		auto temp{join_anyList_.wait_and_pop()};
		const auto id{temp.first};
		temp.second->join();
		return id;
	}

	template<class Func_t>
	CThreadPool<Func_t>::~CThreadPool()
	{
		delete []thr_;	//CThreadPoolItem is RAII, you don't have to call join_all()
	}
}