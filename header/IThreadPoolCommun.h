#ifndef ITHREADPOOLCOMMUN
#define ITHREADPOOLCOMMUN

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
		CThreadPoolItem *item_;
		CThreadList<CThreadPoolItem*> &join_anyList_;	//or use deque
		CThreadQueue<CThreadPoolItem*> &waitingQue_;
	public:
		CThreadPoolCommun(CThreadPoolItem *,CThreadList<CThreadPoolItem*> &,CThreadQueue<CThreadPoolItem*> &);
		void destroy() override;	//erase CThreadPool::Impl::join_anyList and push CThreadPoolItem into CThreadPool::Impl::waitingQue
		void func_is_completed() override;	//push CThreadPoolItem into CThreadPool::Impl::waitingQue
		~CThreadPoolCommun();
	};

	class CThreadPoolCommunDetach: public IThreadPoolCommunBase
	{
		CThreadPoolItem *item_;
		CThreadQueue<CThreadPoolItem*> &waitingQue_;
	public:
		CThreadPoolCommunDetach(CThreadPoolItem *,CThreadQueue<CThreadPoolItem*> &);
		void destroy() override{}
		void func_is_completed() override;
		~CThreadPoolCommunDetach();
	};
}

#endif