#include"CCThreadPool_Ret.h"
#include<memory>	//unique_ptr

namespace nTool
{
	template<class Func>
	CThreadPool_Ret<Func>::CThreadPool_Ret(const std::size_t &count)
		:size_(count),thr_(new CThreadPoolItem<Func>[count])
	{
		for(auto p(thr_);p!=thr_+count;++p)
		{
			p->setCommun(std::unique_ptr<ThreadPoolCommunBase<Func>>(new CThreadPoolCommun_Ret<Func>(p,waitingQue_,id_++)));
			waitingQue_.push(typename CThreadPoolCommun_Ret<Func>::pair(id_.get(),p));
		}
	}

	template<class Func>
	template<class ... Args>
	std::size_t CThreadPool_Ret<Func>::add(Args &&...args)
	{
		auto temp(waitingQue_.wait_and_pop());
		const std::size_t id(temp.first);
		temp.second->assign(std::forward<Args>(args)...);
		return id;
	}

	template<class Func>
	CThreadPool_Ret<Func>::~CThreadPool_Ret()
	{
		delete []thr_;
	}
}