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

	class CThreadPoolCommunBase
	{
	protected:
		virtual void detach_();
		virtual void finish_();
		virtual void join_();
	public:
		CThreadPoolCommunBase()=default;
		CThreadPoolCommunBase(const CThreadPoolCommunBase &)=delete;
		void communPoolDetach();
		void communPoolFinish();
		void communPoolJoin();
		CThreadPoolCommunBase& operator=(const CThreadPoolCommunBase &)=delete;
		virtual ~CThreadPoolCommunBase();
	};

	class CThreadPoolCommun
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolCommun(CThreadPoolItem *,CThreadList<CThreadPoolItem*> *,CThreadQueue<CThreadPoolItem*> *);
		CThreadPoolCommun(CThreadPoolCommun &&) noexcept;
		void detach();	//notify CThreadPool::join_any
		void func_is_completed();	//push CThreadPoolItem into CThreadPool::Impl::waitingQue
		void join();	//erase CThreadPool::Impl::join_anyList and push CThreadPoolItem into CThreadPool::Impl::waitingQue
		CThreadPoolCommun& operator=(CThreadPoolCommun &&) noexcept;
		~CThreadPoolCommun();
	};
}

#endif