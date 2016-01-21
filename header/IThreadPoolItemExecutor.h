#ifndef ITHREADPOOLITEMEXECUTOR
#define ITHREADPOOLITEMEXECUTOR
#include<functional>	//function
#include"../../lib/header/tool/CPimpl.h"

namespace nThread
{
	class CThreadPoolCommun;

	struct IThreadPoolItemExecutorBase	//I give up to use Non-Virtual Interface Idiom here
										//because this is a abstract base struct
	{
		virtual void exec()=0;
		virtual bool is_running() const noexcept=0;
		inline bool joinable() const noexcept	//I am trying to remove this
		{
			return joinable_();
		}
		virtual void wait()=0;
		virtual ~IThreadPoolItemExecutorBase()=0;
	protected:
		virtual bool joinable_() const noexcept
		{
			return false;
		}
	};

	class CThreadPoolItemExecutorDetach:public IThreadPoolItemExecutorBase
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolItemExecutorDetach(CThreadPoolCommun &&,std::function<void()> &&);
		void exec() override;
		bool is_running() const noexcept override;	//only the destructor of CThreadPoolItem will call this
		void wait() override;	//only the destructor of CThreadPoolItem will call this
		~CThreadPoolItemExecutorDetach();
	};

	class CThreadPoolItemExecutorJoin:public IThreadPoolItemExecutorBase
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	protected:
		bool joinable_() const noexcept override
		{
			return true;
		}
	public:
		CThreadPoolItemExecutorJoin(CThreadPoolCommun &&,std::function<void()> &&);
		void exec() override;
		bool is_running() const noexcept override;
		void wait() override;
		~CThreadPoolItemExecutorJoin();
	};
}

#endif