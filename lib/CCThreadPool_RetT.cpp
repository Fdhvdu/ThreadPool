#include"CCThreadPool_Ret.h"
#include<memory>	//make_unique

namespace nTool
{
	template<class Func_t>
	CThreadPool_Ret<Func_t>::CThreadPool_Ret(const std::size_t count)
		:size_{count},thr_{new CThreadPoolItem<Func_t>[count]}
	{
		for(auto p{thr_};p!=thr_+count;++p)
		{
			p->setCommun(std::make_unique<CThreadPoolCommun_Ret<Func_t>>(p,waitingQue_,id_++));
			waitingQue_.emplace(id_.get(),p);
		}
	}

	template<class Func_t>
	template<class Func,class ... Args>
	std::size_t CThreadPool_Ret<Func_t>::add(Func &&func,Args &&...args)
	{
		auto temp{waitingQue_.wait_and_pop()};
		const auto id{temp.first};
		temp.second->assign_and_ret(std::forward<Func>(func),std::forward<Args>(args)...);
		return id;
	}

	template<class Func_t>
	CThreadPool_Ret<Func_t>::~CThreadPool_Ret()
	{
		delete []thr_;
	}
}