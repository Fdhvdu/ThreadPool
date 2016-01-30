#ifndef ITHREADPOOLITEMEXECUTOR
#define ITHREADPOOLITEMEXECUTOR
#include<functional>	//function
#include"../../lib/header/tool/CPimpl.hpp"

namespace nThread
{
	class CThreadPoolCommunDetach;
	class CThreadPoolCommunJoin;

	struct IThreadPoolItemExecutorBase
	{
		virtual void exec()=0;
		virtual bool is_running() const noexcept=0;
		virtual void wait()=0;
		virtual ~IThreadPoolItemExecutorBase()=0;
	};

	class CThreadPoolItemExecutorDetach:public IThreadPoolItemExecutorBase
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolItemExecutorDetach(CThreadPoolCommunDetach &&,std::function<void()> &&);
		void exec() override;
		bool is_running() const noexcept override;	//only the destructor of CThreadPoolItem will call this
		void wait() override;	//only the destructor of CThreadPoolItem will call this
		~CThreadPoolItemExecutorDetach();
	};

	class CThreadPoolItemExecutorJoin:public IThreadPoolItemExecutorBase
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolItemExecutorJoin(CThreadPoolCommunJoin &&,std::function<void()> &&);
		void exec() override;
		bool is_running() const noexcept override;
		void wait() override;
		~CThreadPoolItemExecutorJoin();
	};
}

#endif