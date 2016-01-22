#ifndef ITHREADPOOLITEMEXECUTOR
#define ITHREADPOOLITEMEXECUTOR
#include<functional>	//function
#include<memory>	//unique_ptr
#include"../../lib/header/tool/CPimpl.h"

namespace nThread
{
	struct IThreadPoolCommunBase;

	struct IThreadPoolItemExecutorBase	//I give up to use Non-Virtual Interface Idiom here
										//because this is a abstract base struct
	{
		virtual void exec()=0;
		virtual bool is_running() const noexcept=0;
		virtual void wait()=0;
		virtual ~IThreadPoolItemExecutorBase()=0;
	};

	class CThreadPoolItemExecutor:public IThreadPoolItemExecutorBase
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolItemExecutor(std::unique_ptr<IThreadPoolCommunBase> &&,std::function<void()> &&);
		void exec() override;
		bool is_running() const noexcept override;
		void wait() override;
		~CThreadPoolItemExecutor();
	};
}

#endif