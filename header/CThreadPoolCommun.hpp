#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN
#include<memory>	//allocator

namespace nThread
{
	class CThreadPoolItem;
	template<class T,class Alloc>
	class CThreadForward_list;
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
		CThreadForward_list<CThreadPoolItem*,std::allocator<CThreadPoolItem*>> *join_anyList_;	//or use deque
		CThreadQueue<CThreadPoolItem*> *waitingQue_;
	public:
		CThreadPoolCommunJoin(CThreadPoolItem *,CThreadForward_list<CThreadPoolItem*,std::allocator<CThreadPoolItem*>> *,CThreadQueue<CThreadPoolItem*> *);
		void destroy();	//erase CThreadPool::Impl::join_anyList and push CThreadPoolItem into CThreadPool::Impl::waitingQue
		void func_is_completed();	//push CThreadPoolItem into CThreadPool::Impl::join_anyList
	};
}

#endif