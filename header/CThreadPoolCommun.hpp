#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN

namespace nThread
{
	class CThreadPoolItem;
	template<class>class CWait_bounded_queue;

	class CThreadPoolCommunDetach
	{
		CThreadPoolItem *item_;
		CWait_bounded_queue<CThreadPoolItem*> *waiting_queue_;
	public:
		CThreadPoolCommunDetach(CThreadPoolItem *,CWait_bounded_queue<CThreadPoolItem*> *) noexcept;
		void func_is_completed();	//push CThreadPoolItem into CThreadPool::Impl::waiting_buf
	};

	class CThreadPoolCommunJoin
	{
		CThreadPoolItem *item_;
		CWait_bounded_queue<CThreadPoolItem*> *waiting_queue_;
	public:
		CThreadPoolCommunJoin(CThreadPoolItem *,CWait_bounded_queue<CThreadPoolItem*> *) noexcept;
		void destroy();	//push CThreadPoolItem into CThreadPool::Impl::waiting_buf
	};
}

#endif