#ifndef CTHREADPOOLITEMEXECUTOR_RET
#define CTHREADPOOLITEMEXECUTOR_RET
#include<functional>	//function
#include<memory>	//unique_ptr
#include"../../lib/header/thread/CTask.h"

namespace nThread
{
	template<class Ret>
	class CThreadPoolCommun_Ret;

	template<class Ret>
	class CThreadPoolItemExecutor_Ret
	{
		std::unique_ptr<CThreadPoolCommun_Ret<Ret>> commun_;
		CTask<Ret> task_;
	public:
		template<class Func,class ... Args>
		CThreadPoolItemExecutor_Ret(std::unique_ptr<CThreadPoolCommun_Ret<Ret>> &&,Func &&,Args &&...);
		CThreadPoolItemExecutor_Ret(const CThreadPoolItemExecutor_Ret &)=delete;
		void exec()
		{
			task_();
		}
		Ret get();
		bool is_running() const noexcept
		{
			return task_.valid();
		}
		void wait() const
		{
			task_.wait();
		}
		CThreadPoolItemExecutor_Ret& operator=(const CThreadPoolItemExecutor_Ret &)=delete;
	};
}

#include"CThreadPoolItemExecutor_Ret.cpp"

#endif