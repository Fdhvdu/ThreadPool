#ifndef CTHREADPOOLCOMMUN
#define CTHREADPOOLCOMMUN
#include<cstddef>	//size_t
#include<utility>	//pair
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
	public:
		typedef std::pair<std::size_t,CThreadPoolItem*> pair;
	private:
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		CThreadPoolCommun(CThreadPoolItem *,CThreadList<pair> &,CThreadQueue<pair> &,std::size_t);
		CThreadPoolCommun(const CThreadPoolCommun &)=delete;
		void detach();	//notify CThreadPool::join_any
		void finish();	//push CThreadPoolItem into waitingQue_
		void join();	//erase join_anyList_ and push CThreadPoolItem into waitingQue_
		CThreadPoolCommun& operator=(const CThreadPoolCommun &)=delete;
		~CThreadPoolCommun();
	};
}

#endif