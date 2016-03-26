#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN
#include<memory>	//allocator
//#include"../../lib/header/thread/CThread_forward_list.hpp"	//require C++17

namespace nThread
{
	class CThreadPoolItem;
	template<class T,class Alloc>
	class CThread_forward_list;	//remove this if C++17 is usable
	template<class T>
	class CThreadRingBuf;

	class CThreadPoolCommunDetach
	{
		CThreadPoolItem *item_;
		CThreadRingBuf<CThreadPoolItem*> *waiting_buf_;
	public:
		CThreadPoolCommunDetach(CThreadPoolItem *,CThreadRingBuf<CThreadPoolItem*> *) noexcept;
		void func_is_completed();	//call destroy
	};

	class CThreadPoolCommunJoin
	{
		CThreadPoolItem *item_;
		CThread_forward_list<CThreadPoolItem*,std::allocator<CThreadPoolItem*>> *join_anyList_;
		//CThread_forward_list<CThreadPoolItem*> *join_anyList_;	//require C++17
		//CThread_forward_list<CThreadPoolItem*>::CNode node_;	//require C++17
		CThreadRingBuf<CThreadPoolItem*> *waiting_buf_;
	public:
		CThreadPoolCommunJoin(CThreadPoolItem *,CThread_forward_list<CThreadPoolItem*,std::allocator<CThreadPoolItem*>> *,CThreadRingBuf<CThreadPoolItem*> *);
		void destroy();	//erase CThreadPool::Impl::join_anyList and push CThreadPoolItem into CThreadPool::Impl::waiting_buf
		void func_is_completed(); //noexcept	//(require C++17)
								  //push CThreadPoolItem into CThreadPool::Impl::join_anyList
	};
}

#endif