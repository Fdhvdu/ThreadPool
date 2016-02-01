#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN
#include<memory>	//allocator

namespace nThread
{
	class CThreadPoolItem;
	template<class T,class Alloc>
	class CThreadForward_list;
	template<class T>
	class CThreadRingBuf;

	class CThreadPoolCommunDetach
	{
		CThreadPoolItem *item_;
		CThreadRingBuf<CThreadPoolItem*> *waiting_buf_;
	public:
		CThreadPoolCommunDetach(CThreadPoolItem *,CThreadRingBuf<CThreadPoolItem*> *);
		void func_is_completed();	//call destroy
	};

	class CThreadPoolCommunJoin
	{
		CThreadPoolItem *item_;
		CThreadForward_list<CThreadPoolItem*,std::allocator<CThreadPoolItem*>> *join_anyList_;	//or use deque
		CThreadRingBuf<CThreadPoolItem*> *waiting_buf_;
	public:
		CThreadPoolCommunJoin(CThreadPoolItem *,CThreadForward_list<CThreadPoolItem*,std::allocator<CThreadPoolItem*>> *,CThreadRingBuf<CThreadPoolItem*> *);
		void destroy();	//erase CThreadPool::Impl::join_anyList and push CThreadPoolItem into CThreadPool::Impl::waiting_buf
		void func_is_completed();	//push CThreadPoolItem into CThreadPool::Impl::join_anyList
	};
}

#endif