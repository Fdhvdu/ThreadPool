#ifndef CTHREADPOOLITEMEXECUTOR_RET
#define CTHREADPOOLITEMEXECUTOR_RET
#include"../../lib/header/thread/CTask.h"

namespace nThread
{
	template<class Ret>
	class CThreadPoolItemExecutor_Ret
	{
		CTask<Ret> task_;
	public:
		template<class Func,class ... Args>
		CThreadPoolItemExecutor_Ret(Func &&,Args &&...);
		CThreadPoolItemExecutor_Ret(const CThreadPoolItemExecutor_Ret &)=delete;
		inline void exec()
		{
			task_();
		}
		inline Ret get()
		{
			return task_.get();
		}
		inline bool is_running() const noexcept
		{
			return task_.valid();
		}
		inline void wait() const
		{
			task_.wait();
		}
		CThreadPoolItemExecutor_Ret& operator=(const CThreadPoolItemExecutor_Ret &)=delete;
	};
}

#include"CThreadPoolItemExecutor_Ret.cpp"

#endif