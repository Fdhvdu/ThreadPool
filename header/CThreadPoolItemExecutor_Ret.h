#ifndef CTHREADPOOLITEMEXECUTOR_RET
#define CTHREADPOOLITEMEXECUTOR_RET
#include"IThreadPoolItemExecutor.h"
#include<functional>	//function
#include<memory>	//unique_ptr
#include"../../lib/header/thread/CTask.h"

namespace nThread
{
	template<class Ret>
	class CThreadPoolItemExecutor_Ret:public IThreadPoolItemExecutorBase
	{
		std::unique_ptr<IThreadPoolCommunBase> commun_;
		CTask<Ret> task_;
	public:
		template<class Func,class ... Args>
		CThreadPoolItemExecutor_Ret(std::unique_ptr<IThreadPoolCommunBase> &&,Func &&,Args &&...);
		CThreadPoolItemExecutor_Ret(const CThreadPoolItemExecutor_Ret &)=delete;
		void exec() override
		{
			task_();
		}
		Ret get();
		bool is_running() const noexcept override
		{
			return task_.valid();
		}
		void wait() override
		{
			task_.wait();
		}
		CThreadPoolItemExecutor_Ret& operator=(const CThreadPoolItemExecutor_Ret &)=delete;
	};
}

#include"CThreadPoolItemExecutor_Ret.cpp"

#endif