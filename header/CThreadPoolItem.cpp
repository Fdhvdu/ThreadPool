#include"CThreadPoolItem.h"
#include"../../lib/header/tool/CScopeGuard.h"

namespace nThread
{
	template<class Ret>
	void CThreadPoolItem<Ret>::loop_()
	{
		while(waiting_(),!destructor_)
			exec_->exec();
	}

	template<class Ret>
	CThreadPoolItem<Ret>::CThreadPoolItem()
		:destructor_{false},joinable_{false},wait_{0},thr_{&CThreadPoolItem<Ret>::loop_,this}{}

	template<class Ret>
	template<class Func,class ... Args>
	void CThreadPoolItem<Ret>::assign(Func &&func,Args &&...args)
	{
		exec_=std::make_unique<CThreadPoolItemExecutorJoin>(commun_.get(),std::forward<Func>(func),std::forward<Args>(args)...);
		joinable_=true;
		wake_();
	}

	template<class Ret>
	template<class Func,class ... Args>
	void CThreadPoolItem<Ret>::assign_and_detach(Func &&func,Args &&...args)
	{
		exec_=std::make_unique<CThreadPoolItemExecutorDetach>(commun_.get(),std::forward<Func>(func),std::forward<Args>(args)...);
		joinable_=false;
		wake_();
	}

	template<class Ret>
	template<class Func,class ... Args>
	void CThreadPoolItem<Ret>::assign_and_ret(Func &&func,Args &&...args)
	{
		exec_=std::make_unique<CThreadPoolItemExecutorRet<Ret>>(commun_.get(),std::forward<Func>(func),std::forward<Args>(args)...);
		joinable_=false;
		wake_();
	}

	template<class Ret>
	CThreadPoolItem<Ret>::~CThreadPoolItem()
	{
		if(exec_&&exec_->is_running())
			exec_->wait();
		destructor_=true;
		wake_();
	}

	template<class Ret>
	IThreadPoolItemExecutorBase<Ret>::~IThreadPoolItemExecutorBase(){}

	template<class Func,class ... Args>
	CThreadPoolItemExecutorDetach::CThreadPoolItemExecutorDetach(CThreadPoolCommunBase *commun,Func &&func,Args &&...args)
		:commun_{commun},complete_{0},func_{std::bind(std::forward<Func>(func),std::forward<Args>(args)...)}{}

	template<class Func,class ... Args>
	CThreadPoolItemExecutorJoin::CThreadPoolItemExecutorJoin(CThreadPoolCommunBase *commun,Func &&func,Args &&...args)
		:commun_{commun},complete_{0},func_{std::bind(std::forward<Func>(func),std::forward<Args>(args)...)},running_{true}{}

	template<class Ret>
	template<class Func,class ... Args>
	CThreadPoolItemExecutorRet<Ret>::CThreadPoolItemExecutorRet(CThreadPoolCommunBase *commun,Func &&func,Args &&...args)
		:commun_{commun},task_{std::forward<Func>(func),std::forward<Args>(args)...}{}

	template<class Ret>
	decltype(std::declval<CTask<Ret>>().get()) CThreadPoolItemExecutorRet<Ret>::get()
	{
		const nTool::CScopeGuard<void()> sg{[=]{commun_->communPoolDetach();}};
		return task_.get();
	}
}