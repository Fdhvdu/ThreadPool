#include"CThreadPoolItemExecutor_Ret.h"
#include<utility>
#include"../../lib/header/tool/CScopeGuard.h"

namespace nThread
{
	template<class Ret>
	template<class Func,class ... Args>
	CThreadPoolItemExecutor_Ret<Ret>::CThreadPoolItemExecutor_Ret(std::unique_ptr<IThreadPoolCommunBase> &commun,Func &&func,Args &&...args)
		:commun_{commun},task_{std::forward<Func>(func),std::forward<Args>(args)...}{}

	template<class Ret>
	Ret CThreadPoolItemExecutor_Ret<Ret>::get()
	{
		const nTool::CScopeGuard<void()> sg{[=]{commun_->destroy();}};
		return task_.get();
	}
}