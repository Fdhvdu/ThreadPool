#include"CThreadPoolItem.h"

namespace nThread
{
	template<class Func,class ... Args>
	void CThreadPoolItem::assign(Func &&func,Args &&...args)
	{
		exec_=std::make_unique<CThreadPoolItemExecutorJoin>(commun_.get(),std::forward<Func>(func),std::forward<Args>(args)...);
		wake_();
	}

	template<class Func,class ... Args>
	void CThreadPoolItem::assign_and_detach(Func &&func,Args &&...args)
	{
		exec_=std::make_unique<CThreadPoolItemExecutorDetach>(commun_.get(),std::forward<Func>(func),std::forward<Args>(args)...);
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
}