#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN
#include"../../lib/header/tool/CPimpl.h"

namespace nThread
{
	class CThreadPoolItem;
	template<class Func>
	class CThreadList;
	template<class Func>
	class CThreadQueue;

	struct CThreadPoolCommunBase
	{
		virtual void destroy()=0;
		virtual void func_is_completed()=0;
		virtual ~CThreadPoolCommunBase();
	};

	class CThreadPoolCommun
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolCommun(CThreadPoolItem *,CThreadList<CThreadPoolItem*> *,CThreadQueue<CThreadPoolItem*> *);
		CThreadPoolCommun(CThreadPoolCommun &&) noexcept;
		void destroy();	//erase CThreadPool::Impl::join_anyList and push CThreadPoolItem into CThreadPool::Impl::waitingQue
		void detach();	//notify CThreadPool::join_any
		void func_is_completed();	//push CThreadPoolItem into CThreadPool::Impl::waitingQue
		CThreadPoolCommun& operator=(CThreadPoolCommun &&) noexcept;
		~CThreadPoolCommun();
	};
}

#endif