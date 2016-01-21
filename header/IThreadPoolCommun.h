#ifndef ITHREADPOOLCOMMUN
#define ITHREADPOOLCOMMUN
#include"../../lib/header/tool/CPimpl.h"

namespace nThread
{
	class CThreadPoolItem;
	template<class Func>
	class CThreadList;
	template<class Func>
	class CThreadQueue;

	struct IThreadPoolCommunBase
	{
		virtual void destroy()=0;
		virtual void func_is_completed()=0;
		virtual ~IThreadPoolCommunBase();
	};

	class CThreadPoolCommun: public IThreadPoolCommunBase
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolCommun(CThreadPoolItem *,CThreadList<CThreadPoolItem*> *,CThreadQueue<CThreadPoolItem*> *);
		void destroy() override;	//erase CThreadPool::Impl::join_anyList and push CThreadPoolItem into CThreadPool::Impl::waitingQue
		void func_is_completed() override;	//push CThreadPoolItem into CThreadPool::Impl::waitingQue
		~CThreadPoolCommun();
	};

	class CThreadPoolCommunDetach: public IThreadPoolCommunBase
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolCommunDetach(CThreadPoolItem *,CThreadQueue<CThreadPoolItem*> *);
		void destroy() override{}
		void func_is_completed() override;
		~CThreadPoolCommunDetach();
	};
}

#endif