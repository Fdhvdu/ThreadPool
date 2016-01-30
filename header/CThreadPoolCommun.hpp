#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN

namespace nThread
{
	class CThreadPoolItem;
	template<class T>
	class CThreadList;
	template<class T>
	class CThreadQueue;

	class CThreadPoolCommunDetach
	{
		CThreadPoolItem *item_;
		CThreadQueue<CThreadPoolItem*> *waitingQue_;
	public:
		CThreadPoolCommunDetach(CThreadPoolItem *,CThreadQueue<CThreadPoolItem*> *);
		void func_is_completed();	//call destroy
	};

	class CThreadPoolCommunJoin
	{
		CThreadPoolItem *item_;
		CThreadList<CThreadPoolItem*> *join_anyList_;	//or use deque
		CThreadQueue<CThreadPoolItem*> *waitingQue_;
	public:
		CThreadPoolCommunJoin(CThreadPoolItem *,CThreadList<CThreadPoolItem*> *,CThreadQueue<CThreadPoolItem*> *);
		void destroy();	//erase CThreadPool::Impl::join_anyList and push CThreadPoolItem into CThreadPool::Impl::waitingQue
		void func_is_completed();	//push CThreadPoolItem into CThreadPool::Impl::join_anyList
	};
}

#endif