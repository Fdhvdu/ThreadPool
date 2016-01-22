#include"CThreadPoolItem_Ret.h"

namespace nThread
{
	template<class Ret>
	void CThreadPoolItem_Ret<Ret>::loop_()
	{
		while(waiting_(),!destructor_)
			exec_->exec();
	}

	template<class Ret>
	CThreadPoolItem_Ret<Ret>::CThreadPoolItem_Ret()
		:destructor_{false},wait_{0},thr_{&CThreadPoolItem_Ret<Ret>::loop_,this}{}
	
	template<class Ret>
	template<class Func,class ... Args>
	void CThreadPoolItem_Ret<Ret>::assign_and_ret(Func &&func,Args &&...args)
	{
		exec_=std::make_unique<CThreadPoolItemExecutor_Ret<Ret>>(commun_,std::forward<Func>(func),std::forward<Args>(args)...);
		wake_();
	}

	template<class Ret>
	CThreadPoolItem_Ret<Ret>::~CThreadPoolItem_Ret()
	{
		if(exec_&&exec_->is_running())
			exec_->wait();
		destructor_=true;
		wake_();
	}
}