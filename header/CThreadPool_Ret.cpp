#include"CThreadPool_Ret.h"
#include<memory>	//make_unique
#include"../../lib/header/algorithm/algorithm.h"

namespace nThread
{
	template<class Ret>
	CThreadPool_Ret<Ret>::CThreadPool_Ret(const std::size_t count)
		:size_{count},thr_{new CThreadPoolItem_Ret<Ret>[count]}
	{
		nAlgorithm::for_each_val(thr_,thr_+count,[&](const auto p){
			p->setCommun(std::make_unique<CThreadPoolCommun_Ret<Ret>>(p,waitingQue_,id_++));
			waitingQue_.emplace(id_.get(),p);
		});
	}

	template<class Ret>
	template<class Func,class ... Args>
	typename CThreadPool_Ret<Ret>::thread_id CThreadPool_Ret<Ret>::add(Func &&func,Args &&...args)
	{
		auto temp{waitingQue_.wait_and_pop()};
		const auto id{temp.first};
		temp.second->assign(std::forward<Func>(func),std::forward<Args>(args)...);
		return id;
	}

	template<class Ret>
	CThreadPool_Ret<Ret>::~CThreadPool_Ret()
	{
		delete []thr_;
	}
}